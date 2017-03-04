#pragma once
#include "PhysicsEntity.h"
#include "EntryPortal.h"
#include "Enemy.h"
class ExitPortal : public PhysicsEntity
{
public:
	ExitPortal(PhysicsEntity* physicsEntity, EntryPortal* entryPortal);
	~ExitPortal();
	
	void update(float deltaTime);

	void startContact(PhysicsEntity* other);
	void endContact(PhysicsEntity* other){}

private:
	EntryPortal* entryPortal;
	std::vector<Enemy*> enteredExit;
};

