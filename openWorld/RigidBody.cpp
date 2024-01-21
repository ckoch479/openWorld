#include "RigidBody.h"
RigidBody::RigidBody()
{
	this->position = glm::vec3(0, 0, -5);
	this->mass = 1.0;
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
	//simple euler integration with nothing fancy
	this->velocity.x = this->acceleration.x * dt;
	this->velocity.y = this->acceleration.y * dt;
	this->velocity.z = this->acceleration.z * dt;

	this->position.x += this->velocity.x * dt;
	this->position.y += this->velocity.y * dt;
	this->position.z += this->velocity.z * dt;
}

void RigidBody::applyForce(glm::vec3 newForce)
{
	//A = A/M
	this->acceleration.x += newForce.x / this->mass;
	this->acceleration.y += newForce.y / this->mass;
	this->acceleration.z += newForce.z / this->mass;
}

void RigidBody::sleepObject()
{

}
