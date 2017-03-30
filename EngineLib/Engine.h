#ifndef ENGINE_H
#define ENGINE_H

#include <iostream>
#include "WindowLib.h"
#include "Renderer.h"
#include "Game.h"
#include "DirectInput.h"
#include "Timer.h"
#include "Camera.h"

#define DllExport __declspec( dllexport )

using namespace std;

class Engine{
	public:
		DllExport Engine(HINSTANCE hInstance, unsigned int uiWidth, unsigned int uiHeight);
		DllExport ~Engine();
		DllExport bool init(LPSTR lpCmdLine, int nCmdShow);
		DllExport void run();
		DllExport void setGame(Game* g);

	private:
		Window* w;
		Renderer* m_Graphics;
		HINSTANCE m_hInstance;
		unsigned int m_uiWidth;
		unsigned int m_uiHeight;
		bool bDone = false;
		Game* m_Game;
		DirectInput* m_dInput;
		Timer* m_Timer;
};

#endif