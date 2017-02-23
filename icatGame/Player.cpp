#include "Player.h"


Player::Player(PhysicsEntity* physicsEntity, Weapon* weapon)
	:PhysicsEntity(*physicsEntity)
	, weapon(weapon)
{
	speed = 500.0f;
	jumpStep = 0;
	direction = glm::vec3(0, 0, 0);
	addChild(this->weapon);
	physicsBody->SetUserData(this);
}


Player::~Player()
{
}

void Player::update(float deltaTime){
	PhysicsEntity::update(deltaTime);
}

void Player::moveLeft(float deltaTime){

	linearVelocity = physicsBody->GetLinearVelocity();
	linearVelocity.x = (-speed) * deltaTime;
	physicsBody->SetLinearVelocity(linearVelocity);
}

void Player::moveRight(float deltaTime){

	linearVelocity = physicsBody->GetLinearVelocity();
	linearVelocity.x = speed * deltaTime;
	physicsBody->SetLinearVelocity(linearVelocity);
}

void Player::jump(float deltaTime){
	float force = physicsBody->GetMass() * 16.0f;
	std::cout << force << std::endl;
	physicsBody->ApplyForce(b2Vec2(0, force), physicsBody->GetWorldCenter(), true);
}

void Player::fire(b2World* physicsWorldPtr, Scene* scenePtr){
	weapon->fire(physicsWorldPtr, scenePtr, position);
}