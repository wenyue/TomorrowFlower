#include "TFMaterialManager.h"
#include "TFSingleton.h"
#include <unordered_map>

namespace TomorrowFlower {
	class TFMaterialManagerImplement : public TFSingleton<TFMaterialManagerImplement>, public TFMaterialManager
	{
	public:
		void addMaterial(const TFMaterial::Ptr &material) override
		{
			auto &name = material->getName();
			mMaterials[name] = material;
		}

		TFMaterial::Ptr getMaterial(const string &name) override
		{
			return mMaterials[name];
		}

	private:
		unordered_map<string, TFMaterial::Ptr> mMaterials;
	};

	TFMaterialManager *TFMaterialManager::getInstance()
	{
		return TFMaterialManagerImplement::TFSingleton::getInstance();
	}

	void TFMaterialManager::destroy()
	{
		TFMaterialManagerImplement::TFSingleton::destroy();
	}
}