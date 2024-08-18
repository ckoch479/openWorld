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

	for (unsigned int i = 0; i < this->rigidBodyids.size(); i++)
	{
		RigidBody* body = &this->rigidBodies[rigidBodyids[i]];
		gameRenderer->addCube(*body->getPosition(), *body->getOrientation(), glm::vec3(0.2,0.2,0.2), glm::vec4(1.0f, 0.0, 1.0, 0.9));
	}
}

unsigned int PhysicsWorld::createRigidBody(glm::vec3* newposition, glm::quat* neworientation, float newmass, bodyType newType)
{
	unsigned int newId = getUniqueID();

	RigidBody newBody = *new RigidBody(newposition,neworientation,newmass,newType);
	
	this->rigidBodies[newId] = newBody;
	this->rigidBodyids.push_back(newId);

	this->numRigidBodies++;

	return 0;
}

void PhysicsWorld::updateRigidBodyPosition(glm::vec3* newPos, glm::quat* newOrient, unsigned int rigidBodyId)
{
	this->rigidBodies[rigidBodyId].setPosition(newPos);
	this->rigidBodies[rigidBodyId].setOrientation(newOrient);
}

void PhysicsWorld::attachOBBtoRigidBody(unsigned int colliderID, unsigned int rigidBodyId)
{
	RigidBody* currentBody = &this->rigidBodies[rigidBodyId];
	if(currentBody)
	{
		orientedBoundingBox* newBox = &this->OBBs[colliderID];
		if(newBox)
		{
			currentBody->addOBBtoBody(newBox, colliderID);
		}
		else
		{
			std::cout << "ERROR::NO::COLLIDER::FOUND::WITH::GIVEN::ID::" << colliderID << std::endl;
		}
		
	}
	else
	{
		std::cout << "ERROR::NO::RIGIDBODY::FOUND::WITH::GIVEN::ID::" << rigidBodyId << std::endl;
	}
}

unsigned int PhysicsWorld::attachOBBtoRigidBody(glm::vec3 halfExtents, unsigned int rigidBodyId)
{
	unsigned int colldierId = 0;
	RigidBody* currentBody = &this->rigidBodies[rigidBodyId];
	if (currentBody)
	{
		colldierId = this->createOBB(halfExtents);
		
		orientedBoundingBox* newBox = &this->OBBs[colldierId];
		if (newBox)
		{
			currentBody->addOBBtoBody(newBox, colldierId);
		}
	}
	else
	{
		std::cout << "ERROR::NO::RIGIDBODY::FOUND::WITH::GIVEN::ID::" << rigidBodyId << std::endl;
	}
	return colldierId;
}

void PhysicsWorld::adjustOBBtoRigidBody(glm::vec3 pos, glm::quat orient, unsigned int colliderID, unsigned int rigidBodyId)
{

}

unsigned int PhysicsWorld::createOBB(glm::vec3 halfExtents)
{
	unsigned int newID = this->getUniqueID();
	this->OBBs[newID] = *new orientedBoundingBox(halfExtents);
	this->OBBs[newID].updateTransform(glm::vec3(0.0f), glm::quat(1.0f, 0.0, 0.0, 0.0));
	this->OBBids.push_back(newID);
	this->numOBBs++;
	return newID;
}

void PhysicsWorld::updateOBBtransform(glm::vec3 position, glm::quat orient, unsigned int OBBid)
{
	orientedBoundingBox* box = &this->OBBs[OBBid];
	box->updateTransform(position, orient);
}

void PhysicsWorld::rayCast(glm::vec3 pointA, glm::vec3 pointB)
{

}

void PhysicsWorld::updateCollisions()
{

}

void PhysicsWorld::solveCollisions()
{
	std::vector <collisionData> possibleCollisions;

	//iterate through all OBBs and map possible collisions
	for(unsigned int i = 0; i < this->OBBs.size(); i++)
	{
		orientedBoundingBox* boxA = &this->OBBs[i];
		
		for(unsigned int j = 0; j < this->OBBs.size(); j++)
		{
			orientedBoundingBox* boxB = &this->OBBs[j];
			if(boxA == boxB)
			{
				continue;
			}

		}
	}
}

//check collision between two oriented bounding boxes
void PhysicsWorld::checkCollision(orientedBoundingBox* A, orientedBoundingBox* B)
{

}

//check collision between a ray cast and an oriented bounding box
void PhysicsWorld::checkCollision(raycast* ray, orientedBoundingBox* box)
{

}
