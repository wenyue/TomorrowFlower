#include "TFComponentManager.h"
#include "TFSingleton.h"

namespace TomorrowFlower {
	class TFComponentManagerImplement : public TFSingleton<TFComponentManagerImplement>, public TFComponentManager
	{
	public:
		TFComponentManagerImplement()
		{
			mHookComponents.resize(COMPONENT_HOOK_MAX);
		}

		void registerComponent(ComponentHook componentHook, const TFComponent::Ptr &component, int priority) override
		{
			mHookComponents[componentHook].push_back(component);
		}

		void callComponentDraw() override
		{
			for (auto &component : mHookComponents[COMPONENT_HOOK_DRAW]) {
				component->draw();
			}
		}

		void callComponentTick(float deltaSeconds) override
		{
			for (auto &component : mHookComponents[COMPONENT_HOOK_TICK]) {
				component->tick(deltaSeconds);
			}
		}

		void callComponentKeyPress(int key, int action, int mods) override
		{
			for (auto &component : mHookComponents[COMPONENT_HOOK_KEYPRESS]) {
				component->keyPress(key, action, mods);
			}
		}

	private:
		typedef vector<TFComponent::Ptr> ComponentArray;
		vector<ComponentArray> mHookComponents;
	};

	TFComponentManager* TFComponentManager::getInstance()
	{
		return TFComponentManagerImplement::TFSingleton::getInstance();
	}

	void TFComponentManager::destroy()
	{
		TFComponentManagerImplement::TFSingleton::destroy();
	}
}