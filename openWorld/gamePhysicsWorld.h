#pragma once

#include "includes/glm/glm.hpp"
#include "Includes/glm/gtc/type_ptr.hpp"


#include <iostream>
#include <vector>
#include <unordered_map>

#include "renderingInfoDefinitions.h"

#ifndef GAMEPHYSICSWORLD_H
#define GAMEPHYSICSWORLD_H

struct physObject
{
	float mass;
	transform currentTransf;
	glm::vec3 velocity;
};


class gamePhysicsWorld
{
public:

	gamePhysicsWorld();
	~gamePhysicsWorld();


private:

	std::unordered_map<std::string, physObject> physicsObjects;

};

#endif // !GAMEPHYSICSWORLD_H