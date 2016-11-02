#include "TFTextureLoader.h"
#include "TFSingleton.h"
#include "SOIL/SOIL.h"

namespace TomorrowFlower {
	class TFTextureLoaderImplement : public TFSingleton<TFTextureLoaderImplement>, public TFTextureLoader
	{
	public:
		virtual TFTexture::Ptr loadTexture(const string &path) override
		{
			int width, height;
			unsigned char *image = SOIL_load_image(path.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
			TFTexture::Ptr texture = TFTexture::createByEngine(path, image, width, height);
			SOIL_free_image_data(image);
			return texture;
		}
	};
}