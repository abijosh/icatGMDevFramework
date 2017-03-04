#pragma once
#include <iostream>
#include "PhysicsEntity.h"
#include "Ammo.h"
struct EnemyData{
	EnemyData(Entity* entity,
		float halfWidth, float halfHeight,
		float health, float healthIncreaseFactor,
		b2Vec2 velocity){
		this->entity = entity;
		this->halfHeight = halfHeight;
		this->halfWidth = halfWidth;
		this->health = health;
		this->healthIncreaseFactor = healthIncreaseFactor;
		this->velocity = velocity;
	}
	Entity* entity;
	float halfWidth, halfHeight, health, healthIncreaseFactor;
	b2Vec2 velocity;
};

class Enemy : public PhysicsEntity
{
public:
	Enemy(PhysicsEntity* physicsEntity, float health, float healthIncreaseFactor);
	~Enemy();

	void update(float timeDelta);

	void startContact(PhysicsEntity* other);
	void endContact(PhysicsEntity* other);
	float getDirection(){ return direction; }

	void setOffScreen();
	void regen(const glm::vec3 pos, float health);
	float getHealth(){ return health; }
	float getHealthIncreaseFactor(){ return healthIncreaseFactor; }

private:
	void setPosition(const glm::vec3 pos);

	void setDirAndVel();
	void kill(Ammo* ammo);
	void getHit(Ammo* ammo);
private:
	b2Vec2 prevPos;
	float direction;
	bool hit;
	float hitForce{ 0.0f };
	int contactRegister{ 0 };
	float health, healthIncreaseFactor;
};

