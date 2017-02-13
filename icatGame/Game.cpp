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
	physicsWorld = new b2World(gravity);
	currentScene = levelLoader->load(levelNum, physicsWorld);
	if (currentScene)
		icatGame->setScenePtr(currentScene);
}

void Game::update(){
	auto deltaTime = icatGame->getDeltaTime();
	physicsWorld->Step(0.2f, 8, 3);
	auto es = currentScene->getEntities();
	for (auto* e : es){
		e->update(deltaTime);
	}
	
}