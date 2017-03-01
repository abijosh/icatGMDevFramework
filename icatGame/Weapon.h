#pragma once
#include "Scene.h"
#include "PhysicsEntity.h"
#include "Ammo.h"
class Weapon : public PhysicsEntity
{
public:
	Weapon(PhysicsEntity* physicsEntity, AmmoData ammoData);
	~Weapon();

	void fire(b2World* physicsWorldPtr, Scene* scenePtr, 
		glm::vec3 playerPosition, float playerDirection);

private:
	AmmoData ammoData;
};

