#include "Pacman.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){

	Engine eng(hInstance, 800, 600);

	Game* pacman = new Pacman();
	eng.setGame(pacman);

	if (!eng.init(lpCmdLine, nCmdShow)){
		return 0;
	}else{
		eng.run();
	}
	return 0;
}