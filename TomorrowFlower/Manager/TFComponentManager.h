#pragma once

#include "TFBase.h"
#include "TFComponent.h"

namespace TomorrowFlower {
	class TF_DLL TFComponentManager
	{
	public:
		static TFComponentManager* getInstance();
		static void destroy();

		virtual void registerComponent(ComponentHook componentHook, const TFComponent::Ptr &component, int priority = 0) = 0;
		virtual void callComponentDraw() = 0;
		virtual void callComponentTick(float deltaSeconds) = 0;
		virtual void callComponentKeyPress(int key, int action, int mods) = 0;
	};
}