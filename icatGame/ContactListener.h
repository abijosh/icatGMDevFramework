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

private:
	bool inside(b2Vec2 cp1, b2Vec2 cp2, b2Vec2 p);
	b2Vec2 intersection(b2Vec2 cp1, b2Vec2 cp2, b2Vec2 s, b2Vec2 e);
	bool findIntersectionOfFixtures(b2Fixture* fA, b2Fixture* fB, std::vector<b2Vec2>& outputVertices);
};

