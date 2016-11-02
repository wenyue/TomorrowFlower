#pragma once

#include "TFBase.h"
#include "TFObject.h"
#include "TFShader.h"
#include "MaterialActions/TFMaterialAction.h"

namespace TomorrowFlower {
	class TF_DLL TFMaterial : public TFObject
	{
		OBJECT_BODY(TFMaterial);
	public:
		static const char *DEFAULT_MATERIAL;

		static Ptr create(const string &name, const TFShader::Ptr &shader);

		virtual void onRenderBegin() = 0;
		virtual void onRenderEnd() = 0;

		virtual void addMaterialAction(const TFMaterialAction::Ptr &action) = 0;

		PORPERTY_GET(TFShader::Ptr, Shader);
		PORPERTY_GET(string, Name);
	};

	class TF_DLL TFMaterialInstance : public TFMaterial
	{
		OBJECT_BODY(TFMaterialInstance);
	public:
		static Ptr create(const string &name);

		// TFMaterial functions
		virtual void onRenderBegin() = 0;
		virtual void onRenderEnd() = 0;

		virtual void addMaterialAction(const TFMaterialAction::Ptr &action) = 0;

		PORPERTY_GET(TFShader::Ptr, Shader);
		PORPERTY_GET(string, Name);
	};
}
