#include "RigidBody.h"
RigidBody::RigidBody()
{

}

RigidBody::~RigidBody()
{

}

void RigidBody::createRigidBody(glm::vec3 newposition, glm::quat neworientation, float newmass)
{
	this->position = newposition;
	this->orientation = neworientation;
	this->mass = newmass;

	this->velocity = glm::vec3(0.0f);
	this->acceleration = glm::vec3(0.0f);

	this->rotationOrigin = glm::vec3(0.0, 1.0, 0.0);
	this->angularVelocity = glm::vec3(0.0f);
	this->angularAcceleration = glm::vec3(0.0f);
}

void RigidBody::updatePosition(float dt)
{

}

void RigidBody::applyForce(glm::vec3 newForce)
{

}

void RigidBody::sleepObject()
{

}

glm::vec3 RigidBody::calculateNewPosition(float dt)
{
	return this->position;
}