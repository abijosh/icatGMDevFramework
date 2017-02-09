#pragma once

#include "IcatGame.h"
#include "LevelLoader.h"

class Game
{
public:
	Game(IcatGame* icatGame);
	~Game();

	void initLevel(int levelNum);
private:
	IcatGame *icatGame;
	Scene* currentScene;
	LevelLoader* levelLoader;
};

