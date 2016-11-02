#pragma once

#include "MaterialActions/TFMaterialAction.h"
#include "TFTexture.h"

namespace TomorrowFlower {
	class TFMaterialActionBindTexture : public TFMaterialAction
	{
		OBJECT_BODY(TFMaterialAction)
	public:
		static Ptr create(
			const string &samplerName,
			const TFTexture::Ptr &texture
		)
		{
			return createObject<TFMaterialActionBindTexture>(samplerName, texture);
		}

		// Constructor
		TFMaterialActionBindTexture(
			const string &samplerName,
			const TFTexture::Ptr &texture
		)
			: mSamplerName(samplerName)
			, mTexture(texture)
			, mTextureUnit(-1)
		{
		}

		void onInit(const TFShader::Ptr &shader) override
		{
			mTextureUnit = shader->getUnusedTextureUnit();

			auto &sampler = shader->getCustomerUniform(mSamplerName);
			glUniform1i(sampler.location, mTextureUnit);
		}

		void onRenderBegin(const TFShader::Ptr &shader) override
		{
			if (mTextureUnit != -1) {
				glUniform1i(0, mTextureUnit);
				glActiveTexture(GL_TEXTURE0 + mTextureUnit);
				glBindTexture(GL_TEXTURE_2D, mTexture->getId());
			}
		}

	private:
		string mSamplerName;
		TFTexture::Ptr mTexture;

		GLint mTextureUnit;
	};
}
