#include "Scene.h"


Scene::Scene()
{
}

Scene::~Scene()
{
	for (Entity* e : entities)
		delete e;
}

void Scene::addEntity(Entity* entity)
{
	if (entity)
		entities.push_back(entity);
}

std::vector<Entity*>& Scene::getEntities()
{
	return entities;
}


