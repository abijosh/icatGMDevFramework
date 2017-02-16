#include "Player.h"


Player::Player(PhysicsEntity* physicsEntity, Weapon* weapon)
	:PhysicsEntity(*physicsEntity)
	, weapon(weapon)
{
	speed = 1000.0f;
	direction = glm::vec3(0, 0, 0);
	addChild(this->weapon);
}


Player::~Player()
{
}

void Player::update(float deltaTime){
	updateKeyEvents(deltaTime);
	updateMouseEvents(deltaTime);

	currLinearVel = physicsBody->GetLinearVelocity();
	currLinearVel += linearVelocity;
	physicsBody->SetLinearVelocity(currLinearVel);
	PhysicsEntity::update(deltaTime);
}

void Player::updateMouseEvents(float deltaTime){
	if (UserInteraction::mouseLeftButtonDown){
		weapon->fire();
	}
}

void Player::updateKeyEvents(float deltaTime){
	if (UserInteraction::changed){
		direction.x = 0; direction.y = 0;
		if (UserInteraction::left)
			direction.x = -1;
		if (UserInteraction::right)
			direction.x = 1;
		if (UserInteraction::space && currLinearVel.y <= 0.0f)
			direction.y = 1;
		// linear velocity
		linearVelocity.x = direction.x * speed * deltaTime;
		linearVelocity.y = direction.y * speed * deltaTime;


		UserInteraction::changed = false;
	}
}