#pragma once

#include "IcatGame.h"
#include "LevelLoader.h"

class Game
{
public:
	Game(IcatGame* icatGame);
	~Game();

	void initLevel(int levelNum);
	void update();
private:
	IcatGame *icatGame;
	Scene* currentScene;
	LevelLoader* levelLoader;

	b2Vec2 gravity{ 0.0f, -9.80f };
	b2World* physicsWorld;
};

