#include "TFMaterial.h"
#include "TFMaterialManager.h"

namespace TomorrowFlower {
	const char *TFMaterial::DEFAULT_MATERIAL = "__default__";

	class TFMaterialImplement : public TFMaterial
	{
		OBJECT_BODY(TFMaterialImplement);
	public:
		TFMaterialImplement(
			const string &name,
			const TFShader::Ptr &shader
		)
			: mName(name)
			, mShader(shader)
		{
			setupMaterial();
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

		void addMaterialAction(const TFMaterialAction::Ptr &action) override
		{
			mActions.push_back(action);
			action->onInit(mShader);
		}

	private:
		void setupMaterial()
		{
			// bind with projection matrix
			if (mShader->getDefaultUniform(TFShader::UNIFORM_PROJECTION)) {
				
			}
			// bind with view matrix
			if (mShader->getDefaultUniform(TFShader::UNIFORM_VIEW)) {

			}
		}

	private:
		vector<TFMaterialAction::Ptr> mActions;

		MEMBER_GET(TFShader::Ptr, Shader);
		MEMBER_GET(string, Name);
	};


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


	TFMaterial::Ptr TFMaterial::create(
		const string &name,
		const TFShader::Ptr &shader
	)
	{
		auto material = createObject<TFMaterialImplement>(name, shader);
		TFMaterialManager::getInstance()->addMaterial(material);
		return material;
	}

	TFMaterialInstance::Ptr TFMaterialInstance::create(
		const string &name
	)
	{
		auto material = TFMaterialManager::getInstance()->getMaterial(name);
		auto materialInstance = createObject<TFMaterialInstanceImplement>(material);
		return materialInstance;
	}
}