#include "TFShader.h"
namespace TomorrowFlower {
	// Attribs
	static TFShader::Attrib default_attribs[] = {
		{ TFShader::ATTRIB_POSITION, 1, GL_FLOAT_VEC3, "TF_position" },
		{ TFShader::ATTRIB_COLOR, 1, GL_FLOAT_VEC3, "TF_color" },
		{ TFShader::ATTRIB_NORMAL, 1, GL_FLOAT_VEC3, "TF_normal" },
		{ TFShader::ATTRIB_TEX_COORD, 1, GL_FLOAT_VEC2, "TF_texCoord" },
	};

	// Uniforms
	static TFShader::Uniform default_uniforms[] = {
		{ TFShader::UNIFORM_PROJECTION, 1, GL_FLOAT_MAT4, "TF_projection" },
		{ TFShader::UNIFORM_VIEW, 1, GL_FLOAT_MAT4, "TF_view" },
		{ TFShader::UNIFORM_MODEL, 1, GL_FLOAT_MAT4, "TF_model" },
	};

	const string MODEL_TEXTURE_DIFFUSE = "texture_diffuse";
	const string MODEL_TEXTURE_SPECULAR = "texture_specular";
}