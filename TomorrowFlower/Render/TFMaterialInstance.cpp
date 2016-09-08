#include "TFMaterialInstance.h"
#include "TFMaterialManager.h"

namespace TomorrowFlower {
	class TFMaterialInstanceImplement : public TFMaterialInstance
	{
	public:
		void setMaterial(const TFMaterial::Ptr &material) override
		{
			mMaterial = material;
			for (auto &action : mActions) {
				action->onShaderChanage(mMaterial->getShader());
			}
		}

		void onRenderBegin() override
		{
			mMaterial->onRenderBegin();

			for (auto &action : mActions) {
				action->onRenderBegin(mMaterial->getShader());
			}
		}

		void onRenderEnd() override
		{
			for (auto &action : mActions) {
				action->onRenderEnd(mMaterial->getShader());
			}

			mMaterial->onRenderEnd();
		}

		void addMaterialAction(const TFMaterialAction::Ptr &action) override
		{
			mActions.push_back(action);
			if (mMaterial) {
				action->onShaderChanage(mMaterial->getShader());
			}
		}

		void setShader(const TFShader::Ptr &shader) override
		{
			mMaterial->setShader(shader);
			for (auto &action : mActions) {
				action->onShaderChanage(mMaterial->getShader());
			}
		}

		TFShader::Ptr getShader() override
		{
			return mMaterial->getShader();
		}

		string getName() override
		{
			return mMaterial->getName();
		}

	private:
		TFMaterial::Ptr mMaterial;
		vector<TFMaterialAction::Ptr> mActions;
	};

	TFMaterialInstance::Ptr TFMaterialInstance::create()
	{
		return createObject<TFMaterialInstanceImplement>();
	}

	TFMaterialInstance::Ptr TFMaterialInstance::create(const TFMaterial::Ptr material)
	{

		auto materialInstance = createObject<TFMaterialInstanceImplement>();
		materialInstance->setMaterial(material);
		return materialInstance;
	}
}