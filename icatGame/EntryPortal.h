#pragma once
#include <Box2D\Box2D.h>

#include "Scene.h"
#include "Portal.h"
class EntryPortal : public Portal
{
public:
	EntryPortal(PhysicsEntity* physicsEntity, float maxTimeGapPerEntry, float minTimeGapPerEntry,
		EnemyData* enemyData, Scene* scenePtr, b2World* physicsWorld);
	~EntryPortal();
	void update(float deltaTime);

private:
	void createEnemy();

private:
	EnemyData* enemyData;
	Scene* scenePtr;
	b2World* physicsWorld;
	float timeAfterLastEntry, maxTimeGapPerEntry, minTimeGapPerEntry;
	float offsetX{ 2.0f };
};

