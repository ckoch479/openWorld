#pragma once

#include <iostream>

#include "includes/glm/glm.hpp"
#include "Includes/glm/gtc/type_ptr.hpp"
#include <glm/gtx/string_cast.hpp>

#include "debugger.h"

#ifndef ENTITY_H
#define ENTITY_H

class Entity
{
public:
	
	//a name will need to be assigned to all entities however does not need to be assigned upon creation can be added later
	Entity(std::string name) { this->entityName = name; }
	
	Entity();

	~Entity();

	//update will update the entity state (could be rendering, animation, simulation, health, ect)
	virtual void update(float dt);

	 glm::vec3* getPosition();

	 glm::quat* getOrient();

	 glm::vec3* getScale();

	 void setTransform(glm::vec3 pos, glm::quat orient, glm::vec3 scale);

	 void setPos(glm::vec3 pos);

	 void setOrient(glm::quat orient);

	std::string getName();


protected:

	//all game Entities are required to have a position, orientation, and scale
	glm::vec3 position = glm::vec3(0.0f);
	glm::quat orientation = glm::quat(1.0, 0.0, 0.0, 0.0);
	glm::vec3 scale = glm::vec3(1.0f);

	glm::vec3 front = glm::vec3(0,0,1);
	glm::vec3 right = glm::vec3(-1,0,0);
	glm::vec3 up = glm::vec3(0,1,0);

	std::string entityName;

private:

	
	
};

#endif