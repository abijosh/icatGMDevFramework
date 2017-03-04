#include "ExitPortal.h"


ExitPortal::ExitPortal(PhysicsEntity* physicsEntity, EntryPortal* entryPortal)
	:PhysicsEntity(*physicsEntity)
	, entryPortal(entryPortal)
{
	setType(Entity::PORTAL);
	physicsBody->SetUserData(this);
}


ExitPortal::~ExitPortal()
{
}

void ExitPortal::update(float deltaTime){
	if (enteredExit.size() > 0){
		for (Enemy* e : enteredExit)
			entryPortal->regenerate(e);
		enteredExit.clear();
	}
}

void ExitPortal::startContact(PhysicsEntity* other){
	if (other->getType() == Entity::ENEMY)
		enteredExit.push_back((Enemy*)other);
}