#pragma once
#include "Scene.h"
#include "PhysicsEntity.h"
#include "Ammo.h"
class Weapon : public PhysicsEntity
{
public:
	Weapon(PhysicsEntity* physicsEntity, AmmoData ammoData);
	~Weapon();

	void startFire(b2World* physicsWorldPtr, Scene* scenePtr, 
		glm::vec3 playerPosition, float playerDirection);
	void stopFiring(){ currentRound = 0; }

	void update(float deltaTime){}

protected:
	AmmoData ammoData;
	int const maxRoundsPerFiring{ 1 };
	int currentRound;
};

