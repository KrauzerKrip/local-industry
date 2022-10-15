#include "game.h"

Game::Game(IWindow* pWindow) {
	m_pWindow = pWindow;
}

Game::~Game() {};

void Game::init() {
	m_pInput = m_pWindow->getInput();
}

void Game::update() {

}

void Game::render() {

}

void Game::cleanUp() {

}