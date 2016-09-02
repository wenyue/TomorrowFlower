#pragma once

#include "TFBase.h"
#include "TFComponent.h"

namespace TomorrowFlower {
	class TF_DLL TFCamera : public TFComponent
	{
		OBJECT_BODY(TFCamera)
	public:
		static Ptr create();

		virtual void beginPlay() override = 0;
		virtual void tick(float DeltaSeconds) override = 0;

		// Active current camera to be the main camera.
		static void setActiveCamera(const Ptr &camera);

		// Get Active camera, active camera is the camera to look at the word.
		static Ptr getActiveCamera();
	};
}
