#pragma once
#include "entity.h"
#include <Box2D\Box2D.h>
class PhysicsEntity : public Entity
{
public:
	PhysicsEntity(Entity* entity, b2Body* physicsBody);
	~PhysicsEntity();

	void updateTransformMatrix(){ int i = 0; }
	virtual void update(float deltaTime);

protected:
	b2Body* physicsBody;
};

