#pragma once
#include "entity.h"
#include <Box2D\Box2D.h>

const auto physicsBodyCreator = [](float x, float y, float halfWidth, float halfHeight, 
	b2BodyType bodyType, b2World* physicsWorld, bool collidable) {

	b2BodyDef bodyDef;
	bodyDef.type = bodyType;
	bodyDef.position.Set(x, y);
	b2Body* physicsBody = physicsWorld->CreateBody(&bodyDef);

	b2PolygonShape boxShape;
	boxShape.SetAsBox(halfWidth, halfHeight);

	b2FixtureDef boxFixtureDef;
	boxFixtureDef.shape = &boxShape;
	boxFixtureDef.density = 1;
	if (!collidable)
		boxFixtureDef.filter.maskBits = 0x0000;

	physicsBody->CreateFixture(&boxFixtureDef);

	return physicsBody;
};

class PhysicsEntity : public Entity
{
public:
	PhysicsEntity(Entity* entity, b2Body* physicsBody);
	~PhysicsEntity();

	void updateTransformMatrix(){ int i = 0; }
	virtual void update(float deltaTime);

	virtual void startContact(PhysicsEntity* other){}
	virtual void endContact(PhysicsEntity* other){}

	b2Body* getPhysicsBody(){ return physicsBody; }

protected:
	b2Body* physicsBody;
};

