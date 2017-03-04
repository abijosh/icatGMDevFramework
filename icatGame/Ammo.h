#pragma once
#include "PhysicsEntity.h"

struct AmmoData{
	AmmoData(Entity* entity,
		float x, float y,
		float halfWidth, float halfHeight,
		float hitforce, float damage,
		b2BodyType bodyType,
		b2Vec2 velocity){
		this->entity = entity;
		this->x = x;
		this->y = y;
		this->halfHeight = halfHeight;
		this->halfWidth = halfWidth;
		this->bodyType = bodyType;
		this->velocity = velocity;
		this->damage = damage;
		this->hitForce = hitforce;

	}
	// render properties
	Entity* entity;
	// physics properties
	float x, y, halfWidth, halfHeight;
	b2BodyType bodyType;
	b2Vec2 velocity;
	float damage, hitForce;
};

class Ammo : public PhysicsEntity
{
public:
	Ammo(PhysicsEntity* physicsEntity, b2Vec2 velocity, float damage, float hitForce);
	~Ammo();

	void update(float deltaTime);

	void startContact(PhysicsEntity* other);
	void endContact(PhysicsEntity* other);

	float getHitForce(){ return hitForce; }
	float getDamage(){ return damage; }

private:
	b2Vec2 velocity;
	float damage, hitForce;
};

