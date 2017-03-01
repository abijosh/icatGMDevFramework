#include "ContactListener.h"


ContactListener::ContactListener()
{
}


ContactListener::~ContactListener()
{
}

void ContactListener::BeginContact(b2Contact* contact){
	//check if fixture A was a PhysicsEntity
	void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
	if (bodyUserData)
		static_cast<PhysicsEntity*>(bodyUserData)->startContact();

	//check if fixture B was a PhysicsEntity
	bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
	if (bodyUserData)
		static_cast<PhysicsEntity*>(bodyUserData)->startContact();
}

void ContactListener::EndContact(b2Contact* contact){

	//check if fixture A was a PhysicsEntity
	void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
	if (bodyUserData)
		static_cast<PhysicsEntity*>(bodyUserData)->endContact();

	//check if fixture B was a PhysicsEntity
	bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
	if (bodyUserData)
		static_cast<PhysicsEntity*>(bodyUserData)->endContact();
}
