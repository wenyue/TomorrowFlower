#include "TFCamera.h"
#include "TFComponentImpl.h"

namespace TomorrowFlower {
	TFCamera::Ptr sMainCamera = nullptr;

	class TFCameraImplement : public TFComponentImpl<TFCamera>
	{
	public:
		void beginPlay() override
		{
			registerHook(COMPONENT_HOOK_TICK);
		}

		void tick(float DeltaSeconds) override
		{
		}

	private:
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