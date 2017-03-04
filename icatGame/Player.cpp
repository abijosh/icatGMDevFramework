#include "Player.h"


Player::Player(PhysicsEntity* physicsEntity, Weapon* weapon)
	:PhysicsEntity(*physicsEntity)
	, weapon(weapon)
{
	onAir = false;
	firing = false;
	speed = 250.0f;
	jumpStep = 0;
	direction = glm::vec3(0, 0, 0);
	addChild(this->weapon);
	physicsBody->SetUserData(this);
}


Player::~Player()
{
}

void Player::update(float deltaTime){
	onAir = physicsBody->GetLinearVelocity().y > 0;
	PhysicsEntity::update(deltaTime);
}

void Player::startContact(PhysicsEntity* other){
	if (other->getType() == Entity::PLATFORM && !onAir)
		jumpStep = 0;
}

void Player::endContact(PhysicsEntity* other){
}

void Player::moveLeft(float deltaTime){
	setScale(-1.0f, 1.0f);
	linearVelocity = physicsBody->GetLinearVelocity();
	linearVelocity.x = (-speed) * deltaTime;
	physicsBody->SetLinearVelocity(linearVelocity);
}

void Player::moveRight(float deltaTime){
	setScale(1.0f, 1.0f);
	linearVelocity = physicsBody->GetLinearVelocity();
	linearVelocity.x = speed * deltaTime;
	physicsBody->SetLinearVelocity(linearVelocity);
}

void Player::jump(float deltaTime){
	if (jumpStep > 8)
		return;
	float force = physicsBody->GetMass() * 16.0f;
	physicsBody->ApplyForce(b2Vec2(0, force), physicsBody->GetWorldCenter(), true);
	jumpStep++;
}

void Player::fire(b2World* physicsWorldPtr, Scene* scenePtr){
	firing = true;
	weapon->startFire(physicsWorldPtr, scenePtr, position, getScale().x);
}