#include "TFTextureManager.h"
#include "TFTextureLoader.hpp"
#include "TFSingleton.h"
#include <unordered_map>

namespace TomorrowFlower {
	class TFTextureManagerImplement : public TFSingleton<TFTextureManagerImplement>, public TFTextureManager
	{
	public:
		TFTextureManagerImplement()
		{
			mLoader = TFTextureLoaderImplement::getInstance();
		}

		void setTextureLoader(TFTextureLoader *loader) override
		{
			mLoader = loader;
		}

		TFTextureLoader *getTextureLoader() override
		{
			return mLoader;
		}

		virtual void addTexture(const TFTexture::Ptr &texture) override
		{
			auto &path = texture->getPath();
			mTextures[path] = texture;
		}

		virtual TFTexture::Ptr getTexture(const string &path) override
		{
			if (!mTextures[path]) {
				mTextures[path] = mLoader->loadTexture(path);
			}
			return mTextures[path];
		}

	private:
		TFTextureLoader *mLoader;
		unordered_map<string, TFTexture::Ptr> mTextures;
	};

	TFTextureManager *TFTextureManager::getInstance()
	{
		return TFTextureManagerImplement::TFSingleton::getInstance();
	}

	void TFTextureManager::destroy()
	{
		TFTextureManagerImplement::TFSingleton::destroy();
	}
}