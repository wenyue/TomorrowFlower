#include "TFModelLoader.h"
#include "TFSingleton.h"
#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"
#include "assimp/scene.h"
#include "MaterialActions/TFMaterialActionBindTexture.hpp"
#include "TFShaderDefine.h"

namespace TomorrowFlower {
	class TFModelLoaderImplement : public TFSingleton<TFModelLoaderImplement>, public TFModelLoader
	{
	public:
		TFModel::Ptr loadModel(const string &path)
		{
			// Read file via ASSIMP
			Assimp::Importer importer;
			const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
    
			// Check for errors
			if(!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
			{
				TFLog("ERROR::ASSIMP:: %s", importer.GetErrorString());
				return nullptr;
			}

			// Retrieve the directory path of the filepath
			string directory = path.substr(0, path.find_last_of('/'));

			// Process ASSIMP's root node recursively
			auto rootNode = processNode(scene->mRootNode, scene, directory);

			return TFModel::createByEngine(path, rootNode);
		}

	private:
		TFModelNode::Ptr processNode(aiNode* node, const aiScene* scene, const string &directory)
		{
			vector<TFMesh::Ptr> meshes;
			vector<TFModelNode::Ptr> subNodes;

			// Process each mesh located at the current node
			for(GLuint i = 0; i < node->mNumMeshes; i++)
			{
				// The node object only contains indices to index the actual objects in the scene. 
				// The scene contains all the data, node is just to keep stuff organized (like relations between nodes).
				aiMesh* mesh = scene->mMeshes[node->mMeshes[i]]; 
				meshes.push_back(processMesh(mesh, scene, directory));
			}
			// After we've processed all of the meshes (if any) we then recursively process each of the children nodes
			for(GLuint i = 0; i < node->mNumChildren; i++)
			{
				subNodes.push_back(processNode(node->mChildren[i], scene, directory));
			}

			return TFModelNode::createByEngine(meshes, subNodes);
		}

		TFMesh::Ptr processMesh(aiMesh* mesh, const aiScene* scene, const string &directory)
		{
			vector<TFVertex> vertices;
			vector<GLuint> indices;
			TFMaterialInstance::Ptr materialInstance;

			// Walk through each of the mesh's vertices
			for(GLuint i = 0; i < mesh->mNumVertices; i++)
			{
				TFVertex vertex;
				TFVec3 vector; // We declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's vec3 class so we transfer the data to this placeholder TFVec3 first.
				// Positions
				vector.x = mesh->mVertices[i].x;
				vector.y = mesh->mVertices[i].y;
				vector.z = mesh->mVertices[i].z;
				vertex.position = vector;
				// Normals
				vector.x = mesh->mNormals[i].x;
				vector.y = mesh->mNormals[i].y;
				vector.z = mesh->mNormals[i].z;
				vertex.normal = vector;
				// Texture Coordinates
				if(mesh->mTextureCoords[0]) // Does the mesh contain texture coordinates?
				{
					TFVec2 vec;
					// A vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't 
					// use models where a vertex can have multiple texture coordinates so we always take the first set (0).
					vec.x = mesh->mTextureCoords[0][i].x; 
					vec.y = mesh->mTextureCoords[0][i].y;
					vertex.texCoord = vec;
				}
				else
					vertex.texCoord = TFVec2(0.0f, 0.0f);
				vertices.push_back(vertex);
			}
			// Now walk through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
			for(GLuint i = 0; i < mesh->mNumFaces; i++)
			{
				aiFace face = mesh->mFaces[i];
				// Retrieve all indices of the face and store them in the indices vector
				for(GLuint j = 0; j < face.mNumIndices; j++)
					indices.push_back(face.mIndices[j]);
			}
			// Process materials
			if (mesh->mMaterialIndex >= 0)
			{
				aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
				materialInstance = processMaterial(material, directory);
			}
        
			// Return a mesh object created from the extracted mesh data
			auto modelMesh = TFMesh::create();
			modelMesh->setMaterial(materialInstance);
			modelMesh->setVertices(move(vertices), move(indices));
			return modelMesh;
		}

		TFMaterialInstance::Ptr processMaterial(aiMaterial* material, const string &directory)
		{
			auto materialInstance = TFMaterialInstance::create();
			materialInstance->setMaterial(TFMaterial::create(TFMaterial::DEFAULT_MATERIAL));

			// We assume a convention for sampler names in the shaders. Each diffuse texture should be named
			// as 'texture_diffuseN' where N is a sequential number ranging from 1 to MAX_SAMPLER_NUMBER. 
			// Same applies to other texture as the following list summarizes:
			// Diffuse: texture_diffuseN
			// Specular: texture_specularN
			// Normal: texture_normalN

			// 1. Diffuse maps
			vector<TFTexture::Ptr> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, directory);
			for (size_t i = 0; i < diffuseMaps.size(); ++i) {
				auto &diffuse = diffuseMaps[i];
				string diffuseName(MODEL_TEXTURE_DIFFUSE + to_string(i));
				materialInstance->addMaterialAction(TFMaterialActionBindTexture::create(
					diffuseName,
					diffuse
				));
			}
			// 2. Specular maps
			vector<TFTexture::Ptr> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, directory);
			for (size_t i = 0; i < specularMaps.size(); ++i) {
				auto &specular = specularMaps[i];
				string specularName(MODEL_TEXTURE_SPECULAR + to_string(i));
				materialInstance->addMaterialAction(TFMaterialActionBindTexture::create(
					specularName,
					specular
				));
			}

			return materialInstance;
		}

		vector<TFTexture::Ptr> loadMaterialTextures(aiMaterial* mat, aiTextureType type, const string &directory)
		{
			vector<TFTexture::Ptr> textures;
			for(GLuint i = 0; i < mat->GetTextureCount(type); i++)
			{
				aiString str;
				mat->GetTexture(type, i, &str);
				string path = directory + '/' + str.C_Str();
				TFTexture::Ptr texture = TFTexture::create(path);
				textures.push_back(texture);
			}
			return textures;
		}
	};
}