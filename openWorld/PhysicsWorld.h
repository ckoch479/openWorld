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
	//std::vector <ID> colliderIDs;
	//sphereCollider broadCollisionCollider; //collider will be a sphere collider for ease of use and calculation
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

	ID createRigidBody(glm::vec3 position, float rotation, glm::vec3 rotationOrigin, float mass);

	ID createPhysicsObject(ID rigidBodyID); //Add collision ID as a parameter later

	ID createPhysicsObject(RigidBody* body, std::vector <orientedBoundingBox> colliders);

	void deletePhysicsObject(ID objectID);

	//manipulate object------------------------------------------

	void applyForce(ID bodyID,glm::vec3 force);

	void setPosition(ID bodyID, glm::vec3 position);

	void setRotation(ID bodyID, float rotation);

	void setRotationOrigin(ID bodyID, glm::vec3 origin);



	//get data from object------------------------------------

	glm::vec3 getBodyPosition(ID bodyID);

	float getBodyOrientation(ID bodyID);
	
	glm::vec3 getBodyRotationOrigin(ID bodyID);

	void stepSimulation(float dt);

private:

	//dynamics

	//collision resolution

	float physicsWorldObjects = 0;
	float numRigidBodies = 0;
	std::vector <ID> worldObjectIDs;

};

//physics simulation methods:
//Euler method
//Verlet integration 
//Runge-Kutta

#endif