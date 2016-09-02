#pragma once

#include "TFBase.h"
#include "TFShader.h"

namespace TomorrowFlower {
	class TF_DLL TFShaderManager
	{
	public:
		static TFShaderManager* getInstance();
		static void destroy();

		virtual void addShader(const TFShader::Ptr &shader) = 0;
		virtual TFShader::Ptr getShader(const string &vertexPath, const string &fragmentPath) = 0;
	};
}