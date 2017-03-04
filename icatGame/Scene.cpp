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

void Scene::addDynamicEntity(Entity* entity){
	if (entity){
		dynamicEntities.push_back(entity);
		entities.push_back(entity);
	}
}

std::vector<Entity*>& Scene::getEntities()
{
	return entities;
}

std::vector<Entity*>& Scene::getDynamicEntities()
{
	return dynamicEntities;
}

void Scene::erase(Entity* entity){
	auto it = std::find(entities.begin(), entities.end(), entity);
	if (it < entities.end()){
		entities.erase(it);
		//delete entity;
	}
	it = std::find(dynamicEntities.begin(), dynamicEntities.end(), entity);
	if (it < dynamicEntities.end()){
		dynamicEntities.erase(it);
		//delete entity;
	}
}

