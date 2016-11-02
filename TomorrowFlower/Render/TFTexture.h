#pragma once

#include "TFBase.h"
#include "TFObject.h"

namespace TomorrowFlower {
	class TF_DLL TFTexture : public TFObject
	{
		OBJECT_BODY(TFTexture);
	public:
		static Ptr create(const string &path);

		static Ptr createByEngine(
			const string &path,
			const unsigned char *image,
			int width,
			int height
		);

		virtual const string & getPath() = 0;
		virtual GLint getId() = 0;
	};
}
