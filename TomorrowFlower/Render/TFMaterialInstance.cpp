#include "TFMaterialInstance.h"
#include "TFMaterialManager.h"

namespace TomorrowFlower {
	class TFMaterialInstanceImplement : public TFMaterialInstance
	{
	public:
		TFMaterialInstanceImplement(const TFMaterial::Ptr &material)
			: mMaterial(material)
		{
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
				action->onInit(mMaterial->getShader());
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

	TFMaterialInstance::Ptr TFMaterialInstance::create(const TFMaterial::Ptr &material)
	{

		auto materialInstance = createObject<TFMaterialInstanceImplement>(material);
		return materialInstance;
	}
}