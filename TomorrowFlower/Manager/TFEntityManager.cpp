#include "TFEntityManager.h"
#include "TFSingleton.h"

namespace TomorrowFlower {
	class TFEntityManagerImplement : public TFSingleton<TFEntityManagerImplement>, public TFEntityManager
	{
	public:
		TFEntityManagerImplement()
		{
			auto rootEntity = TFEntity::createByEngine();
			mRootEntity = rootEntity;
		}

		TFEntity* getRootEntity() override
		{
			return mRootEntity.get();
		}

	private:
		TFEntity::Ptr mRootEntity;
	};

	TFEntityManager* TFEntityManager::getInstance()
	{
		return TFEntityManagerImplement::TFSingleton::getInstance();
	}

	void TFEntityManager::destroy()
	{
		TFEntityManagerImplement::TFSingleton::destroy();
	}
}