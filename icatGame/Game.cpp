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
	if (currentScene){
		icatGame->setScenePtr(currentScene);
		players = levelLoader->getPlayer();
	}
}

void Game::update(){
	physicsWorld->Step(0.2f, 8, 3);

	auto deltaTime = icatGame->getDeltaTime();
	updateKeyEvents(deltaTime);
	updateMouseEvents(deltaTime);

	auto es = currentScene->getEntities();
	for (auto* e : es){
		e->update(deltaTime);
	}

}


void Game::updateMouseEvents(float deltaTime){
	if (UserInteraction::mouseLeftButtonDown){
		for (auto* player : players){
			player->fire(physicsWorld, currentScene);
		}
	}
}

void Game::updateKeyEvents(float deltaTime){

	if (UserInteraction::changed){
		for (auto* player : players){
			if (UserInteraction::left)	player->moveLeft(deltaTime);
			if (UserInteraction::right)	player->moveRight(deltaTime);
			if (UserInteraction::space)	player->jump(deltaTime);
		}
		//UserInteraction::changed = false;
	}
}