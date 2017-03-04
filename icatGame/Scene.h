#pragma once
#include "Entity.h"
class Scene 
{
public:
	Scene();
	~Scene();

	void addEntity(Entity* entity);
	void addDynamicEntity(Entity* entity);
	std::vector<Entity*>& getEntities();
	std::vector<Entity*>& getDynamicEntities();
	void erase(Entity* entity);

private:
	std::vector<Entity*> entities, dynamicEntities;
};

