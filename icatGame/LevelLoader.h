#pragma once

#include <fstream>
#include <sstream>
#include <iomanip>

#include "IcatGame.h"
#include "Scene.h"
#include "PhysicsEntity.h"

class LevelLoader
{
public:
	LevelLoader(IcatGame* icatGame);
	~LevelLoader();

	Scene* load(int levelNum);

private:
	Scene* createScene(std::string levelData);
	std::string readLevelData(int levelNum);

	PhysicsEntity *createBrick(const glm::vec3& position);
	PhysicsEntity *createPlatform(const glm::vec3& position);
	PhysicsEntity *createPlayer(const glm::vec3& position);

private:
	IcatGame* icatGame;
};

