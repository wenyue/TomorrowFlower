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
			auto &components = mHookComponents[COMPONENT_HOOK_DRAW];
			for (auto it = components.rbegin(); it != components.rend(); ++it) {
				auto component = it->lock();
				if (component) component->draw(); else components.erase(it.base());
			}
		}

		void callComponentTick(float deltaSeconds) override
		{
			auto &components = mHookComponents[COMPONENT_HOOK_DRAW];
			for (auto it = components.rbegin(); it != components.rend(); ++it) {
				auto component = it->lock();
				if (component) component->tick(deltaSeconds); else components.erase(it.base());
			}
		}

		void callComponentKeyPress(int key, int action, int mods) override
		{
			auto &components = mHookComponents[COMPONENT_HOOK_DRAW];
			for (auto it = components.rbegin(); it != components.rend(); ++it) {
				auto component = it->lock();
				if (component) component->keyPress(key, action, mods); else components.erase(it.base());
			}
		}

	private:
		typedef vector<TFComponent::WPtr> ComponentArray;
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