#pragma once
#include <Box2D\Box2D.h>
#include "Entity.h"
#include "PhysicsEntity.h"
#include "Player.h"
#include "Ammo.h"

class ContactListener : public b2ContactListener
{
public:
	ContactListener();
	~ContactListener();

	// Called when two fixtures begin to touch
	void BeginContact(b2Contact* contact);

	// Called when two fixtures cease to touch
	void EndContact(b2Contact* contact);
};

