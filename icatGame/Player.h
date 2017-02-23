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

	void fire(b2World* physicsWorldPtr, Scene* scenePtr);

private:

private:
	float speed;
	int jumpStep;
	glm::vec3 direction;
	b2Vec2 linearVelocity;
	Weapon* weapon;
};

