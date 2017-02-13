#include "Header.h"



PhysicsEntity::PhysicsEntity(Entity* entity, b2Body* physicsBody)
	:Entity(*entity)
	, physicsBody(physicsBody)
{
}


PhysicsEntity::~PhysicsEntity()
{
}

void PhysicsEntity::update(float deltaTime){
	if (physicsBody->GetType() == b2_dynamicBody){
		b2Vec2 b2dPos = physicsBody->GetPosition();
		setPosition(b2dPos.x, b2dPos.y, 0.0f);
	}
}