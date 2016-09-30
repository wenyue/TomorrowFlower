#include "TFCamera.h"
#include "TFComponentImpl.h"
#include "Application/TFApplication.h"

namespace TomorrowFlower {
	TFCamera::Ptr sMainCamera = nullptr;

	class TFCameraImplement : public TFComponentImpl<TFCamera>
	{
	public:
		void beginPlay() override
		{
			registerHook(COMPONENT_HOOK_DRAW);

			updateProjection();
		}

		void draw() override
		{
		}

	private:
		void updateProjection()
		{
			auto app = TFApplication::getInstance();
			if (!app) {
				TFError("Haven't create application object");
				return;
			}

			int width = app->getWidth();
			int height = app->getHeight();
			mProjection = glm::perspective(45.0f, (float)width / (float)height, 0.1f, 100.0f);
		}

	private:
		TFMat4 mProjection;
	};

	TFCamera::Ptr TFCamera::create()
	{
		return createObject<TFCameraImplement>();
	}

	void TFCamera::setActiveCamera(const Ptr &camera)
	{
		sMainCamera = camera;
	}

	TFCamera::Ptr TFCamera::getActiveCamera()
	{
		return sMainCamera;
	}
}