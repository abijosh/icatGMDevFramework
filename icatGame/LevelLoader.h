#pragma once

#include <fstream>
#include <sstream>
#include <iomanip>

#include "IcatGame.h"
#include "Scene.h"
#include "PhysicsEntity.h"
#include "Ammo.h"
#include "Weapon.h"
#include "Player.h"
#include "Enemy.h"
#include "EntryPortal.h"
#include "ExitPortal.h"

class LevelLoader
{
public:
	LevelLoader(IcatGame* icatGame);
	~LevelLoader();

	Scene* load(int levelNum, b2World* worldPtr);
	Player* getPlayer(){ return player; }

private:
	Scene* createScene(std::string levelData);
	std::string readLevelData(int levelNum);

	EntryPortal *createEntryPortal(const glm::vec3& position, Scene *scene);
	PhysicsEntity *createExitPortal(const glm::vec3& position, Scene *scene);
	PhysicsEntity *createBrick(const glm::vec3& position);
	PhysicsEntity *createPlatform(const glm::vec3& position);
	Weapon* createPistol(const glm::vec3& position);
	void createPlayer(const glm::vec3& position);

	EnemyData* getEnemyData();

	b2Body* createPhysicsBody(float x, float y, float width, float height, b2BodyType bodyType);

private:
	b2World* currentWorldPtr;
	IcatGame* icatGame;
	Player* player;
};

