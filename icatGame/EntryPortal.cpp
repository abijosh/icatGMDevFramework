#include "EntryPortal.h"
auto optionalNegative = [](float x){int i = rand() % 2; i == 0 ? x : x *= -1; return x; };

EntryPortal::EntryPortal(PhysicsEntity* physicsEntity, float maxTimeGapPerEntry, float minTimeGapPerEntry,
	EnemyData* enemyData, Scene* scenePtr, b2World* physicsWorld)
	:Portal(physicsEntity)
	, maxTimeGapPerEntry(maxTimeGapPerEntry)
	, minTimeGapPerEntry(minTimeGapPerEntry)
	, enemyData(enemyData)
	, scenePtr(scenePtr)
	, physicsWorld(physicsWorld)
{
	timeAfterLastEntry = 0.0f;
	physicsBody->SetUserData(this);
}


EntryPortal::~EntryPortal()
{
}

void EntryPortal::update(float deltaTime){
	timeAfterLastEntry += deltaTime;
	if (timeAfterLastEntry > minTimeGapPerEntry){
		if (rand() % 2){
			timeAfterLastEntry = 0.0f;
			createEnemy();
		}
		else if (timeAfterLastEntry > maxTimeGapPerEntry){
			timeAfterLastEntry -= maxTimeGapPerEntry;
			createEnemy();
		}
	}
}

void EntryPortal::createEnemy(){
	glm::vec3 spawnPos = position;
	spawnPos.x += optionalNegative(offsetX);
	spawnPos.y += 2.0f;

	b2Body* physicsBody = physicsBodyCreator(spawnPos.x, spawnPos.y, enemyData->halfWidth, enemyData->halfHeight, b2_dynamicBody, physicsWorld, true);
	
	scenePtr->addDynamicEntity( new Enemy(new PhysicsEntity(enemyData->entity, physicsBody), enemyData->health));
}