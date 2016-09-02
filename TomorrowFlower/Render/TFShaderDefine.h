#include "TFShader.h"
namespace TomorrowFlower {
	// Attribs
	static TFShader::Attrib default_attribs[] = {
		{ TFShader::ATTRIB_POSITION, 1, GL_FLOAT_VEC3, "_position" },
		{ TFShader::ATTRIB_COLOR, 1, GL_FLOAT_VEC3, "_color" },
		{ TFShader::ATTRIB_NORMAL, 1, GL_FLOAT_VEC3, "_normal" },
		{ TFShader::ATTRIB_TEX_COORD, 1, GL_FLOAT_VEC2, "_texCoord" },
	};

	// Uniforms
	static TFShader::Uniform default_uniforms[] = {
		{ TFShader::UNIFORM_CAMERA_OFFSET, 1, GL_FLOAT_VEC3, "_cameraOffset" },
	};

	const string MODEL_TEXTURE_DIFFUSE = "texture_diffuse";
	const string MODEL_TEXTURE_SPECULAR = "texture_specular";
}