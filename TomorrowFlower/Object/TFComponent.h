#pragma once

#include "TFBase.h"
#include "TFObject.h"

namespace TomorrowFlower {
	enum ComponentHook {
		COMPONENT_HOOK_DRAW,
		COMPONENT_HOOK_TICK,
		COMPONENT_HOOK_KEYPRESS,

		COMPONENT_HOOK_MAX,
	};

	class TFEntity;

	class TF_DLL TFComponent : public TFObject
	{
		OBJECT_BODY(TFComponent)
	public:
		// Some hook
		virtual void registerHook(ComponentHook componentHook) = 0;
		virtual void beginPlay() {};
		virtual void tick(float DeltaSeconds) {};
		virtual void draw() {};
		virtual void keyPress(int key, int action, int mods) {};

		virtual void setEntity(shared_ptr<TFEntity> entity) = 0;
		virtual shared_ptr<TFEntity> entity() = 0;
	};
}