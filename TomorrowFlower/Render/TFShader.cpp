#include "TFShader.h"
#include "TFShaderDefine.h"
#include "TFShaderManager.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <unordered_map>

namespace TomorrowFlower {
	const TFShader::Attrib & TFShader::getDefaultAttribInfo(TFShader::AttribType attribType)
	{
		TFAssert(default_attribs[attribType].location == attribType, "");

		return default_attribs[attribType];
	}

	class TFShaderImplement : public TFShader
	{
	public:
		TFShaderImplement(
			const string &vertexPath,
			const string &fragmentPath
		)
			: mVertexPath(vertexPath)
			, mFragmentPath(fragmentPath)
		{
			setupProgram();
		}

		void use() override
		{
			glUseProgram(mProgram);
		}

		void unuse() override
		{
			glUseProgram(0);
		}

		const string & getVertexPath() override
		{
			return mVertexPath;
		}

		const string & getFragmentPath() override
		{
			return mFragmentPath;
		}

		const Attrib & getDefaultAttrib(AttribType attribType) override
		{
			return mDefaultAttribs[attribType];
		}

		const Attrib & getCustomerAttrib(const string &attribName) override
		{
			return mCustomerAttribs[attribName];
		}

		const Uniform & getDefaultUniform(UniformType uniformType) override
		{
			return mDefaultUniforms[uniformType];
		}

		const Uniform & getCustomerUniform(const string &uniformName) override
		{
			return mCustomerUniforms[uniformName];
		}

		GLint getUnusedTextureUnit() override
		{
			auto ret = mUnusedTextureUnit.back();
			mUnusedTextureUnit.pop_back();
			return ret;
		}

		void releaseTextureUnit(GLint textureUnit) override
		{
#ifdef DEBUG
			for (auto value : mUnusedTextureUnit) {
				TFAssert(value != textureUnit, "can't release an unused texture unit: %d", textureUnit);
			}
#endif // DEBUG

			mUnusedTextureUnit.push_back(textureUnit);
		}

	private:
		void setupProgram()
		{
			// 1. Retrieve the vertex/fragment source code from filePath
			string vertexCode;
			string fragmentCode;
			ifstream vShaderFile;
			ifstream fShaderFile;
			// ensures ifstream objects can throw exceptions:
			vShaderFile.exceptions (std::ifstream::badbit);
			fShaderFile.exceptions (std::ifstream::badbit);
			try
			{
				// Open files
				vShaderFile.open(mVertexPath);
				fShaderFile.open(mFragmentPath);
				std::stringstream vShaderStream, fShaderStream;
				// Read file's buffer contents into streams
				vShaderStream << vShaderFile.rdbuf();
				fShaderStream << fShaderFile.rdbuf();
				// close file handlers
				vShaderFile.close();
				fShaderFile.close();
				// Convert stream into string
				vertexCode = vShaderStream.str();
				fragmentCode = fShaderStream.str();
			}
			catch (std::ifstream::failure e)
			{
				std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
			}
			const GLchar *vShaderCode = vertexCode.c_str();
			const GLchar *fShaderCode = fragmentCode.c_str();
			// 2. Compile shaders
			GLuint vertex, fragment;
			GLint success;
			GLchar infoLog[512];
			// Vertex Shader
			vertex = glCreateShader(GL_VERTEX_SHADER);
			glShaderSource(vertex, 1, &vShaderCode, nullptr);
			glCompileShader(vertex);
			// Print compile errors if any
			glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(vertex, 512, nullptr, infoLog);
				std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
			}
			// Fragment Shader
			fragment = glCreateShader(GL_FRAGMENT_SHADER);
			glShaderSource(fragment, 1, &fShaderCode, nullptr);
			glCompileShader(fragment);
			// Print compile errors if any
			glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(fragment, 512, nullptr, infoLog);
				std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
			}
			// Shader Program
			mProgram = glCreateProgram();
			glAttachShader(mProgram, vertex);
			glAttachShader(mProgram, fragment);

			// 3. Bind predefine attributes
			bindPredefinedVertexAttribs();

			// 4. Link program
			glLinkProgram(mProgram);
			// Print linking errors if any
			glGetProgramiv(mProgram, GL_LINK_STATUS, &success);
			if (!success)
			{
				glGetProgramInfoLog(mProgram, 512, nullptr, infoLog);
				std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
			}
			// Delete the shaders as they're linked into our program now and no longer necessery
			glDeleteShader(vertex);
			glDeleteShader(fragment);

