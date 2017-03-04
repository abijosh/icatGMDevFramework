#include "Enemy.h"
auto randNegate = [](float x){int i = rand() % 2; i == 0 ? x : x *= -1; return x; };
/*add dynamic list
enemy update - dont call base update

enemy direction - dont check for wall
*/
Enemy::Enemy(PhysicsEntity* physicsEntity, float health, float healthIncreaseFactor)
	:PhysicsEntity(*physicsEntity)
	, health(health)
	, healthIncreaseFactor(healthIncreaseFactor)
{
	setType(ENEMY);
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

void Enemy::setPosition(const glm::vec3 pos){
	Entity::setPosition(pos);
	physicsBody->SetTransform(b2Vec2(pos.x, pos.y), 0.0f);
}

void Enemy::setDirAndVel(){
	b2Vec2 currPos = physicsBody->GetPosition();
	b2Vec2 distTravelled = prevPos - currPos;
	prevPos = currPos;
	if (distTravelled.Length() < 0.1f){
		b2Vec2 vel = physicsBody->GetLinearVelocity();
		direction *= -1;
	}
	else
		b2Vec2 vel = physicsBody->GetLinearVelocity();


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

void Enemy::regen(const glm::vec3 pos, float health){
	physicsBody->SetTransform(b2Vec2(pos.x, pos.y), physicsBody->GetAngle());
	physicsBody->SetGravityScale(1.0f);
	this->health = health;
}

void Enemy::setOffScreen(){
	physicsBody->SetTransform(b2Vec2(90, 150), physicsBody->GetAngle());
	physicsBody->SetGravityScale(0.0f);
}