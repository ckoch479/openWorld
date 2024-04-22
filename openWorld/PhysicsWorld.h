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

struct AABBCollider
{
	glm::vec3 topA;
	glm::vec3 topB;
	glm::vec3 topC;
	glm::vec3 topD;

	glm::vec3 bottomA;
	glm::vec3 bottomB;
	glm::vec3 bottomC;
	glm::vec3 bottomD;
};

struct physicsObject
{
	ID rigidBodyID;
	//starting with simple AABB for testing
	AABBCollider objectCollider;
	RigidBody objectBody;

	std::vector <glm::vec3> forcesApplied;
	std::vector <glm::vec3> torqueApplied;

};

class PhysicsWorld
{
public:

	PhysicsWorld();
	~PhysicsWorld();

	lookup_table<RigidBody> rigidBodies;

	//physics world objects
	lookup_table <physicsObject> objects;

	ID createRigidBody(RigidBody body);

	ID createRigidBody(glm::vec3 position, glm::quat rotation, float mass);

	ID createPhysicsObject(std::vector <glm::vec3> &meshData, glm::vec3 startingPosition, glm::quat rotation);

	void deletePhysicsObject(ID objectID);

	void addTerrainMeshVertices(std::vector <glm::vec3> verts);

	//manipulate object------------------------------------------

	void applyForce(ID objectID,glm::vec3 force);

	void setPosition(ID bodyID, glm::vec3 position);

	void setRotation(ID bodyID, glm::quat rotation);

	



	//get data from object------------------------------------

	glm::vec3 getBodyPosition(ID bodyID);

	glm::quat getBodyOrientation(ID bodyID);
	
	

	void stepSimulation(float dt);

	std::vector <ID> objectIDs;
	int numObjects = 0;
	

private:

	//dynamics

	//collision resolution

	float physicsWorldObjects = 0;
	float numRigidBodies = 0;

	std::vector <ID> worldObjectIDs;

	std::vector <glm::vec3> WorldMeshVertices; //Vertices for the worlds mesh for ground based collision detection
	std::map <float, std::map<float, float>> XZtable;

	AABBCollider calculateAABBFromMeshData(std::vector <glm::vec3>& meshData);
};

//physics simulation methods:
//Euler method
//Verlet integration 
//Runge-Kutta

// new physics world ideas
// 
// add game map into physics world to start as a ground mesh with collision detection/resolution
// 
// 
//

#endif