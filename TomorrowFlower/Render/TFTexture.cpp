#include "TFTexture.h"
#include "TFTextureManager.h"

namespace TomorrowFlower {
	class TFTextureImplement : public TFTexture
	{
	public:
		TFTextureImplement(
			const string &path,
			const unsigned char* image,
			int width,
			int height
		)
			: mPath(path)
			, mWidth(width)
			, mHeight(height)
		{
			generateTexture(image);
		}

		const string &getPath() override
		{
			return mPath;
		}

		GLint getId() override
		{
			return mId;
		}

	private:
		void generateTexture(const unsigned char* image)
		{
			//Generate texture ID and load texture data 
			glGenTextures(1, &mId);
			// Assign texture to ID
			glBindTexture(GL_TEXTURE_2D, mId);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, mWidth, mHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
			glGenerateMipmap(GL_TEXTURE_2D);	

			// Parameters
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glBindTexture(GL_TEXTURE_2D, 0);
		}

	private:
		GLuint mId;
		string mPath;
		int mWidth;
		int mHeight;
	};

	TFTexture::Ptr TFTexture::create(const string &path)
	{
		return TFTextureManager::getInstance()->getTexture(path);
	}

	TFTexture::Ptr TFTexture::createByEngine(
		const string &path,
		const unsigned char* image,
		int width,
		int height
	)
	{
		auto texture = createObject<TFTextureImplement>(path, image, width, height);
		TFTextureManager::getInstance()->addTexture(texture);
		return texture;
	}
}