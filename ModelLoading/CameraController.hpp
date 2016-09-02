#pragma once

#include "TFComponent.h"
#include "TFComponentImpl.h"

namespace TomorrowFlower {
	class CameraController : public TFComponentImpl<TFComponent>
	{
	public:
		void beginPlay() override
		{
			registerHook(COMPONENT_HOOK_KEYPRESS);
			entity()->setPosition(TFVec3(0, 0, -1));
			entity()->transform.lookAt(TFVec3(0, 0, 0));
		}

		void keyPress(int key, int action, int mods) override
		{
			entity()->transform.lookAt(TFVec3(0, 0, 0));
		}

	private:
	};
}