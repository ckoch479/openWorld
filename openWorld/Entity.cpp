#include "Entity.h"

Entity::Entity()
{

}

Entity::~Entity()
{

}

//update will update the entity state (could be rendering, animation, simulation, health, ect)
void Entity::update(float dt)
{

}

glm::vec3* Entity::getPosition()
{
	return &this->position;
}

glm::quat* Entity::getOrient()
{
	return &this->orientation;
}

glm::vec3* Entity::getScale()
{
	return &this->scale;
}

void Entity::setTransform(glm::vec3 pos, glm::quat orient, glm::vec3 scale)
{
	this->position = pos;
	this->orientation = orient;
	this->scale = scale;
}

void Entity::setPos(glm::vec3 pos)
{
	this->position = pos;
}

void Entity::setOrient(glm::quat orient)
{
	this->orientation = orient;
}

std::string Entity::getName()
{
	return this->entityName;
}