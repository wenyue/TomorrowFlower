#pragma once

#include "TFBase.h"

struct GLFWwindow;
namespace TomorrowFlower {
	// Class that creates and handles the main window.
	// Game main loop is also implement in this class.
	class TF_DLL TFApplication
	{
	public:
		static TFApplication *getInstance();

	public:
		TFApplication();
		~TFApplication();

		bool init();

		// Start game main loop.
		void run();

		// Some hooks provide for the users.
		virtual void beginPlay();
		virtual void tick(float deltaSeconds);
		virtual void draw();
		virtual void keyPress(int key, int action, int mods);

		virtual int getWidth() { return mWidth; }
		virtual int getHeight() { return mHeight; }
	protected:
		GLFWwindow *mWindow;

		int mWidth;
		int mHeight;
	};
}