#pragma once
#include "PhysicsEntity.h"
#include "Enemy.h"
class Portal : public PhysicsEntity
{
public:
	Portal(PhysicsEntity* physicsEntity);
	~Portal();
};

