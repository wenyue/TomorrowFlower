#pragma once

#include "TFBase.h"
#include "TFEntity.h"
#include "TFComponentManager.h"

namespace TomorrowFlower {
	template class TF_DLL weak_ptr<TFEntity>;

	template <class TFComponent>
	class TFComponentImpl : public TFComponent
	{
	public:
		virtual void registerHook(ComponentHook componentHook) override
		{
			TFComponentManager::getInstance()->registerComponent(componentHook, self());
		}

		virtual void setEntity(TFEntity::Ptr entity) override
		{
			mEntity = entity;
		}

		virtual TFEntity::Ptr entity() override
		{
			return mEntity.lock();
		}

	private:
		TFEntity::WPtr mEntity;
	};
}