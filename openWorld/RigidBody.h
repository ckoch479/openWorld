#pragma once

#include <iostream>
#include <vector>
#include <map>

#include "includes/glm/glm.hpp"
#include "Includes/glm/gtc/type_ptr.hpp"

#ifndef RIGIDBODY_H
#define RIGIDBODY_H
class RigidBody
{
public:

	RigidBody();
	~RigidBody();

	glm::vec3 position;
	glm::vec3 velocity;
	glm::vec3 acceleration;

	glm::quat orientation;

	glm::vec3 angularVelocity;
	glm::vec3 angularAcceleration;
	glm::vec3 momentOfInteria;

	float mass;

	float coefficientFriction;

	//intertia tensor?
	//force accumulator?
	// torque accumulator?
	//material properties (friction, restitution)
	//sleeping
	//user interface hooks I.E. player controlling movement

	void createRigidBody(glm::vec3 newposition, glm::quat neworientation, float newmass);

	void updatePosition(float dt);

	void applyForce(glm::vec3 newForce);

	void sleepObject();

private:

};

#endif