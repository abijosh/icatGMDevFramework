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

void Scene::erase(Entity* entity){
	auto it = std::find(entities.begin(), entities.end(), entity);
	if (it < entities.end()){
		entities.erase(it);
		//delete entity;
	}
}

