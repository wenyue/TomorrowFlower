#include "TomorrowFlower.h"
#include "TFCamera.h"
#include "TFEntity.h"
#include "TFMaterial.h"

#include "CameraController.hpp"

using namespace TomorrowFlower;

class Application : public TomorrowFlower::TFApplication
{
	SUPER(TomorrowFlower::TFApplication)
public:
	virtual void beginPlay() override
	{
		auto shader = TFShader::create("res/shader/default.vs", "res/shader/default.ps");
		TFMaterial::createByEngine(TFMaterial::DEFAULT_MATERIAL, shader);

		/*
		auto model = TFModel::create("res/char/nanosuit/nanosuit.obj");
		auto entity = TFEntity::create("nanosuit");
		entity->addComponent(model);*/

		auto entity = TFEntity::create("camera");
		auto camera = TFCamera::create();
		entity->addComponent(camera);
		auto cameraController = createObject<CameraController>();
		entity->addComponent(cameraController);

		Super::beginPlay();
	}

	virtual void tick(float deltaSeconds) override
	{
		Super::tick(deltaSeconds);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
	}
};

int main()
{
	Application app;
	app.init();
	app.run();
	
	return 0;
}