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

	glm::vec3 position;
	glm::vec3 velocity;

	float mass;

	void applyForce(const glm::vec3& force, float dt);

	void update(float dt);

private:

};

#endif