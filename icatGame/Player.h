#pragma once
#include "PhysicsEntity.h"
#include "userInteraction.h"
#include "Weapon.h"
#include "glm/glm.hpp"
class Player : public PhysicsEntity
{
public:
	Player(PhysicsEntity* physicsEntity, Weapon* weapon);
	~Player();

	void update(float deltaTime);

private:
	void updateKeyEvents(float deltaTime);
	void updateMouseEvents(float deltaTime);

private:
	float speed;
	glm::vec3 direction;
	b2Vec2 linearVelocity, currLinearVel;
	Weapon* weapon;
};

