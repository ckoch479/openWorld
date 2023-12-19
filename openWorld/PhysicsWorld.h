#pragma once

#include <iostream>
#include <vector>
#include <map>

#include "includes/glm/glm.hpp"
#include "Includes/glm/gtc/type_ptr.hpp"

#include "Collider.h"
#include "RigidBody.h"

#ifndef PHYSICSWORLD_H
#define PHYSICSWORLD_H

struct physicsObject
{
	RigidBody* body;
	Collider* collider;
};

struct Force
{
	glm::vec3 direction;
	float magnitude;
};

class PhysicsWorld
{
public:

	std::vector <RigidBody> rigidBodies;
	std::vector <Collider> colliders;

	std::vector <physicsObject> objects;

	physicsObject* addPhysicsObject(RigidBody body, Collider collider);

	RigidBody* createRigidBody(glm::vec3 Positon, glm::vec3 velocity, float mass);

	Collider* createCollider(AABB collider);

	//Collider* createCollider(CircleCollider collider);

	//Collider* createCollider(Collider collider);

	void stepPhysicsSimulation(float dt);

private:
	//dynamics

	void eulerIntergration(physicsObject& object, Force& force, float dt);

	//collision detection

	//collision resolution


};

//physics simulation methods:
//Euler method
//Verlet integration 
//Runge-Kutta

#endif