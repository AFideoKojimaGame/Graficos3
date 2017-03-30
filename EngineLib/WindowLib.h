#include <windows.h>

class Window{
		// window creation
	private:
		HWND _hwnd;
	public:
		bool create(HINSTANCE hInstance, unsigned int uiWidth, unsigned int uiHeight, LPSTR lpCmdLine, int nCmdShow);

		HWND hwnd() const;
};