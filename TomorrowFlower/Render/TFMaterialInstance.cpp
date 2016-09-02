#include "TFMaterialInstance.h"

namespace TomorrowFlower {
	class TFMaterialInstanceImplement : public TFMaterialInstance
	{
	public:
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

		void setMaterial(const TFMaterial::Ptr &material) override
		{
			mMaterial = material;
			for (auto &action : mActions) {
				action->onShaderChanage(mMaterial->getShader());
			}
		}

		void addMaterialAction(TFMaterialAction* action) override
		{
			mActions.push_back(unique_ptr<TFMaterialAction>(action));
			if (mMaterial) {
				action->onShaderChanage(mMaterial->getShader());
			}
		}

	private:
		TFMaterial::Ptr mMaterial;
		vector<unique_ptr<TFMaterialAction>> mActions;
	};

	TFMaterialInstance::Ptr TFMaterialInstance::create()
	{
		return createObject<TFMaterialInstanceImplement>();
	}
}