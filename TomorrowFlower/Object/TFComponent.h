#pragma once

#include "TFBase.h"
#include "TFObject.h"
#include "TFEventProtocol.h"

namespace TomorrowFlower {
	enum ComponentHook {
		COMPONENT_HOOK_DRAW,
		COMPONENT_HOOK_TICK,
		COMPONENT_HOOK_KEYPRESS,

		COMPONENT_HOOK_MAX,
	};

	DEFINE_EVENT(DESTROY, void(void));

	class TFEntity;

	class TF_DLL TFComponent : public TFObject, TFEventProtocol
	{
		OBJECT_BODY(TFComponent);
	public:
		~TFComponent()
		{
			dispatchEvent<DESTROY>();
		}

		template<typename HandlerPtr>
		void autoReleaseHandler(const HandlerPtr &handler)
		{
			registerEvent<DESTROY>([=]() {
				auto ptr = handler.lock();
				if (ptr) ptr->clear();
			});
		}

		// Some hook
		virtual void registerHook(ComponentHook componentHook) = 0;
		virtual void beginPlay() {};
		virtual void tick(float DeltaSeconds) {};
		virtual void draw() {};
		virtual void keyPress(int key, int action, int mods) {};

		PORPERTY(shared_ptr<TFEntity>, Entity);
	};
}