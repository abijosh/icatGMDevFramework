#pragma once
#include "Entity.h"
class Scene 
{
public:
	Scene();
	~Scene();

	void addEntity(Entity* entity);
	std::vector<Entity*>& getEntities();
	void erase(Entity* entity);

private:
	std::vector<Entity*> entities;
};

