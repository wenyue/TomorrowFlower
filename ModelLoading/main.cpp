#include "TomorrowFlower.h"
#include "TFCamera.h"
#include "TFEntity.h"
#include "TFMaterial.h"
#include "TFMeshBuilder.h"
#include "TFPrimitive.h"

#include "CameraController.hpp"

using namespace TomorrowFlower;

class Application : public TomorrowFlower::TFApplication
{
	SUPER(TomorrowFlower::TFApplication);
public:
	Application()
	{
		mWidth = 800;
		mHeight = 600;
	}

	virtual void beginPlay() override
	{
		auto shader = TFShader::create("res/shader/default.vs", "res/shader/default.ps");
		auto material = TFMaterial::create(TFMaterial::DEFAULT_MATERIAL, shader);
		//material->addMaterialAction();


		createCamera();
		createCube();

		Super::beginPlay();
	}

	virtual void tick(float deltaSeconds) override
	{
		Super::tick(deltaSeconds);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
	}

private:
	void createCamera()
	{
		auto entity = TFEntity::create("camera");
		auto camera = TFCamera::create();
		entity->addComponent(camera);
		auto cameraController = createObject<CameraController>();
		entity->addComponent(cameraController);
	}

	void createCube()
	{
		auto entity = TFEntity::create("cube");
		auto cube = TFPrimitive::create();
		cube->setMesh(buildCube(TFVec3(0.5, 0.5, 1)));
		entity->addComponent(cube);
	}
};

int main()
{
	Application app;
	app.init();
	app.run();
	
	return 0;
}