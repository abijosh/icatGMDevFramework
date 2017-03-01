#include "Weapon.h"


Weapon::Weapon(PhysicsEntity* physicsEntity, AmmoData ammoData)
	:PhysicsEntity(*physicsEntity)
	, ammoData(ammoData)
{
}


Weapon::~Weapon()
{
}


void Weapon::fire(b2World* physicsWorldPtr, Scene* scenePtr, 
	glm::vec3 playerPosition, float playerDirection){
	b2Vec2 ammoPosition(playerPosition.x + (playerDirection * (position.x + ammoData.x)),
		playerPosition.y + position.y + ammoData.y);
	b2BodyDef bodyDef;
	bodyDef.type = ammoData.bodyType;
	bodyDef.position.Set(ammoPosition.x, ammoPosition.y);
	b2Body* physicsBody = physicsWorldPtr->CreateBody(&bodyDef);

	b2PolygonShape boxShape;
	boxShape.SetAsBox(ammoData.halfWidth, ammoData.halfHeight);

	b2FixtureDef boxFixtureDef;
	boxFixtureDef.shape = &boxShape;
	boxFixtureDef.density = 1;

	physicsBody->CreateFixture(&boxFixtureDef);
	physicsBody->SetLinearVelocity(b2Vec2(200, 0));
	physicsBody->SetGravityScale(0);
	b2Vec2 currBulletVelocity = ammoData.velocity;
	currBulletVelocity.x *= playerDirection;
	scenePtr->addEntity(new Ammo(new PhysicsEntity(ammoData.entity, physicsBody), currBulletVelocity));
}