#include "PhysicsWorld.h"

PhysicsWorld::PhysicsWorld()
{
	
}

PhysicsWorld::~PhysicsWorld()
{
	
}

void PhysicsWorld::stepSimulation(float dt)
{
	
}

unsigned int PhysicsWorld::getUniqueID()
{
	this->physicsWorldObjects++;
	return this->physicsWorldObjects;
}

void PhysicsWorld::debugOBBs(renderer* gameRenderer)
{
	for(unsigned int i = 0; i < this->OBBids.size(); i++)
	{
		orientedBoundingBox* box = &this->OBBs[OBBids[i]];
		gameRenderer->addCube(box->returnPosition(), box->returnOrientation(), box->returnHalfExtents(), glm::vec4(1.0f, 0.0, 0.0, 0.9));
	}
}

void PhysicsWorld::debugRigidBodies(renderer* gameRenderer)
{
	//do later
}

unsigned int PhysicsWorld::createRigidBody()
{
	return 0;
}

void PhysicsWorld::updateRigidBodyPosition(glm::vec3 newPos, glm::quat newOrient, unsigned int rigidBodyId)
{

}

unsigned int PhysicsWorld::createOBB(glm::vec3 halfExtents)
{
	unsigned int newID = this->getUniqueID();
	this->OBBs[newID] = *new orientedBoundingBox(halfExtents);
	this->OBBs[newID].updateTransform(glm::vec3(0.0f), glm::quat(1.0f, 0.0, 0.0, 0.0));
	this->OBBids.push_back(newID);
	return newID;
}

void PhysicsWorld::updateOBBtransform(glm::vec3 position, glm::quat orient, unsigned int OBBid)
{
	orientedBoundingBox* box = &this->OBBs[OBBid];
	box->updateTransform(position, orient);
}

