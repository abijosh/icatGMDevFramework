#pragma once
#include "PhysicsEntity.h"
#include "Ammo.h"
class Weapon : public PhysicsEntity
{
public:
	Weapon(PhysicsEntity* physicsEntity, Ammo* ammo);
	~Weapon();

	void fire();
};

