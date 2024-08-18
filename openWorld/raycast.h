#pragma once

#include "includes/glm/glm.hpp"
#include "Includes/glm/gtc/type_ptr.hpp"
#include <glm/gtx/string_cast.hpp>

#include "orientedBoundingBox.h"

#ifndef RAYCAST_H
#define RAYCAST_H

class raycast
{
public:
	raycast(glm::vec3 pointa, glm::vec3 pointb);
	~raycast();

	//used by the physics world to add colliders this ray has collided with
	void addCollision(orientedBoundingBox* colliderBox);

	orientedBoundingBox* returnFirstCollision();

	std::vector <orientedBoundingBox*> returnAllCollisions();

	bool checkCollision(orientedBoundingBox* box);

private:

	glm::vec3 pointA;
	glm::vec3 pointB;

	//this is a vector of all colliders this raycast has came into contact with, the beginning of the vector is the first object collided with
	std::vector <orientedBoundingBox*> collidedBoxes; 

};

#endif