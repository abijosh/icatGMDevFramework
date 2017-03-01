#pragma once

#include "IcatGame.h"
#include "LevelLoader.h"
#include "ContactListener.h"

class Game
{
public:
	Game(IcatGame* icatGame);
	~Game();

	void initLevel(int levelNum);
	void update();

private:
	void updateKeyEvents(float deltaTime);
	void updateMouseEvents(float deltaTime);

private:
	IcatGame *icatGame;
	Scene* currentScene;
	LevelLoader* levelLoader;
	std::vector<Player*> players;
	std::vector<Entity*> toBeRemoved;

	b2Vec2 gravity{ 0.0f, -9.80f };
	b2World* physicsWorld;

	ContactListener contactListener;
};

