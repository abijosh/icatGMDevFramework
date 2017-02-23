#include "Ammo.h"


Ammo::Ammo(PhysicsEntity* physicsEntity, b2Vec2 velocity)
	:PhysicsEntity(*physicsEntity)
	, velocity(velocity)
{
	physicsBody->SetUserData(this);
}


Ammo::~Ammo()
{
}

void Ammo::update(float deltaTime){
	physicsBody->SetLinearVelocity(velocity);
	PhysicsEntity::update(deltaTime); 
}

void Ammo::startContact(){
	velocity.x = 0;
	physicsBody->SetGravityScale(1.0f);
}

void Ammo::endContact(){

}