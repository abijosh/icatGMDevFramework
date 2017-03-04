#pragma once
#include "PhysicsEntity.h"
#include "userInteraction.h"
#include "Weapon.h"
#include <iostream>
#include "glm/glm.hpp"
class Player : public PhysicsEntity
{
public:
	Player(PhysicsEntity* physicsEntity, Weapon* weapon);
	~Player();

	void update(float deltaTime);
	void moveLeft(float deltaTime);
	void moveRight(float deltaTime);
	void jump(float deltaTime);

	void startContact(PhysicsEntity* other);
	void endContact(PhysicsEntity* other);

	void fire(b2World* physicsWorldPtr, Scene* scenePtr);

	bool isFiring(){ return firing; }
	void stopFiring(){ weapon->stopFiring(); firing = false; }

private:

private:
	bool firing, onAir;
	float speed;
	int jumpStep;
	glm::vec3 direction;
	b2Vec2 linearVelocity;
	Weapon* weapon;
};

