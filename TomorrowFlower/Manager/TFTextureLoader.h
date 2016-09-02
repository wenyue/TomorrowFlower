#pragma once

#include "TFBase.h"
#include "TFTexture.h"

namespace TomorrowFlower {
	class TF_DLL TFTextureLoader
	{
	public:
		virtual TFTexture::Ptr loadTexture(const string &path) = 0;
	};
}