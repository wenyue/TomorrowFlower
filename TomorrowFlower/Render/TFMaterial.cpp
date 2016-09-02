#include "TFMaterial.h"
#include "TFMaterialManager.h"

namespace TomorrowFlower {
	const char* TFMaterial::DEFAULT_MATERIAL = "__default__";

	class TFMaterialImplement : public TFMaterial
	{
		OBJECT_BODY(TFMaterialImplement)
	public:
		TFMaterialImplement(
			const string &name,
			const TFShader::Ptr &shader
		)
			: mName(name)
			, mShader(shader)
		{
		}

		void onRenderBegin() override
		{
			mShader->use();

			for (auto &action : mActions) {
				action->onRenderBegin(mShader);
			}
		}

		void onRenderEnd() override
		{
			for (auto &action : mActions) {
				action->onRenderEnd(mShader);
			}

			mShader->unuse();
		}

		void addMaterialAction(TFMaterialAction *action) override
		{
			mActions.push_back(unique_ptr<TFMaterialAction>(action));
			action->onShaderChanage(mShader);
		}

	private:
		vector<unique_ptr<TFMaterialAction>> mActions;

	private:
		MEMBER(TFShader::Ptr, Shader)
		MEMBER_GET(string, Name)
	};

	TFMaterial::Ptr TFMaterial::create(const string &name)
	{
		return TFMaterialManager::getInstance()->getMaterial(name);
	}

	TFMaterial::Ptr TFMaterial::createByEngine(
		const string &name,
		const TFShader::Ptr &shader
	)
	{
		auto material = createObject<TFMaterialImplement>(name, shader);
		TFMaterialManager::getInstance()->addMaterial(material);
		return material;
	}
}