#include <glm/glm.hpp>//graphics lib for mathematics
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <Box2D/Box2D.h>

#include "RawModel.h"
#include "Shader.h"
#include "Material.h"
#include "TexturedModel.h"

#pragma once
class Entity
{
public:
	Entity(TexturedModel *TexturedModelPtr
				 , glm::vec3 position = glm::vec3(0)
				 , glm::vec3 scale = glm::vec3(1)
				 , float rotateAngle = 0
				 , glm::vec3 rotateAxis = glm::vec3(0, 0, 1));
	~Entity();

	enum Type{
		NOT_SET, WALL, PLATFORM, BULLET, WEAPON, PLAYER, ENEMY, PORTAL, NUMTYPES
	};

	void setType(Type type){ entityType = type; }
	const Type& getType()const { return entityType; }

	virtual void update(float deltaTime);

	void updateTransformMatrix();

	void setBox2DReferences(b2Body* dynamicBody){
		position.x = dynamicBody->GetPosition().x;
		position.y = dynamicBody->GetPosition().y;
	}

	virtual void setPosition(float x, float y, float z){
		position.x = x;
		position.y = y;
		position.z = z;
		matrixUpdated = false;
	}
	virtual void setPosition(const glm::vec3 pos){
		position = pos;
		matrixUpdated = false;
	}
	glm::vec3& getPosition(){
		return position;
	}

    void setRotate(float angle){
        rotateAngle = angle;
        matrixUpdated = false;
    }

	virtual void rotate(float angle){
		rotateAngle += angle;
		if (rotateAngle >= 360)
			rotateAngle -= 360;
		matrixUpdated = false;
	}

	float getAngle(){
		return rotateAngle;
	}

	void scaleTo(float value){
		scale.x += value;
		scale.y += value;
		scale.z = 1;
		matrixUpdated = false;
	}

	void setScale(float value){
		scale = glm::vec3(value);
		scale.z = 1;
		matrixUpdated = false;
	}

	void setScale(float x, float y, float z = 1){
		scale.x = x;
		scale.y = y;
		scale.z = z;
		matrixUpdated = false;
	}

	glm::vec3 getScale(){
		return scale;
	}


    virtual bool isActive(){
        return active;
    }

    virtual void activate(glm::vec3 position){
		active = true;
        setPosition(position);
    }

	virtual void deactivate(){
		active = false;
	}

	void addChild(Entity* childEntity);
	const std::vector<Entity*>& getChildren()const;

	void setParent(Entity* parentEntity){ parent = parentEntity; }
	const Entity* getParent()const{ return parent; }

	void setTexturedModel(TexturedModel* TexturedModelPtr);

	TexturedModel* getModelPointer();
	glm::mat4& getTransformMatrix();

	void removeAfter(float time = 0.001f){ lifeRemaining = time; }
	bool isScheduledToBeRemoved(){ return scheduleToBeRemoved; }

protected:
	Type entityType;
	bool active;
	glm::vec3 position, scale, rotateAxis;
	float rotateAngle;
	bool matrixUpdated;

private:
	glm::mat4 transformMatrix;
	TexturedModel *pTexturedModel;

	std::vector<Entity*> children;
	Entity* parent;

	float lifeRemaining;
	bool scheduleToBeRemoved;
};