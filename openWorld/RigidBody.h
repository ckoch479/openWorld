#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>

#include "includes/glm/glm.hpp"
#include "Includes/glm/gtc/type_ptr.hpp"

#include "orientedBoundingBox.h"

#ifndef RIGIDBODY_H
#define RIGIDBODY_H

enum bodyType
{
	STATIC, //doesnt move at all
	DYNAMIC, //moves based on preset or programmed movements (user controlled)
	KINEMATIC, //moves based on physics
};

class RigidBody
{
public:
	RigidBody();

	RigidBody(bodyType newType);

	~RigidBody();

	RigidBody(glm::vec3* newposition, glm::quat* neworientation, float newmass, bodyType newType);

	void updatePosition(float dt);

	glm::vec3* getPosition();

	glm::quat* getOrientation();

	void setPosition(glm::vec3* newPos);

	void setOrientation(glm::quat* newOrient);

	void applyForce(glm::vec3 newForce);

	void sleepObject();

	bodyType getBodyType();

	void addOBBtoBody(orientedBoundingBox* box, unsigned int boxId);

	void adjustOBBtoBody(glm::vec3 pos, glm::quat orient, unsigned int colliderID);

	//check if an oriented bounding box is contained within this rigid body
	bool OBBinBody(orientedBoundingBox* box);
	//check if an oriented bounding box is contained within this rigid body
	bool OBBinBody(unsigned int boxId);

private:

	glm::vec3 velocity;
	glm::vec3 acceleration;

	glm::vec3* position;
	glm::quat* orientation;

	glm::vec3 angularVelocity;
	glm::vec3 angularAcceleration;

	float mass;
	float coefficientFriction = 0.5; //defaults to 0.5 for kinematic objects

	bodyType type = STATIC;

	std::vector <orientedBoundingBox*> colliders;
	std::unordered_map<unsigned int, orientedBoundingBox*> boxIDmap;
	std::vector <unsigned int> colliderIds;

};

#endif