#pragma once

#include "TFBase.h"
#include "TFModel.h"

namespace TomorrowFlower {
	class TF_DLL TFModelLoader
	{
	public:
		virtual TFModel::Ptr loadModel(const string &path) = 0;
	};
}