#include "Weapon.h"


Weapon::Weapon(PhysicsEntity* physicsEntity, AmmoData ammoData)
	:PhysicsEntity(*physicsEntity)
	, ammoData(ammoData)
{
	physicsBody->SetUserData(this);
}

Weapon::~Weapon()
{
}

void Weapon::startFire(b2World* physicsWorldPtr, Scene* scenePtr, 
	glm::vec3 playerPosition, float playerDirection){
	if (currentRound < maxRoundsPerFiring){
		currentRound++;
		b2Vec2 ammoPosition(playerPosition.x + (playerDirection * (position.x + ammoData.x)),
			playerPosition.y + position.y + ammoData.y);

		physicsBody = physicsBodyCreator(ammoPosition.x, ammoPosition.y, ammoData.halfWidth, ammoData.halfHeight
			, ammoData.bodyType, physicsWorldPtr, true);

		physicsBody->SetGravityScale(0);

		b2Vec2 currBulletVelocity = ammoData.velocity;
		currBulletVelocity.x *= playerDirection;
		scenePtr->addDynamicEntity(new Ammo(new PhysicsEntity(ammoData.entity, physicsBody), currBulletVelocity, ammoData.damage, ammoData.hitForce));
	}
}