#pragma once

#include "TFBase.h"
#include "TFObject.h"
#include "TFShader.h"

namespace TomorrowFlower {
	class TF_DLL TFMaterialAction : public TFObject
	{
		OBJECT_BODY(TFMaterialAction);
	public:
		virtual void onInit(const TFShader::Ptr &shader) {};
		virtual void onRenderBegin(const TFShader::Ptr &shader) {};
		virtual void onRenderEnd(const TFShader::Ptr &shader) {};
	};
}
