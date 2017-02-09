#include "Game.h"


Game::Game(IcatGame* icatGame)
{
	this->icatGame = icatGame;
	currentScene = nullptr;
	levelLoader = new LevelLoader(icatGame);
}


Game::~Game()
{
}

void Game::initLevel(int levelNum){
	currentScene = levelLoader->load(levelNum);
	if (currentScene)
		icatGame->setScenePtr(currentScene);
}