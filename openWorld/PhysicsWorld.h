#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>

#include "includes/glm/glm.hpp"
#include "Includes/glm/gtc/type_ptr.hpp"
#include <glm/gtx/string_cast.hpp>

#include "renderer.h"

#include "RigidBody.h"
#include "orientedBoundingBox.h"
#include "raycast.h"

#ifndef PHYSICSWORLD_H
#define PHYSICSWORLD_H

class PhysicsWorld
{
public:

	PhysicsWorld();
	~PhysicsWorld();
 	
	void stepSimulation(float dt);

	void debugOBBs(renderer* gameRenderer);

	void debugRigidBodies(renderer* gameRenderer);

	unsigned int createRigidBody();

	void updateRigidBodyPosition(glm::vec3 newPos, glm::quat newOrient, unsigned int rigidBodyId);

	unsigned int createOBB(glm::vec3 halfExtents);

	void updateOBBtransform(glm::vec3 position, glm::quat orient, unsigned int OBBid);

	void rayCast(glm::vec3 pointA, glm::vec3 pointB);

private:

	void updateCollisions();

	unsigned int physicsWorldObjects = 0; //total number of objects in the world

	int numRigidBodies = 0;
	int numOBBs = 0;

	unsigned int getUniqueID();

	std::map <unsigned int, RigidBody> rigidBodies;
	std::unordered_map <unsigned int, orientedBoundingBox> OBBs;

	std::vector <unsigned int> OBBids; //for debugging
	std::vector <unsigned int> rigidBodyids; //also for debugging
	
};
#endif

//simulated/physics world needs:
//
// oriented Bounding Box collider representations
// collision algorythm for OBB vs OBB and OBB vs rayCast
// rayCast representations
// basic collision response (not looking for actual kinematic simulation yet just a response that means the player wont fall through the floor and cant walk through walls)
// damageRaycast representation
// damageOBB representation
// entity messaging system for damage response
// 
//