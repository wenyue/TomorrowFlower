#pragma once

#include "TFBase.h"
#include "TFMaterial.h"

namespace TomorrowFlower {
	class TF_DLL TFMaterialManager
	{
	public:
		static TFMaterialManager* getInstance();
		static void destroy();

		virtual void addMaterial(const TFMaterial::Ptr &material) = 0;
		virtual TFMaterial::Ptr getMaterial(const string &name) = 0;
	};
}
