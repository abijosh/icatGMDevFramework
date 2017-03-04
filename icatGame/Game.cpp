#include "Game.h"


Game::Game(IcatGame* icatGame)
{
	this->icatGame = icatGame;
	currentScene = nullptr;
	levelLoader = new LevelLoader(icatGame);
}


Game::~Game()
{
	int i = 1;
}

void Game::initLevel(int levelNum){
	physicsWorld = new b2World(gravity);
	physicsWorld->SetContactListener(&contactListener);

	currentScene = levelLoader->load(levelNum, physicsWorld);
	if (currentScene){
		icatGame->setScenePtr(currentScene);
		player = levelLoader->getPlayer();
	}
}

void Game::update(){

	auto deltaTime = icatGame->getDeltaTime();
	updateKeyEvents(deltaTime);
	updateMouseEvents(deltaTime);

	auto es = currentScene->getDynamicEntities();
	for (auto* e : es){
		e->update(deltaTime);
		if (e->isScheduledToBeRemoved()){
			removeEntity(e);
		}
	}
	physicsWorld->Step(0.2f, 8, 3);
	std::cout << physicsWorld->GetBodyCount() <<std::endl;
}

void Game::removeEntity(Entity* entity){
	physicsWorld->DestroyBody(((PhysicsEntity*)entity)->getPhysicsBody());
	currentScene->erase(entity);
}

void Game::updateMouseEvents(float deltaTime){
	if (UserInteraction::mouseLeftButtonDown)
		player->fire(physicsWorld, currentScene);
	else if (player->isFiring())
		player->stopFiring();
}

void Game::updateKeyEvents(float deltaTime){
	if (UserInteraction::left)	player->moveLeft(deltaTime);
	if (UserInteraction::right)	player->moveRight(deltaTime);
	if (UserInteraction::space || UserInteraction::up)	player->jump(deltaTime);
}