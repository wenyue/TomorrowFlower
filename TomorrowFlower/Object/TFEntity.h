#pragma once

#include "TFBase.h"
#include "TFObject.h"
#include "TFComponent.h"
#include "TFTransform.h"

namespace TomorrowFlower {
	class TF_DLL TFEntity : public TFObject
	{
		OBJECT_BODY(TFEntity)
	public:
		static Ptr create(const string &name = "", const Ptr &parent = nullptr);

		static Ptr createByEngine();

		// Some hook
		virtual void beginPlay() = 0;

		// About the children
		virtual void addChild(const Ptr &child) = 0;
		virtual void removeChild(const Ptr &chid) = 0;
		virtual int getChildCount() = 0;

		// About the parent
		PORPERTY_GET(Ptr, Parent)
		virtual void removeFromParent() = 0;

		// About the component
		virtual void addComponent(const TFComponent::Ptr &component) = 0;

		// About transform
		TFTransform transform;
		TFVec3 &position = transform.translation;
		inline TFVec3 forward() { return transform.forward(); }
		inline TFVec3 up() { return transform.up(); }
		inline TFVec3 left() { return transform.left(); }
		inline void lookAt(const TFVec3 &center) { transform.lookAt(center); }

		// Porpeties
		PORPERTY_GET(string, Name)
	};
}