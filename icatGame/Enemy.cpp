#include "Enemy.h"
auto randNegate = [](float x){int i = rand() % 2; i == 0 ? x : x *= -1; return x; };
/*add dynamic list
enemy update - dont call base update

enemy direction - dont check for wall
*/
Enemy::Enemy(PhysicsEntity* physicsEntity, float health)
	:PhysicsEntity(*physicsEntity)
	, health(health)
{
	physicsBody->SetUserData(this);
	prevPos = physicsBody->GetPosition();
	direction = randNegate(1);
	hit = false;
}


Enemy::~Enemy()
{
}

void Enemy::update(float timeDelta){
	setDirAndVel();
	PhysicsEntity::update(timeDelta);
}

void Enemy::setDirAndVel(){
	b2Vec2 currPos = physicsBody->GetPosition();
	b2Vec2 distTravelled = prevPos - currPos;
	prevPos = currPos;
	if (distTravelled.Length() < 0.1f){
		direction *= -1;
	}

	b2Vec2 linearVel = physicsBody->GetLinearVelocity();
	linearVel.x = direction;
	physicsBody->SetLinearVelocity(linearVel);
}

void Enemy::startContact(PhysicsEntity* other){
	if (other->getType() == Entity::BULLET && !hit){
		getHit((Ammo*)other);
	}
	if (contactRegister != 0)
		return;
	if (other->getType() == Entity::WALL || other->getType() == Entity::ENEMY){
		direction *= -1;
		contactRegister++;
	}
	/*if (other->getType() == Entity::ENEMY){
		direction = ((Enemy*)other)->getDirection();
		contactRegister++;
	}*/
	setScale(direction, 1);
}

void Enemy::endContact(PhysicsEntity* other){
	if (other->getType() == Entity::WALL || other->getType() == Entity::ENEMY){
		contactRegister--;
	}
}

void Enemy::getHit(Ammo* ammo){
	health -= ammo->getDamage();
	b2Vec2 ammoVel = ammo->getPhysicsBody()->GetLinearVelocity();
	ammoVel.x *= ammo->getHitForce();
	physicsBody->ApplyForceToCenter(ammoVel, true);
	if (health < 0)
		kill(ammo);
}

void Enemy::kill(Ammo* ammo){
	hit = true;
	removeAfter(0.2f);
	b2Vec2 hitDir = ammo->getPhysicsBody()->GetLinearVelocity();
	hitForce = ammo->getHitForce();
	hitForce *= hitDir.x * -1;
	physicsBody->SetGravityScale(0.6f);
	physicsBody->ApplyAngularImpulse(hitForce, true);
}