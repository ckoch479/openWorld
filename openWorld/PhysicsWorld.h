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

class PhysicsWorld
{
public:

	std::vector <RigidBody> rigidBodies;
	std::vector <Collider> colliders;

	physicsObject addPhysicsObject(RigidBody body, Collider collider);

	RigidBody* createRigidBody();

	Collider* createCollider(AABB collider);

	Collider* createCollider(CircleCollider collider);

	Collider* createCollider(Collider collider);

	void stepPhysicsSimulation(float dt);

private:
	//force calculation

	//collision detection

	//collision resolution


};

//physics simulation methods:
//Euler method
//Verlet integration 
//Runge-Kutta

#endif