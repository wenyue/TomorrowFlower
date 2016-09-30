#include "Application/TFApplication.h"
#include "TFEntityManager.h"
#include "TFComponentManager.h"
#include <time.h>

// GLFW
#include <GL/glfw3.h>

#define MAJOR_VERSION 3
#define MINOR_VERSION 3

namespace TomorrowFlower {
	TFApplication* app = nullptr;

	TFApplication* TFApplication::getInstance()
	{
		return app;
	}

	TFApplication::TFApplication()
		: mWidth(0)
		, mHeight(0)
	{
		TFAssert(!app, "Look forward to create multiple applications");
		app = this;
	};

	TFApplication::~TFApplication()
	{
		app = nullptr;
	}

	bool TFApplication::init()
	{
		// Init GLFW
		glfwInit();
		// Set all the required options for GLFW
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, MAJOR_VERSION);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, MINOR_VERSION);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

		// Create a GLFWwindow object that we can use for GLFW's functions
		mWindow = glfwCreateWindow(mWidth, mHeight, "LearnOpenGL", nullptr, nullptr);
		if (mWindow == nullptr)
		{
			TFError("Failed to create GLFW window");
			glfwTerminate();
			return false;
		}

		glfwMakeContextCurrent(mWindow);
		// Set the required callback functions
		auto keyCallback = [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			app->keyPress(key, action, mods);
		};
		glfwSetKeyCallback(mWindow, keyCallback);

		// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
		glewExperimental = GL_TRUE;
		// Initialize GLEW to setup the OpenGL Function pointers
		if (glewInit() != GLEW_OK)
		{
			TFError("Failed to initialize GLEW");
			return false;
		}

		// Define the viewport dimensions
		glViewport(0, 0, mWidth, mHeight);

		return true;
	}

	void TFApplication::run()
	{
		beginPlay();

		// Game loop
		clock_t start, end;
		start = clock();
		while (!glfwWindowShouldClose(mWindow))
		{
			// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
			glfwPollEvents();

			// tick
			end = clock();
			float deltaSeconds = (static_cast<float>(end - start)) / CLOCKS_PER_SEC;
			start = end;
			tick(deltaSeconds);

			// draw
			draw();

			// Swap the screen buffers
			glfwSwapBuffers(mWindow);
		}

		// Terminate GLFW, clearing any resources allocated by GLFW.
		glfwTerminate();
	}

	void TFApplication::beginPlay()
	{
		// Init all Entities
		auto rootEntity = TFEntityManager::getInstance()->getRootEntity();
		rootEntity->beginPlay();
	}

	void TFApplication::tick(float deltaSeconds)
	{
		TFComponentManager::getInstance()->callComponentTick(deltaSeconds);
	}

	void TFApplication::draw()
	{
		TFComponentManager::getInstance()->callComponentDraw();
	}

	void TFApplication::keyPress(int key, int action, int mods)
	{
		TFComponentManager::getInstance()->callComponentKeyPress(key, action, mods);
	}
}