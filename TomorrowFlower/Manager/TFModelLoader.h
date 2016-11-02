#pragma once

#include "TFBase.h"
#include "TFModel.h"

namespace TomorrowFlower {
	class TF_DLL TFModelLoader
	{
	public:
		static TFModelLoader * getInstance();
		static void destroy();

		virtual TFModel::Ptr loadModel(const string &path) = 0;
	};
}