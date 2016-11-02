#pragma once

#include "TFBase.h"
#include "TFComponent.h"

namespace TomorrowFlower {
	class TF_DLL TFCamera : public TFComponent
	{
		OBJECT_BODY(TFCamera);
	public:
		static Ptr create();

		// Active current camera to be the main camera.
		static void setActiveCamera(const Ptr &camera);

		// Get Active camera, active camera is the camera to look at the word.
		static Ptr getActiveCamera();
	};
}
