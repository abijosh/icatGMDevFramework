#pragma once
#include "entity.h"
#include <Box2D\Box2D.h>
class PhysicsEntity
{
public:
	PhysicsEntity(Entity* entity, b2Body* physicsBody);
	~PhysicsEntity();
};

