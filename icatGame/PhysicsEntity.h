#pragma once
#include "entity.h"
#include <Box2D\Box2D.h>
class PhysicsEntity : public Entity
{
public:
	PhysicsEntity(Entity* entity, b2Body* physicsBody);
	~PhysicsEntity();

	virtual void update(float deltaTime);

private:
	b2Body* physicsBody;
};

