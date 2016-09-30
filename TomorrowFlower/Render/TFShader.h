#pragma once

#include "TFBase.h"
#include "TFObject.h"

namespace TomorrowFlower {
	class TF_DLL TFShader : public TFObject
	{
		OBJECT_BODY(TFShader)
	public:
		static Ptr create(const string &vertexPath, const string &fragmentPath);

		static Ptr createByEngine(const string &vertexPath, const string &fragmentPath);

		virtual void use() = 0;
		virtual void unuse() = 0;
		virtual const string & getVertexPath() = 0;
		virtual const string & getFragmentPath() = 0;

		///////////////////////////////////////////////////////////////////////
		// Attribute
		enum AttribType {
			ATTRIB_POSITION,
			ATTRIB_COLOR,
			ATTRIB_NORMAL,
			ATTRIB_TEX_COORD,

			ATTRIB_MAX,
		};
		struct Attrib
		{
			GLint location;
			GLint size;
			GLenum type;
			string name;
		};
		/*	Default attribs are predefined in fix location, size, type and name.
		 *	This method return the attrib info by specify attrib type.
		 */
		static const Attrib & getDefaultAttribInfo(AttribType attribType);
		/*	Similar as getDefaultAttribInfo, but it is not static method,
		 *	and return null while the instance hasn't speify attrib type.
		 */
		virtual const Attrib & getDefaultAttrib(AttribType attribType) = 0;
		virtual const Attrib & getCustomerAttrib(const string &attribName) = 0;

		///////////////////////////////////////////////////////////////////////
		// Uniform
		enum UniformType {
			UNIFORM_PROJECTION,
			UNIFORM_VIEW,
			UNIFORM_MODEL,

			UNIFORM_MAX,
		};
		struct Uniform
		{
			GLint location;
			GLint size;
			GLenum type;
			string name;
		};
		virtual const Uniform & getDefaultUniform(UniformType uniformType) = 0;
		virtual const Uniform & getCustomerUniform(const string &uniformName) = 0;

		///////////////////////////////////////////////////////////////////////
		// Texture
		virtual GLint getUnusedTextureUnit() = 0;
		virtual void releaseTextureUnit(GLint textureUnit) = 0;
	};
}
