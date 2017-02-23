#pragma once
#include "PhysicsEntity.h"

struct AmmoData{
	AmmoData(Entity* entity,
		float x, float y,
		float halfWidth, float halfHeight,
		b2BodyType bodyType,
		b2Vec2 velocity){
		this->entity = entity;
		this->x = x;
		this->y = y;
		this->halfHeight = halfHeight;
		this->halfWidth = halfWidth;
		this->bodyType = bodyType;
		this->velocity = velocity;

	}
	// render properties
	Entity* entity;
	// physics properties
	float x, y, halfWidth, halfHeight;
	b2BodyType bodyType;
	b2Vec2 velocity;
};

class Ammo : public PhysicsEntity
{
public:
	Ammo(PhysicsEntity* physicsEntity, b2Vec2 velocity);
	~Ammo();

	void update(float deltaTime);

	void startContact();
	void endContact();

private:
	b2Vec2 velocity;
};

