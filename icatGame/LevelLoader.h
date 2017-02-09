#pragma once

#include <fstream>
#include <sstream>
#include <iomanip>

#include "IcatGame.h"
#include "Scene.h"

class LevelLoader
{
public:
	LevelLoader(IcatGame* icatGame);
	~LevelLoader();

	Scene* load(int levelNum);

private:
	Scene* createScene(std::string levelData);
	std::string readLevelData(int levelNum);

	Entity *createBrick(const glm::vec3& position);
	Entity *createPlatform(const glm::vec3& position);
	Entity *createPlayer(const glm::vec3& position);

private:
	IcatGame* icatGame;
};

