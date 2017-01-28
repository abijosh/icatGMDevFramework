#pragma once
#include "Entity.h"
class Scene 
{
public:
	Scene();
	~Scene();

	void addEntity(Entity* Entity);
	std::vector<Entity*>& getEntities();
	TexturedModel* getModelPointer(){
		return pTexturedModel;
	}

private:
	std::vector<Entity*> entities;
	TexturedModel *pTexturedModel;
};

