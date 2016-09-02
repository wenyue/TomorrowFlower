#include "TFModelManager.h"
#include "TFModelLoader.hpp"
#include "TFSingleton.h"
#include <unordered_map>

namespace TomorrowFlower {
	class TFModelManagerImplement : public TFSingleton<TFModelManagerImplement>, public TFModelManager
	{
	public:
		TFModelManagerImplement()
		{
			mLoader = TFModelLoaderImplement::getInstance();
		}

		void setModelLoader(TFModelLoader* loader) override
		{
			mLoader = loader;
		}

		TFModelLoader* getModelLoader() override
		{
			return mLoader;
		}

		void addModel(const TFModel::Ptr &model) override
		{
			auto &path = model->getPath();
			mModels[path] = model;
		}

		TFModel::Ptr getModel(const string &path) override
		{
			if (!mModels[path]) {
				if (!mLoader) {
					TFError("trying to get model before set a model loader.");
					return nullptr;
				}
				mModels[path] = mLoader->loadModel(path);
			}
			return mModels[path];
		}

	private:
		TFModelLoader* mLoader;
		unordered_map<string, TFModel::Ptr> mModels;
	};

	TFModelManager* TFModelManager::getInstance()
	{
		return TFModelManagerImplement::TFSingleton::getInstance();
	}

	void TFModelManager::destroy()
	{
		TFModelManagerImplement::TFSingleton::destroy();
	}
}