#pragma once

#include "TFBase.h"
#include "TFObject.h"
#include "TFMaterial.h"

namespace TomorrowFlower {
	class TF_DLL TFMaterialInstance : public TFMaterial
	{
		OBJECT_BODY(TFMaterialInstance)
	public:
		static Ptr create();
		static Ptr create(const TFMaterial::Ptr material);

		virtual void setMaterial(const TFMaterial::Ptr &material) = 0;

		// TFMaterial functions
		virtual void onRenderBegin() = 0;
		virtual void onRenderEnd() = 0;

		virtual void addMaterialAction(const TFMaterialAction::Ptr &action) = 0;

		PORPERTY(TFShader::Ptr, Shader)
		PORPERTY_GET(string, Name)
	};
}
