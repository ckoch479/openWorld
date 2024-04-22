#include "PhysicsWorld.h"

PhysicsWorld::PhysicsWorld()
{

}

PhysicsWorld::~PhysicsWorld()
{

}

void PhysicsWorld::stepSimulation(float dt)
{
	for (unsigned int i = 0; i < this->numObjects; i++) //iterate through all physics world objects
	{
		physicsObject* tempObject = &objects.lookup(objectIDs[i]); //create a pointer to the main object for ease of use

		float coefficientFrictionKinetic = 0.0; //temporary test value
		//apply forces to objects:

		for (unsigned int j = 0; j < tempObject->forcesApplied.size(); ++j)
		{
			glm::vec3 force(0.0f);
				force = tempObject->forcesApplied[j];
			glm::vec3 acceleration = force / tempObject->objectBody.mass; //A = F/M

			tempObject->objectBody.velocity += acceleration * dt; // set object velocity


			//calculate friction

			if (tempObject->objectBody.velocity.x > 0) {
				tempObject->objectBody.velocity.x -= coefficientFrictionKinetic * dt;
			}
			else if (tempObject->objectBody.velocity.x < 0) {
				tempObject->objectBody.velocity.x += coefficientFrictionKinetic * dt;
			}

			if (tempObject->objectBody.velocity.y > 0) {
				tempObject->objectBody.velocity.y -= coefficientFrictionKinetic * dt;
			}
			else if (tempObject->objectBody.velocity.y < 0) {
				tempObject->objectBody.velocity.y += coefficientFrictionKinetic * dt;
			}

			if (tempObject->objectBody.velocity.z > 0) {
				tempObject->objectBody.velocity.z -= coefficientFrictionKinetic * dt;
			}
			else if (tempObject->objectBody.velocity.z < 0) {
				tempObject->objectBody.velocity.z += coefficientFrictionKinetic * dt;
			}

			//prevent friction from making the objects velocity reverse
			if (tempObject->objectBody.velocity.x * force.x <= 0.0) {
				tempObject->objectBody.velocity.x = 0;
			}

			if (tempObject->objectBody.velocity.y * force.y <= 0.0) {
				tempObject->objectBody.velocity.y = 0;
			}

			if (tempObject->objectBody.velocity.z * force.z <= 0.0) {
				tempObject->objectBody.velocity.z = 0;
			}

			tempObject->objectBody.position += tempObject->objectBody.velocity * dt; //set object position
		}

		tempObject->forcesApplied.clear();

		//rotational force
		
		

		//check for collisions

		//terrainCollisionDetection
		
		if (tempObject->objectBody.position.y < this->XZtable[tempObject->objectBody.position.x][tempObject->objectBody.position.z])
		{
			tempObject->objectBody.position.y = this->XZtable[tempObject->objectBody.position.x][tempObject->objectBody.position.z];
			//tempObject->objectBody.velocity.y = 0;
		}

		

		
			//broad phase collision


			//narrow phase collision

		//resolve collisions (update positions of intersecting objects, apply forces to objects affected by collisions)


		//update object positions

		

	}
}

void PhysicsWorld::addTerrainMeshVertices(std::vector <glm::vec3> verts)
{
	this->WorldMeshVertices = verts;

	for(unsigned int i = 0; i < this->WorldMeshVertices.size(); i++)
	{
		this->XZtable[(int)WorldMeshVertices[i].x][(int)WorldMeshVertices[i].z] = WorldMeshVertices[i].y;
	}
}

//create a new Physics object and return an ID for the object created

