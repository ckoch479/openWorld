#include "PhysicsWorld.h"

PhysicsWorld::PhysicsWorld()
{

}

PhysicsWorld::~PhysicsWorld()
{

}

void PhysicsWorld::stepSimulation(float dt)
{
	for (int i = 0; i < worldObjectIDs.size(); i++) //iterate through all world objects and then update their positions
	{
		physicsObject* tempObject = &this->objects.lookup(worldObjectIDs[i]);

		//rigid bodies
		RigidBody* tempBody = &this->rigidBodies.lookup(tempObject->rigidBodyID);
		tempBody->updatePosition(dt);

	}
}

//create a new Physics object and return an ID for the object created
ID PhysicsWorld::createPhysicsObject(RigidBody* body, std::vector <orientedBoundingBox> colliders)
{
	physicsObject newObject;

	newObject.rigidBodyID = this->rigidBodies.add(*body);
	this->numRigidBodies++;

	ID newID;
	newID = this->objects.add(newObject);
	this->physicsWorldObjects++;

	this->worldObjectIDs.push_back(newID);

	return newID;
}

void PhysicsWorld::deletePhysicsObject(ID objectID)
{
	this->rigidBodies.remove(this->objects.lookup(objectID).rigidBodyID); //remove the rigid body attached to this world object
	this->numRigidBodies--;

	this->objects.remove(objectID); //remove world object itself
	this->physicsWorldObjects--;
}

void PhysicsWorld::applyForce(ID bodyID, glm::vec3 force)
{
	RigidBody* tempBody = &this->rigidBodies.lookup(bodyID);
	tempBody->applyForce(force);
}

glm::vec3 PhysicsWorld::getBodyPosition(ID bodyID)
{
	RigidBody* tempBody = &this->rigidBodies.lookup(bodyID);
	return tempBody->position;
}

glm::quat PhysicsWorld::getBodyOrientation(ID bodyID)
{
	RigidBody* tempBody = &this->rigidBodies.lookup(bodyID);
	return tempBody->orientation;
}

glm::vec3 PhysicsWorld::getBodyRotationOrigin(ID bodyID)
{
	RigidBody* tempBody = &this->rigidBodies.lookup(bodyID);
	return tempBody->rotationOrigin;
}


ID PhysicsWorld::createPhysicsObject(ID rigidBodyID) //Add collision boxes later
{
	ID newObjectID;
	physicsObject newObject;
	newObject.rigidBodyID = rigidBodyID;

	newObjectID = this->objects.add(newObject);
	this->physicsWorldObjects++;

	this->worldObjectIDs.push_back(newObjectID);

	return newObjectID;
}

ID PhysicsWorld::createRigidBody(RigidBody body)
{
	ID bodyID;
	bodyID = this->rigidBodies.add(body);

	return bodyID;
}

ID PhysicsWorld::createRigidBody(glm::vec3 position, glm::quat rotation, glm::vec3 rotationOrigin, float mass)
{
	ID bodyID;
	RigidBody newBody;

	newBody.position = position;
	newBody.orientation = rotation;
	newBody.rotationOrigin = rotationOrigin;
	newBody.mass = mass;
	newBody.acceleration = glm::vec3(0.0f);
	newBody.velocity = glm::vec3(0.0f);

	bodyID = this->rigidBodies.add(newBody);
	return bodyID;
}

void PhysicsWorld::setPosition(ID bodyID, glm::vec3 position)
{
	RigidBody* tempBody = &this->rigidBodies.lookup(bodyID);
	tempBody->position = position;
}

void PhysicsWorld::setRotation(ID bodyID, glm::quat rotation)
{
	RigidBody* tempBody = &this->rigidBodies.lookup(bodyID);
	tempBody->orientation = rotation;
}

void PhysicsWorld::setRotationOrigin(ID bodyID, glm::vec3 origin)
{
	RigidBody* tempBody = &this->rigidBodies.lookup(bodyID);
	tempBody->rotationOrigin = origin;
}





