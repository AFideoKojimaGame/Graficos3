#include "Game.h"

bool Game::isDone() const{
	return m_bDone;
}

void Game::setDone(bool bDone){
	m_bDone = bDone;
}