#pragma once

#include <iostream>

#include "includes/glm/glm.hpp"
#include "includes/glm/gtc/type_ptr.hpp"
#include "includes/glm/gtc/quaternion.hpp"

#include "PhysicsWorld.h"

#ifndef MELEE_H
#define MELEE_H

class melee
{
public:

	melee(std::string uniqueId);

	~melee();

	void use();


private:

	//damageOBB (still needs to be implimented)

	PhysicsWorld* gameWorld;
	//requires an attached is collidable object
	
	//this tells if the item can actually apply damage currently so sheathed or stationary weapons cannot do damage to entities
	bool damageActive;

	float damageAmount;
	std::string uniqueID;
};

#endif