#pragma once

#include "TFBase.h"
#include "TFObject.h"
#include "TFShader.h"
#include "MaterialActions/TFMaterialAction.h"

namespace TomorrowFlower {
	class TF_DLL TFMaterial : public TFObject
	{
		OBJECT_BODY(TFMaterial)
	public:
		static const char* DEFAULT_MATERIAL;

		static Ptr create(const string &name);

		static Ptr createByEngine(
			const string &name,
			const TFShader::Ptr &shader
		);

		virtual void onRenderBegin() = 0;
		virtual void onRenderEnd() = 0;

		virtual void addMaterialAction(TFMaterialAction *action) = 0;

		PORPERTY(TFShader::Ptr, Shader)
		PORPERTY_GET(string, Name)
	};
}
