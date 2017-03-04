#include "Header.h"


Entity::Entity(TexturedModel *TexturedModelPtr,
						   glm::vec3 position,
						   glm::vec3 scale,
						   float rotateAngle,
						   glm::vec3 rotateAxis)
		: pTexturedModel(TexturedModelPtr)
		, position(position)
		, scale(scale)
		, rotateAngle(rotateAngle)
		, rotateAxis(rotateAxis)
{
	entityType = NOT_SET;
	parent = nullptr;
	matrixUpdated = false;
    active = true;
	lifeRemaining = -1.0f;
	scheduleToBeRemoved = false;
}


Entity::~Entity()
{
	delete pTexturedModel;
}

void Entity::update(float deltaTime){
	if (lifeRemaining > 0){
		lifeRemaining -= deltaTime;
		if (lifeRemaining < 0){
			scheduleToBeRemoved = true;
		}
	}

	for (Entity* child : children)child->update(deltaTime);
}

void Entity::updateTransformMatrix() {
	glm::mat4 referenceMatrix(1.0f);
	if (parent)
		referenceMatrix = parent->getTransformMatrix();
	referenceMatrix = glm::translate(referenceMatrix, position);
	referenceMatrix = glm::scale(referenceMatrix, scale);
	transformMatrix = glm::rotate(referenceMatrix, glm::radians(rotateAngle), rotateAxis);
	matrixUpdated = true;
}

glm::mat4& Entity::getTransformMatrix(){
	if (!matrixUpdated){
		updateTransformMatrix();
		for (Entity* child : children)
			child->updateTransformMatrix();
	}
	return transformMatrix;
}

TexturedModel* Entity::getModelPointer(){
	return pTexturedModel;
}

void Entity::setTexturedModel(TexturedModel* TexturedModelPtr){	
	this->pTexturedModel = TexturedModelPtr;
}

void  Entity::addChild(Entity* childEntity)
{
	children.push_back(childEntity);
	childEntity->setParent(this);
}
const std::vector<Entity*>&  Entity::getChildren() const
{
	return children;
}
