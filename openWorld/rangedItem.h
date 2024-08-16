#pragma once

#include <iostream>

#include "includes/glm/glm.hpp"
#include "includes/glm/gtc/type_ptr.hpp"
#include "includes/glm/gtc/quaternion.hpp"

#include "PhysicsWorld.h"

#ifndef RANGEDITEM_H
#define RANGEDITEM_H

class rangedItem
{
public:

	rangedItem(std::string uniqueId);
	~rangedItem();

	void setPosDirection(glm::vec3 position, glm::vec3 direction);

	void setDamageAmount(float amount);

	void setTotalCapacity(int newCap);

	void useItem(PhysicsWorld* world);

	void reloadItem(int amount);


private:
	//position of the object itself or where the projectile comes from
	glm::vec3 position;
	//direction the projectile travels in
	glm::vec3 direction;

	float damageAmount;

	int maxCapacity;
	int currentCapacity;

	std::string uniqueID;

	//PhysicsWorld* gameWorld; //for casting a damage ray into
};

#endif