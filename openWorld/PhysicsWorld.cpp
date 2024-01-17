#include "PhysicsWorld.h"

void PhysicsWorld::eulerIntergration(physicsObject& object, Force& force, float dt)
{
	/*float accelerationX = force.direction.x * (force.magnitude / object.body->mass);
	float accelerationY = force.direction.y * (force.magnitude / object.body->mass);;
	float accelerationZ = force.direction.z * (force.magnitude / object.body->mass);;



	object.body->velocity.x += accelerationX * dt;
	object.body->velocity.y += accelerationY * dt;
	object.body->velocity.z += accelerationZ * dt;

	object.body->position.x += object.body->velocity.x * dt;
	object.body->position.y += object.body->velocity.y * dt;
	object.body->position.z += object.body->velocity.z * dt;*/

}

void PhysicsWorld::stepSimulation(float dt)
{
	//iterate through every physics object in the physics world and do its physics, check for collisions, if collisions are found make items not penetrat eachother
	for(int i = 0; i < objects.size(); i++)
	{
		//update position of the object based on the parameters of its rigid body
		RigidBody* tempBody = &rigidBodies.lookup(objects[i].rigidBodyID);
		tempBody->updatePosition(dt);

		//broad phase collision detection, check for possible collisions
		std::vector <physicsObject*> possibleCollisions = createPossibleCollisions(&objects[i]);

		//narrow phase collision detection, check all objects created in the broad phase collsion detection against our current object
		for(int j = 0; j < possibleCollisions.size(); j++)
		{
			//return collision detection result
			bool collisionResult = checkCollision(&objects[i], possibleCollisions[j]);
			//resolve collision
		}
	}


}

std::vector<physicsObject*> PhysicsWorld::createPossibleCollisions(physicsObject* currentObject)
{
	std::vector <physicsObject*> objects;

	//iterate through all world objects checking the distance to their broad phase collider, if the distance is less than the broad phase collider size add to objects list
	for(int i = 0; i < objects.size(); i++)
	{
		float distance = findDistance(currentObject->broadCollisionCollider.position, objects[i]->broadCollisionCollider.position);
		if(distance < currentObject->broadCollisionCollider.returnRadius())
		{
			objects.push_back(objects[i]);
		}
	}

	return objects;
}

bool PhysicsWorld::checkCollision(physicsObject* objectA, physicsObject* objectB)
{
	bool collisionResult = false;

	//do SAT here
	return collisionResult;
}

physicsObject* PhysicsWorld::createPhysicsObject(RigidBody body, std::vector <Collider> colliders)
{
	//create a new physics object
	physicsObject newObject;
	//generate the rigid body id and add the body to the lookup table
	newObject.rigidBodyID = rigidBodies.add(body);
	this->numRigidBodies++;

	std::vector <ID> colliderIDs;
	//generate ids for all smaller colliders and store them in the lookup table
	for(int i = 0; i < colliders.size(); i++)
	{
		ID newID = this->colliders.add(colliders[i]);
		colliderIDs.push_back(newID);
		numColliders++;
	}

	newObject.colliderIDs = colliderIDs;

	//generate the broad phase collision colldier
	newObject.broadCollisionCollider = generateBroadPhaseCollider(newObject);
	numBroadPhaseColliders++;

	objects.push_back(newObject);
	this->physicsWorldObjects++;

	return &newObject;
}

void PhysicsWorld::deletePhysicsObject(physicsObject* object)
{

}

sphereCollider PhysicsWorld::generateBroadPhaseCollider(physicsObject object)
{
	glm::vec3 position = this->rigidBodies.lookup(object.rigidBodyID).position;
	float furthestPoint = 0.0;

	//loop through each of the objects colliders and find the further point from the center of the object this is the radius of the sphere collider

	std::vector <Collider*> colliders; //list of object colliders for sorting

	for(int i = 0; i < object.colliderIDs.size(); i++) //add all colliders into a ptr container
	{
		colliders.push_back(&this->colliders.lookup(object.colliderIDs[i]));
	}

	//iterate through each collider looking for the furthest point
	for(int i = 0; i < colliders.size(); i++)
	{
		float localPoint = 0.0;
		std::vector <glm::vec3> vertices = colliders[i]->returnVertices();
	
		for(int j = 0; j < vertices.size(); j++)
		{
			float distance = findDistance(position, vertices[j]);
			if(distance > localPoint)
			{
				localPoint = distance;
			}
		}
		if(localPoint > furthestPoint)
		{
			furthestPoint = localPoint;
		}
	}

	//once furthestPoint was calculated we have our sphere radius
	sphereCollider newSphere;
	newSphere.createCollider(position, furthestPoint);

	return newSphere;
}

float PhysicsWorld::findDistance(glm::vec3 pointA, glm::vec3 pointB)
{
	float distance;

	distance = (pointB.x - pointA.x) + (pointB.y - pointA.y) + (pointB.z - pointA.z);

	return distance;
}