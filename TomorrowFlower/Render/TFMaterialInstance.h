#pragma once

#include "TFBase.h"
#include "TFObject.h"
#include "TFMaterial.h"

namespace TomorrowFlower {
	class TF_DLL TFMaterialInstance : public TFMaterial
	{
		OBJECT_BODY(TFMaterialInstance)
	public:
		static Ptr create(const TFMaterial::Ptr &material);

		// TFMaterial functions
		virtual void onRenderBegin() = 0;
		virtual void onRenderEnd() = 0;

		virtual void addMaterialAction(const TFMaterialAction::Ptr &action) = 0;

		PORPERTY_GET(TFShader::Ptr, Shader)
		PORPERTY_GET(string, Name)
	};
}
