#include "Engine.h"

Engine::Engine(HINSTANCE hInstance, unsigned int uiWidth, unsigned int uiHeight)
	:
	m_hInstance(hInstance),
	m_uiWidth(uiWidth),
	m_uiHeight(uiHeight),
	w(new Window()),
	m_Graphics(new Renderer()),
	m_Game(NULL),
	m_dInput(new DirectInput()),
	m_Timer(new Timer())
{}

Engine::~Engine(){
	delete m_Game;
	m_Game = NULL;
	delete m_Graphics;
	m_Graphics = NULL;
	delete m_dInput;
	m_dInput = NULL;
	delete m_Timer;
	m_Timer = NULL;
	delete w;
	w = NULL;
}

bool Engine::init(LPSTR lpCmdLine, int nCmdShow){
	if (!w->create(m_hInstance, m_uiWidth, m_uiHeight, lpCmdLine, nCmdShow))
		return false;

	if (!m_Graphics->init(w->hwnd()))
		return false;

	if (!m_dInput->init(m_hInstance, w->hwnd()))
		return false;

	if (!m_Game->init(*m_Graphics))
		return false;

	if (!m_Timer) return false;

	else m_Timer->firstMeasure();

	return true;
}

void Engine::setGame(Game* g){
	m_Game = g;
}

void Engine::run(){
	MSG msg;

	while (!m_Game->isDone()){
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if (msg.message == WM_QUIT){
			m_Game->setDone(true);
		}

		m_dInput->reacquire();
		m_Graphics->beginFrame();
		m_Game->frame(*m_Graphics, *m_dInput, *m_Timer);
		m_Timer->measure();
		m_Graphics->endFrame();
	}

	m_Game->deinit();
}