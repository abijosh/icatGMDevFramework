#include "Scene.h"


Scene::Scene()
{
}

Scene::~Scene()
{
	for (Entity* e : entities)
		delete e;
}

void Scene::addEntity(Entity* Entity)
{
	entities.push_back(Entity);
}

std::vector<Entity*>& Scene::getEntities()
{
	return entities;
}


