#include "Ammo.h"


Ammo::Ammo(PhysicsEntity* physicsEntity, b2Vec2 velocity)
	:PhysicsEntity(*physicsEntity)
	, velocity(velocity)
{
}


Ammo::~Ammo()
{
}

void Ammo::update(float deltaTime){
	physicsBody->SetLinearVelocity(velocity);
	PhysicsEntity::update(deltaTime); 
}