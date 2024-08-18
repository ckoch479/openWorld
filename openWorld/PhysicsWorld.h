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

#include "Collider.h"

#ifndef PHYSICSWORLD_H
#define PHYSICSWORLD_H

struct collisionData
{
	Collider* collA;
	Collider* collB;
	std::vector <glm::vec3> contactPoints;
	glm::vec3 contactNormal;
};

class PhysicsWorld
{
public:

	PhysicsWorld();
	~PhysicsWorld();
 	
	void stepSimulation(float dt);

	void debugOBBs(renderer* gameRenderer);

	void debugRigidBodies(renderer* gameRenderer);

	unsigned int createRigidBody(glm::vec3* newposition, glm::quat* neworientation, float newmass, bodyType newType);

	void updateRigidBodyPosition(glm::vec3* newPos, glm::quat* newOrient, unsigned int rigidBodyId);

	void attachOBBtoRigidBody(unsigned int colliderID, unsigned int rigidBodyId);

	unsigned int attachOBBtoRigidBody(glm::vec3 halfExtents, unsigned int rigidBodyId);

	void adjustOBBtoRigidBody(glm::vec3 pos, glm::quat orient, unsigned int colliderID, unsigned int rigidBodyId);

	unsigned int createOBB(glm::vec3 halfExtents);

	void updateOBBtransform(glm::vec3 position, glm::quat orient, unsigned int OBBid);

	void rayCast(glm::vec3 pointA, glm::vec3 pointB);

private:

	void updateCollisions();

	void solveCollisions();

	//check collision between two oriented bounding boxes
	void checkCollision(orientedBoundingBox* A, orientedBoundingBox* B);

	//check collision between a ray cast and an oriented bounding box
	void checkCollision(raycast* ray, orientedBoundingBox* box);

	unsigned int physicsWorldObjects = 0; //total number of objects in the world

	int numRigidBodies = 0;
	int numOBBs = 0;

	unsigned int getUniqueID();

	std::map <unsigned int, RigidBody> rigidBodies;
	std::unordered_map <unsigned int, orientedBoundingBox> OBBs;

	std::vector <collisionData> collisions;

	std::vector <unsigned int> OBBids; //for debugging
	std::vector <unsigned int> rigidBodyids; //also for debugging

	//rays cast into the world
	std::vector <raycast> worldRays; 
	
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