#include "TFShaderManager.h"
#include "TFSingleton.h"
#include <unordered_map>

namespace TomorrowFlower {
	class TFShaderManagerImplement : public TFSingleton<TFShaderManagerImplement>, public TFShaderManager
	{
	public:

		virtual void addShader(const TFShader::Ptr &shader) override
		{
			auto &vertexPath = shader->getVertexPath();
			auto &fragmentPath = shader->getFragmentPath();
			auto hashValue = hash_value(vertexPath) + hash_value(fragmentPath);
			mShaders[hashValue] = shader;
		}

		virtual TFShader::Ptr getShader(const string &vertexPath, const string &fragmentPath) override
		{
			auto hashValue = hash_value(vertexPath) + hash_value(fragmentPath);
			if (!mShaders[hashValue]) {
				mShaders[hashValue] = TFShader::createByEngine(vertexPath, fragmentPath);
			}
			return mShaders[hashValue];
		}

	private:
		unordered_map<size_t, TFShader::Ptr> mShaders;
	};

	TFShaderManager* TFShaderManager::getInstance()
	{
		return TFShaderManagerImplement::TFSingleton::getInstance();
	}

	void TFShaderManager::destroy()
	{
		TFShaderManagerImplement::TFSingleton::destroy();
	}
}