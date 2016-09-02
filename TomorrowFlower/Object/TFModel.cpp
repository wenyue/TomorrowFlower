#include "TFModel.h"
#include "TFComponentImpl.h"
#include "TFModelManager.h"

namespace TomorrowFlower {
	class TFModelNodeImplement : public TFModelNode
	{
	public:
		TFModelNodeImplement(
			const vector<TFMesh::Ptr> &meshes,
			const vector<Ptr> &subNodes
		)
			: mMeshes(meshes)
			, mSubNodes(subNodes)
		{
		}

		void draw() override
		{
			for (auto &mesh : mMeshes) {
				mesh->draw();
			}
		}

	private:
		vector<TFMesh::Ptr> mMeshes;
		vector<TFModelNode::Ptr> mSubNodes;
	};

	TFModelNode::Ptr TFModelNode::createByEngine(
		const vector<TFMesh::Ptr> &meshes,
		const vector<Ptr> &subNodes
	)
	{
		return createObject<TFModelNodeImplement>(meshes, subNodes);
	}


	class TFModelImplement : public TFComponentImpl<TFModel>
	{
	public:
		// Contructor
		TFModelImplement(
			const string &path,
			const TFModelNode::Ptr &rootNode
		)
			: mPath(path)
			, mRootNode(rootNode)
		{
		}

		void beginPlay() override
		{
			registerHook(COMPONENT_HOOK_DRAW);
		}

		void draw() override
		{
			mRootNode->draw();
		}

		const string & getPath() override
		{
			return mPath;
		}

	private:
		string mPath;
		TFModelNode::Ptr mRootNode;
	};

	TFModel::Ptr TFModel::create(const string &path)
	{
		return TFModelManager::getInstance()->getModel(path);
	}

	TFModel::Ptr TFModel::createByEngine(
		const string &path,
		const TFModelNode::Ptr &rootNode
	)
	{
		auto model = createObject<TFModelImplement>(path, rootNode);
		TFModelManager::getInstance()->addModel(model);
		return model;
	}
}