#include "Ammo.h"


Ammo::Ammo(PhysicsEntity* physicsEntity, b2Vec2 velocity, float damage, float hitForce)
	:PhysicsEntity(*physicsEntity)
	, velocity(velocity)
	, damage(damage)
	, hitForce(hitForce)
{
	physicsBody->SetUserData(this);
	setType(Entity::BULLET);
}


Ammo::~Ammo()
{
}

void Ammo::update(float deltaTime){
	physicsBody->SetLinearVelocity(velocity);
	PhysicsEntity::update(deltaTime); 
}

void Ammo::startContact(PhysicsEntity* other){
	//velocity.x *= -1;
	deactivate();
	removeAfter();
}

void Ammo::endContact(PhysicsEntity* other){

}