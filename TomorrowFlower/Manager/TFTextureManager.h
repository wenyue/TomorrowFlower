#pragma once

#include "TFBase.h"
#include "TFTexture.h"
#include "TFTextureLoader.h"

namespace TomorrowFlower {
	class TF_DLL TFTextureManager
	{
	public:
		static TFTextureManager * getInstance();
		static void destroy();

		virtual void setTextureLoader(TFTextureLoader *loader) = 0;
		virtual TFTextureLoader * getTextureLoader() = 0;

		virtual void addTexture(const TFTexture::Ptr &texture) = 0;
		virtual TFTexture::Ptr getTexture(const string &path) = 0;
	};
}