ID PhysicsWorld::createPhysicsObject(std::vector <glm::vec3>& meshData, glm::vec3 startingPosition, glm::quat rotation)
{
	ID newObjectID;


	physicsObject newObject;
	newObject.objectBody.position = startingPosition;
	newObject.objectBody.orientation = rotation;
	newObject.objectBody.mass = 10.0f;
	newObject.objectBody.velocity = glm::vec3(0.0f);
	newObject.objectBody.acceleration = glm::vec3(0.0f);
	newObject.objectBody.angularAcceleration = glm::vec3(0.0f);
	newObject.objectBody.angularVelocity = glm::vec3(0.0f);
	newObject.objectBody.momentOfInteria = glm::vec3(0.0f);

	newObject.objectCollider = calculateAABBFromMeshData(meshData);

	newObjectID = objects.add(newObject); //add physics object to the lookup table
	objectIDs.push_back(newObjectID);

	numObjects++;

	std::cout << "add new object ID of: " << newObjectID.index << std::endl;

	return newObjectID;
}

AABBCollider PhysicsWorld::calculateAABBFromMeshData(std::vector <glm::vec3>& meshData)
{
	AABBCollider newCollider;

	//take the average width, depth, and height and create an AABB for the mesh

	std::vector <float> widths;
	std::vector <float> depths;
	std::vector <float> heights;
	
	double averageWidth = 0;
	double averageHeight = 0;
	double averageDepth = 0;
	//seperate the mesh into three float vectors
	for(unsigned int i = 0; i < meshData.size(); i++)
	{
		widths.push_back(meshData[i].x);
		depths.push_back(meshData[i].z);
		heights.push_back(meshData[i].y);
	}
	//calculate average width
	for(unsigned int i = 0; i < widths.size(); i++)
	{
		averageWidth += widths[i];
	}
	averageWidth /= widths.size();
	//calculate average height
	for (unsigned int i = 0; i < heights.size(); i++)
	{
		averageHeight += heights[i];
	}
	averageHeight /= heights.size();
	//calculate average depth
	for (unsigned int i = 0; i < depths.size(); i++)
	{
		averageDepth += depths[i];
	}
	averageDepth /= depths.size();

	newCollider.bottomA = glm::vec3( averageWidth, 0, -averageDepth);
	newCollider.bottomB = glm::vec3( averageWidth, 0,  averageDepth);
	newCollider.bottomC = glm::vec3(-averageWidth, 0,  averageDepth);
	newCollider.bottomD = glm::vec3(-averageWidth, 0, -averageDepth);
	newCollider.topA = glm::vec3( averageWidth, averageHeight, -averageDepth);
	newCollider.topB = glm::vec3( averageWidth, averageHeight,  averageDepth);
	newCollider.topC = glm::vec3(-averageWidth, averageHeight,  averageDepth);
	newCollider.topD = glm::vec3(-averageWidth, averageHeight, -averageDepth);

	return newCollider;
}

void PhysicsWorld::deletePhysicsObject(ID objectID)
{
	this->rigidBodies.remove(this->objects.lookup(objectID).rigidBodyID); //remove the rigid body attached to this world object
	this->numRigidBodies--;

	this->objects.remove(objectID); //remove world object itself
	this->physicsWorldObjects--;
}

void PhysicsWorld::applyForce(ID objectID, glm::vec3 force)
{
	objects.lookup(objectID).forcesApplied.push_back(force);
}

glm::vec3 PhysicsWorld::getBodyPosition(ID bodyID)
{
	physicsObject* tempBody = &this->objects.lookup(bodyID);
	return tempBody->objectBody.position;
}

glm::quat PhysicsWorld::getBodyOrientation(ID bodyID)
{
	physicsObject* tempBody = &this->objects.lookup(bodyID);
	return tempBody->objectBody.orientation;
}

ID PhysicsWorld::createRigidBody(RigidBody body)
{
	ID bodyID;
	bodyID = this->rigidBodies.add(body);

	return bodyID;
}

ID PhysicsWorld::createRigidBody(glm::vec3 position, glm::quat rotation, float mass)
{
	ID bodyID;
	RigidBody newBody;

	newBody.position = position;
	newBody.orientation = rotation;

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







