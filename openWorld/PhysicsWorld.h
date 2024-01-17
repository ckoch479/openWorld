#pragma once

#include <iostream>
#include <vector>
#include <map>

#include "lookup_table.h"

#include "includes/glm/glm.hpp"
#include "Includes/glm/gtc/type_ptr.hpp"

#include "Collider.h"
#include "RigidBody.h"

#ifndef PHYSICSWORLD_H
#define PHYSICSWORLD_H

struct physicsObject
{
	ID rigidBodyID;
	std::vector <ID> colliderIDs;
	sphereCollider broadCollisionCollider; //collider will be a sphere collider for ease of use and calculation
};

struct Force
{
	glm::vec3 direction;
	float magnitude;
};

class PhysicsWorld
{
public:

	lookup_table<RigidBody> rigidBodies;
	lookup_table<Collider> colliders;
	std::vector <Collider> broadPhaseColliders; //large AABB that fully contains all colliders in each physics object

	std::vector <physicsObject> objects;

	void stepSimulation(float dt);

	physicsObject* createPhysicsObject(RigidBody body, std::vector <Collider> colliders);

	void deletePhysicsObject(physicsObject* object);

private:

	//broad phase collider is generated based on the colliders in an object
	sphereCollider generateBroadPhaseCollider(physicsObject object);
	//dynamics

	void eulerIntergration(physicsObject& object, Force& force, float dt);

	//collision detection

	std::vector<physicsObject*> createPossibleCollisions(physicsObject* currentObject);

	bool checkCollision(physicsObject* objectA, physicsObject* objectB);

	//collision resolution

	float physicsWorldObjects = 0;
	float numRigidBodies = 0;
	float numColliders = 0;
	float numBroadPhaseColliders = 0;

	//utility functions

	float findDistance(glm::vec3 pointA, glm::vec3 pointB);

};

//physics simulation methods:
//Euler method
//Verlet integration 
//Runge-Kutta

#endif