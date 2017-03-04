#pragma once
#include <Box2D\Box2D.h>

#include "Scene.h"
#include "PhysicsEntity.h"
#include "Enemy.h"
class EntryPortal : public PhysicsEntity
{
public:
	EntryPortal(PhysicsEntity* physicsEntity, float maxTimeGapPerEntry, float minTimeGapPerEntry,
		EnemyData* enemyData, Scene* scenePtr, b2World* physicsWorld);
	~EntryPortal();
	void update(float deltaTime);

	void regenerate(Enemy* enemy);

private:
	void createEnemy();
	void respawn(const glm::vec3 spawnPos);
private:
	std::vector<Enemy*> regeneratables;
	EnemyData* enemyData;
	Scene* scenePtr;
	b2World* physicsWorld;
	float timeAfterLastEntry, maxTimeGapPerEntry, minTimeGapPerEntry;
	float offsetX{ 2.0f };
};

