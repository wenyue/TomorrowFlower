#include "TFEntity.h"
#include "TFEntityManager.h"

namespace TomorrowFlower {
	class TFEntityImplement : public TFEntity
	{
	public:
		// Contructor
		TFEntityImplement(const string &name)
			: mName(name)
		{
		}

		void beginPlay() override
		{
			for (auto &component : mComponents) {
				component->beginPlay();
			}

			for (auto &child : mChildren) {
				child->beginPlay();
			}
		}

		void addChild(const Ptr &child) override
		{
			auto &parent = (dynamic_cast<TFEntityImplement*>(child.get()))->mParent;
			TFAssert(parent.expired(), "The child '%s' has multiply parents", child->getName().c_str());
			mChildren.push_back(child);
			parent = self();
		}

		void removeChild(const Ptr &child) override
		{
			auto childIter = find(mChildren.begin(), mChildren.end(), child);
			TFAssert(childIter != mChildren.end(), "Can't find the child '%s' from '%s'", child->getName().c_str(), getName().c_str());
			mChildren.erase(childIter);
			(dynamic_cast<TFEntityImplement*>(child.get()))->mParent.reset();
		}

		int getChildCount() override
		{
			return mChildren.size();
		}

		Ptr getParent() override
		{
			return mParent.lock();
		}

		void removeFromParent() override
		{
			auto parent = getParent();
			TFAssert(parent, "");
			parent->removeChild(self());
		}

		void addComponent(const TFComponent::Ptr &component) override
		{
			mComponents.push_back(component);
			component->setEntity(self());
		}

		TFVec3 getPosition() override
		{
			return transform.translation;
		}

		void setPosition(const TFVec3 &position)
		{
			transform.translation = position;
		}

	private:
		vector<Ptr> mChildren;
		TFEntity::WPtr mParent;

		vector<TFComponent::Ptr> mComponents;

		MEMBER_GET(string, Name)
	};

	TFEntity::Ptr TFEntity::create(const string &name, const Ptr &parent)
	{
		auto entity = createObject<TFEntityImplement>(name);
		if (parent) {
			parent->addChild(entity);
		}
		else {
			auto rootEntity = TFEntityManager::getInstance()->getRootEntity();
			rootEntity->addChild(entity);
		}
		return entity;
	}

	TFEntity::Ptr TFEntity::createByEngine()
	{
		return createObject<TFEntityImplement>("");
	}
}