#pragma once

#include "TFBase.h"
#include "TFModelLoader.h"

namespace TomorrowFlower {
	class TF_DLL TFModelManager
	{
	public:
		static TFModelManager* getInstance();
		static void destroy();

		virtual void setModelLoader(TFModelLoader* loader) = 0;
		virtual TFModelLoader* getModelLoader() = 0;

		virtual void addModel(const TFModel::Ptr &model) = 0;
		virtual TFModel::Ptr getModel(const string &path) = 0;
	};
}