			// 5. Parse shader
			parseAttribs();
			parseUniforms();
			setupUnusedTextureUnit();
		}

		void bindPredefinedVertexAttribs()
		{
			const int size = sizeof(default_attribs) / sizeof(default_attribs[0]);

			for (auto &attr : default_attribs) {
				glBindAttribLocation(mProgram, attr.location, attr.name.c_str());
			}
		}

		void parseAttribs()
		{
			mCustomerAttribs.clear();

			GLint activeAttribs;
			GLint length;
			glGetProgramiv(mProgram, GL_ACTIVE_ATTRIBUTES, &activeAttribs);
			glGetProgramiv(mProgram, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &length);
			GLchar *attribName = (GLchar*)alloca(length + 1);
			attribName[length] = '\0';
			Attrib attrib;

			// Walk through each of the active attribs, and store their information.
			for (int i = 0; i < activeAttribs; ++i) {
				glGetActiveAttrib(mProgram, i, length, nullptr, &attrib.size, &attrib.type, attribName);
				attrib.name = attribName;
				attrib.location = glGetAttribLocation(mProgram, attribName);
				mCustomerAttribs[attrib.name] = attrib;
			}

			// Remove the default attribs from customer map, and restore them into the default map.
			for (auto &attr : default_attribs) {
				if (mCustomerAttribs.count(attr.name)) {
#ifdef DEBUG
					auto equal = [](const Attrib &a, const Attrib &b) {
						return a.location == b.location && a.size == b.size && a.type == b.type;
					};
					TFAssert(equal(mCustomerAttribs[attr.name], attr), "");
#endif // DEBUG
					mCustomerAttribs.erase(attr.name);
					mDefaultAttribs[(AttribType)attr.location] = attr;
				}
			}
		}

		void parseUniforms()
		{
			mCustomerUniforms.clear();

			GLint activeUniforms;
			GLint length;
			glGetProgramiv(mProgram, GL_ACTIVE_UNIFORMS, &activeUniforms);
			glGetProgramiv(mProgram, GL_ACTIVE_UNIFORM_MAX_LENGTH, &length);
			GLchar *uniformName = (GLchar*)alloca(length + 1);
			uniformName[length] = '\0';
			Uniform uniform;

			// Walk through each of the actived uniforms, and store their information.
			for (int i = 0; i < activeUniforms; ++i) {
				glGetActiveUniform(mProgram, i, length, nullptr, &uniform.size, &uniform.type, uniformName);
				uniform.name = uniformName;
				uniform.location = glGetUniformLocation(mProgram, uniformName);
				mCustomerUniforms[uniform.name] = uniform;
			}

			// Remove the default uniforms from customer map, and restore them into the default map.
			for (auto &uniform : default_uniforms) {
				if (mCustomerUniforms.count(uniform.name)) {
#ifdef DEBUG
					auto equal = [](const Uniform &a, const Uniform &b) {
						return a.size == b.size && a.type == b.type;
					};
					TFAssert(equal(mCustomerUniforms[uniform.name], uniform), "");
#endif // DEBUG
					mCustomerUniforms.erase(uniform.name);
					mDefaultUniforms[(UniformType)uniform.location] = uniform;
				}
			}
		}

		void setupUnusedTextureUnit()
		{
			GLint texture_units;
			glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &texture_units);
			for (GLint i = texture_units - 1; i >= 0; --i) {
				mUnusedTextureUnit.push_back(i);
			}
		}

	private:
		GLuint mProgram;
		string mVertexPath, mFragmentPath;

		unordered_map<AttribType, Attrib> mDefaultAttribs;
		unordered_map<string, Attrib> mCustomerAttribs;
		unordered_map<UniformType, Uniform> mDefaultUniforms;
		unordered_map<string, Uniform> mCustomerUniforms;

		vector<GLint> mUnusedTextureUnit;
	};

	TFShader::Ptr TFShader::create(const string &vertexPath, const string &fragmentPath)
	{
		return TFShaderManager::getInstance()->getShader(vertexPath, fragmentPath);
	}

	TFShader::Ptr TFShader::createByEngine(const string &vertexPath, const string &fragmentPath)
	{
		auto shader = createObject<TFShaderImplement>(vertexPath, fragmentPath);
		TFShaderManager::getInstance()->addShader(shader);
		return shader;
	}
}
