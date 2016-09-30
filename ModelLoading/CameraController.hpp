#pragma once

#include "TFComponent.h"
#include "TFComponentImpl.h"
#include <GL/glfw3.h>

namespace TomorrowFlower {
	class CameraController : public TFComponentImpl<TFComponent>
	{
	public:
		CameraController()
			: mForward(0)
			, mLeft(0)
		{
		}

		void beginPlay() override
		{
			registerHook(COMPONENT_HOOK_KEYPRESS);
			registerHook(COMPONENT_HOOK_TICK);

			auto entity = getEntity();
			entity->position = TFVec3(0, 0, -1);
			entity->lookAt(TFVec3(0, 0, 0));
		}

		void keyPress(int key, int action, int mods) override
		{
			if (action != GLFW_PRESS && action != GLFW_RELEASE) return;

			if (key == GLFW_KEY_W)
				mForward += action == GLFW_PRESS ? 1.0f : -1.0f;
			else if (key == GLFW_KEY_S)
				mForward += action == GLFW_PRESS ? -1.0f : 1.0f;
			else if (key == GLFW_KEY_A)
				mLeft += action == GLFW_PRESS ? 1.0f : -1.0f;
			else if (key == GLFW_KEY_D)
				mLeft += action == GLFW_PRESS ? -1.0f : 1.0f;
		}

		void tick(float DeltaSeconds) override
		{
			auto entity = getEntity();
			const float forwardSpeed = 1.0f;

			auto deltaForward = entity->forward() * forwardSpeed * mForward;
			entity->position += deltaForward;
			TFLog("%lf %lf %lf", entity->position.x, entity->position.y, entity->position.z);
		}

	private:
		float mForward;
		float mLeft;
	};
}