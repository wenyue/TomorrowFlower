#include "TFMesh.h"

namespace TomorrowFlower {
	class TFMeshImplement : public TFMesh
	{
	public:
		TFMeshImplement()
			: mIsDirty(false)
		{
			setupMesh();
		}

		void draw() override
		{
			if (!mMaterial) {
				return;
			}

			// Refresh VBO and EBO if it is dirty.
			if (mIsDirty) {
				RefreshBuffer();
				mIsDirty = false;
			}

			mMaterial->onRenderBegin();

			// Draw mesh
			glBindVertexArray(mVAO);
			glDrawElements(GL_TRIANGLES, mIndices.size(), GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);

			mMaterial->onRenderEnd();
		}

		void setVertices(vector<TFVertex> &&vertices, vector<GLuint> &&indices) override
		{
			mVertices = move(vertices);
			mIndices = move(indices);
			mIsDirty = true;
		}

	private:
		void convertAttribType(GLenum inType, GLenum &outType, GLint &outCounter)
		{
			switch (inType) {
			case GL_FLOAT_VEC2:
				outType = GL_FLOAT;
				outCounter = 2;
				break;
			case GL_FLOAT_VEC3:
				outType = GL_FLOAT;
				outCounter = 3;
				break;
			default:
				outType = inType;
				outCounter = 1;
			}
		}

		void setupMesh()
		{
			glGenVertexArrays(1, &mVAO);
			glGenBuffers(1, &mVBO);
			glGenBuffers(1, &mEBO);
		}

		void RefreshBuffer()
		{
			glBindVertexArray(mVAO);

			glBindBuffer(GL_ARRAY_BUFFER, mVBO);
			glBufferData(GL_ARRAY_BUFFER, mVertices.size() * sizeof(TFVertex), &mVertices[0], GL_STATIC_DRAW);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, mIndices.size() * sizeof(GLuint), &mIndices[0], GL_STATIC_DRAW);

			auto setVertexAttrib = [&](TFShader::AttribType attribType, size_t offset) {
				auto attr = TFShader::getDefaultAttribInfo(attribType);
				glEnableVertexAttribArray(attr->location);
				GLenum type;
				GLint size;
				convertAttribType(attr->type, type, size);
				glVertexAttribPointer(attr->location, size, type,
					GL_FALSE, sizeof(TFVertex), (GLvoid*)offset);
			};

			// Vertex Position
			setVertexAttrib(TFShader::ATTRIB_POSITION, offsetof(TFVertex, position));

			// Vertex Normals
			setVertexAttrib(TFShader::ATTRIB_NORMAL, offsetof(TFVertex, normal));

			// Vertex Texture Coords
			setVertexAttrib(TFShader::ATTRIB_TEX_COORD, offsetof(TFVertex, texCoord));

			glBindVertexArray(0);
		}

	private:
		vector<TFVertex> mVertices;
		vector<GLuint> mIndices;
		GLuint mVAO, mVBO, mEBO;

		bool mIsDirty;

		MEMBER(TFMaterialInstance::Ptr, Material);
	};

	TFMesh::Ptr TFMesh::create()
	{
		return createObject<TFMeshImplement>();
	}
}