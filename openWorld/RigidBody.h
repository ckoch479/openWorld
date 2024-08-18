#pragma once

#include <iostream>
#include <vector>
#include <map>

#include "includes/glm/glm.hpp"
#include "Includes/glm/gtc/type_ptr.hpp"

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

	RigidBody(bodyType newType);

	~RigidBody();

	void createRigidBody(glm::vec3 newposition, glm::quat neworientation, float newmass);

	void updatePosition(float dt);

	void applyForce(glm::vec3 newForce);

	void sleepObject();

	bodyType getBodyType();

private:

	glm::vec3 velocity;
	glm::vec3 acceleration;

	glm::vec3 position;
	glm::quat orientation;

	glm::vec3 angularVelocity;
	glm::vec3 angularAcceleration;

	float mass;
	float coefficientFriction;

	bodyType type;

};

#endif