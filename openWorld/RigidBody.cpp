#include "RigidBody.h"
RigidBody::RigidBody(bodyType newType)
{
	this->position = nullptr;
	this->mass = 1.0;
}

RigidBody::RigidBody()
{

}

RigidBody::~RigidBody()
{

}

RigidBody::RigidBody(glm::vec3* newposition, glm::quat* neworientation, float newmass, bodyType newType)
{
	this->position = newposition;
	this->orientation = neworientation;
	this->mass = newmass;

	this->velocity = glm::vec3(0.0f);
	this->acceleration = glm::vec3(0.0f);

	this->angularVelocity = glm::vec3(0.0f);
	this->angularAcceleration = glm::vec3(0.0f);
}

void RigidBody::setPosition(glm::vec3* newPos)
{
	this->position = newPos;
}

void RigidBody::setOrientation(glm::quat* newOrient)
{
	this->orientation = newOrient;
}

void RigidBody::updatePosition(float dt)
{
	//simple euler integration with nothing fancy
	/*this->velocity.x = this->acceleration.x * dt;
	this->velocity.y = this->acceleration.y * dt;
	this->velocity.z = this->acceleration.z * dt;

	this->position.x += this->velocity.x * dt;
	this->position.y += this->velocity.y * dt;
	this->position.z += this->velocity.z * dt;*/
}

void RigidBody::applyForce(glm::vec3 newForce)
{
	//A = A/M
	//this->acceleration.x += newForce.x / this->mass;
	//this->acceleration.y += newForce.y / this->mass;
	//this->acceleration.z += newForce.z / this->mass;
}

void RigidBody::sleepObject()
{

}

bodyType RigidBody::getBodyType()
{
	return this->type;
}

void RigidBody::addOBBtoBody(orientedBoundingBox* box, unsigned int boxId)
{
	this->colliders.push_back(box);
	this->colliderIds.push_back(boxId);
	this->boxIDmap[boxId] = box;
}

bool RigidBody::OBBinBody(orientedBoundingBox* box)
{
	bool isInBody = false;

	for(unsigned int i = 0; i < this->colliders.size(); i++)
	{
		if (colliders[i] = box)
		{
			isInBody = true;
			break;
		}
	}

	return isInBody;
}

bool RigidBody::OBBinBody(unsigned int boxId)
{
	bool isInBody = false;

	for(unsigned int i = 0; i < this->colliderIds.size(); i++)
	{
		if(colliderIds[i] = boxId)
		{
			isInBody = true;
			break;
		}
	}

	return isInBody;
}

glm::vec3* RigidBody::getPosition()
{
	return this->position;
}

glm::quat* RigidBody::getOrientation()
{
	return this->orientation;
}

void RigidBody::adjustOBBtoBody(glm::vec3 pos, glm::quat orient, unsigned int colliderID)
{
	this->boxIDmap[colliderID]->updateTransform(pos, orient);
}