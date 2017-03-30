#ifndef GAME_H
#define GAME_H

#include "Renderer.h"
#include "Quad.h"
#include "Sprite.h"

#define DllExport __declspec( dllexport )

class DirectInput;
class Timer;

class Game{
	public:
		DllExport Game(){};
		DllExport virtual bool init(Renderer& rkRenderer) = 0;
		DllExport virtual void frame(Renderer& pkRenderer, DirectInput& rkInput, Timer& rkTimer) = 0;
		DllExport virtual void deinit() = 0;

		DllExport bool isDone() const;
		DllExport void setDone(bool bDone);

	private:
		bool m_bDone = false;
};

#endif