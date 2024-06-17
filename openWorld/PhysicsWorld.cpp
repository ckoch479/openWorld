#include "PhysicsWorld.h"

PhysicsWorld::PhysicsWorld()
{
	this->physicsCommon = new reactphysics3d::PhysicsCommon;
	this->world = physicsCommon->createPhysicsWorld();
	this->world->setIsDebugRenderingEnabled(false);
	this->worldListener = new reactPhysicsListener();
	this->world->setEventListener(this->worldListener);
}

PhysicsWorld::~PhysicsWorld()
{
	this->physicsCommon->destroyPhysicsWorld(this->world);
	delete this->worldListener;
	delete this->physicsCommon;
}

void PhysicsWorld::stepSimulation(float dt)
{
	this->world->update(dt);
}

//collider/rigid body creation-----------------------------------------------------------------------------------------
unsigned int PhysicsWorld::createRigidBody(glm::vec3 position, glm::quat rotation, float mass, std::vector <glm::vec3> vertices, rigidBodyType type)
{
	reactphysics3d::Vector3 Position(position.x, position.y, position.z);
	//reactphysics3d::Quaternion orientation(rotation.x, rotation.y, rotation.z, rotation.w);
	rp3d::Quaternion orientation = rp3d::Quaternion::identity();
	
	reactphysics3d::Transform transform(Position,orientation);

	int rigidBodyID = getUniqueID();
	rigidBody RigidBody;

	this->rigidBodies[rigidBodyID] = RigidBody;
	this->rigidBodies[rigidBodyID].vertices = vertices;

	rp3d::VertexArray vertexArray(&this->rigidBodies[rigidBodyID].vertices[0], sizeof(glm::vec3), vertices.size(), rp3d::VertexArray::DataType::VERTEX_FLOAT_TYPE);
	
	reactphysics3d::RigidBody* newBody = this->world->createRigidBody(transform);
	this->rigidBodies[rigidBodyID].body = newBody;
	newBody->setMass(mass);

	switch(type)
	{
	case(Static):
		newBody->setType(rp3d::BodyType::STATIC);
		newBody->setIsAllowedToSleep(false);
		break;
	case(Dynamic):
		newBody->setType(rp3d::BodyType::DYNAMIC);
		newBody->setIsAllowedToSleep(true);
		break;
	case(Kinematic):
		newBody->setType(rp3d::BodyType::KINEMATIC);
		newBody->setIsAllowedToSleep(false);
		break;
	}

	std::vector<rp3d::Message> messages;
	rp3d::ConvexMesh* convexMesh = this->physicsCommon->createConvexMesh(vertexArray, messages);

	if (messages.size() > 0) {

		for (const rp3d::Message& message : messages) {

			std::string messageType;
			switch (message.type) {
			case rp3d::Message::Type::Information:
				messageType = "info";
				break;
			case rp3d::Message::Type::Warning:
				messageType = "warning";
				break;
			case rp3d::Message::Type::Error:
				messageType = "error";
				break;
			}

			std::cout << "Message (" << messageType << "): " << message.text << std::endl;
		}
	}

	assert(convexMesh != nullptr);

	rp3d::Vector3 scaling(1, 1, 1);

	rp3d::ConvexMeshShape* convexMeshShape = this->physicsCommon->createConvexMeshShape(convexMesh,scaling);
	
	rp3d::Transform identity = rp3d::Transform::identity();
	
	this->rigidBodies[rigidBodyID].body = newBody;
	this->rigidBodies[rigidBodyID].collider = newBody->addCollider(convexMeshShape, identity);

	this->rigidBodies[rigidBodyID].collider->setIsSimulationCollider(true);
	this->rigidBodies[rigidBodyID].body->updateMassPropertiesFromColliders();
	this->rigidBodies[rigidBodyID].body->updateLocalCenterOfMassFromColliders();

	//this->rigidBodies[rigidBodyID].body->setIsDebugEnabled(true);

	return rigidBodyID;
}

unsigned int PhysicsWorld::CreateRigidBody()
{
	unsigned int newId = getUniqueID();
	mRigidBody Body;

	reactphysics3d::Vector3 Position(0,0,0);
	rp3d::Quaternion orientation = rp3d::Quaternion::identity();
	reactphysics3d::Transform transform(Position, orientation);

	reactphysics3d::RigidBody* newBody = this->world->createRigidBody(transform);
	newBody->setType(rp3d::BodyType::STATIC);

	Body.body = newBody;
	Body.ID = newId;
	Body.type = Static;

	this->RigidBodies[newId] = Body;

	return newId;
}


void PhysicsWorld::attachConcaveColliderToBody(ColliderTypes type, glm::vec3 relPosition, glm::quat relOrient, std::vector <glm::vec3> vertices, std::vector <unsigned int> indices, unsigned int id)
{
	rp3d::RigidBody* body = this->RigidBodies[id].body;
	
	rp3d::Vector3 position(relPosition.x, relPosition.y, relPosition.z);
	rp3d::Quaternion orient;
	orient.x = relOrient.x;
	orient.y = relOrient.y;
	orient.z = relOrient.z;
	orient.w = relOrient.w;

	rp3d::Transform identity(position, orient);

	int numVerts = vertices.size();
	int numTriangles = indices.size() / 3;

	rp3d::TriangleVertexArray* triangleArray = new rp3d::TriangleVertexArray(numVerts, &vertices[0], sizeof(glm::vec3), numTriangles, &indices[0],
		3 * sizeof(unsigned int), rp3d::TriangleVertexArray::VertexDataType::VERTEX_FLOAT_TYPE, rp3d::TriangleVertexArray::IndexDataType::INDEX_INTEGER_TYPE);

	std::vector <rp3d::Message> messages;
	rp3d::TriangleMesh* triangleMesh = this->physicsCommon->createTriangleMesh(*triangleArray, messages);

	if (messages.size() > 0) {

		for (const rp3d::Message& message : messages) {

			std::string messageType;
			switch (message.type) {
			case rp3d::Message::Type::Information:
				messageType = "info";
				break;
			case rp3d::Message::Type::Warning:
				messageType = "warning";
				break;
			case rp3d::Message::Type::Error:
				messageType = "error";
				break;
			}

			std::cout << "Message (" << messageType << "): " << message.text << std::endl;
		}
	}

	assert(triangleMesh != nullptr);

	rp3d::ConcaveMeshShape* meshShape = this->physicsCommon->createConcaveMeshShape(triangleMesh, rp3d::Vector3(1.0, 1.0, 1.0));

	this->RigidBodies[id].bodyColliders.push_back(body->addCollider(meshShape, identity));
	
}

void PhysicsWorld::addCollidertoRigidBody(unsigned int ID, std::vector <glm::vec3>& vertices, glm::vec3 relativePos, glm::quat relOrientation)
{
	rigidBody* body = &this->rigidBodies[ID];
	
	//create transform
	rp3d::Vector3 relativePosition = rp3d::Vector3(relativePos.x,relativePos.y,relativePos.z);
	rp3d::Quaternion relativeOrient(relOrientation.x, relOrientation.y, relOrientation.z, relOrientation.w);
	rp3d::Transform transform(relativePosition,relativeOrient);

	//create collider shape
	rp3d::VertexArray vertexArray(&vertices[0], sizeof(glm::vec3), vertices.size(), rp3d::VertexArray::DataType::VERTEX_FLOAT_TYPE);

	std::vector<rp3d::Message> messages;
	rp3d::ConvexMesh* convexMesh = this->physicsCommon->createConvexMesh(vertexArray, messages);

	if (messages.size() > 0) {

		for (const rp3d::Message& message : messages) {

			std::string messageType;
			switch (message.type) {
			case rp3d::Message::Type::Information:
				messageType = "info";
				break;
			case rp3d::Message::Type::Warning:
				messageType = "warning";
				break;
			case rp3d::Message::Type::Error:
				messageType = "error";
				break;
			}

			std::cout << "Message (" << messageType << "): " << message.text << std::endl;
		}
	}

	assert(convexMesh != nullptr);

	rp3d::Vector3 scaling(1, 1, 1);

	rp3d::ConvexMeshShape* convexMeshShape = this->physicsCommon->createConvexMeshShape(convexMesh, scaling);

	//add collider to the rigid body
	body->body->addCollider(convexMeshShape,transform);

}

unsigned int PhysicsWorld::createBoxCollider(glm::vec3 postion, glm::vec3 rotation, glm::vec3 halfExtents, rigidBodyType type)
{
	return 0;
}

unsigned int PhysicsWorld::createSphereCollider(glm::vec3 position, float radius, rigidBodyType type)
{
	return 0;
}

unsigned int PhysicsWorld::createCapsuleShape(glm::vec3 position, glm::quat rotation,float mass, float radius, float height, rigidBodyType type)
{
	reactphysics3d::Vector3 Position(position.x, position.y, position.z);
	
	rp3d::Quaternion orientation = rp3d::Quaternion::identity();

	reactphysics3d::Transform transform(Position, orientation);

	int rigidBodyID = getUniqueID();
	rigidBody RigidBody;

	reactphysics3d::RigidBody* newBody = this->world->createRigidBody(transform);
	this->rigidBodies[rigidBodyID].body = newBody;
	newBody->setMass(10);

	switch (type)
	{
	case(Static):
		newBody->setType(rp3d::BodyType::STATIC);
		newBody->setIsAllowedToSleep(false);
		break;
	case(Dynamic):
		newBody->setType(rp3d::BodyType::DYNAMIC);
		newBody->setIsAllowedToSleep(true);
		break;
	case(Kinematic):
		newBody->setType(rp3d::BodyType::KINEMATIC);
		newBody->setIsAllowedToSleep(false);
		break;
	}

	rp3d::Transform identity = rp3d::Transform::identity();

	rp3d::CapsuleShape* capsuleShape = this->physicsCommon->createCapsuleShape(radius,height);

	this->rigidBodies[rigidBodyID] = RigidBody;

	this->rigidBodies[rigidBodyID].body = newBody;
	this->rigidBodies[rigidBodyID].collider = newBody->addCollider(capsuleShape, identity);

	this->rigidBodies[rigidBodyID].collider->setIsSimulationCollider(true);
	this->rigidBodies[rigidBodyID].body->updateMassPropertiesFromColliders();
	this->rigidBodies[rigidBodyID].body->updateLocalCenterOfMassFromColliders();

	return rigidBodyID;
}

void PhysicsWorld::setBodyPosition(unsigned int id, glm::vec3 pos)
{
	rigidBody* body = &this->rigidBodies[id];
	rp3d::Quaternion newQuat = rp3d::Quaternion::identity();
	rp3d::Transform newTransform(rp3d::Vector3(pos.x, pos.y, pos.z), newQuat);
	body->body->setTransform(newTransform);
}

void PhysicsWorld::addForceToBody(unsigned int id, glm::vec3 force)
{
	rigidBody* body = &this->rigidBodies[id];
	body->body->applyWorldForceAtCenterOfMass(rp3d::Vector3(force.x, force.y, force.z));
}

void PhysicsWorld::changeBodyVelocity(unsigned int id, glm::vec3 newVel)
{
	rigidBody* body = &this->rigidBodies[id];
	rp3d::Vector3 velocity = body->body->getLinearVelocity();
	body->body->setLinearVelocity(rp3d::Vector3(newVel.x, velocity.y,newVel.z));
}

void PhysicsWorld::changeBodyFriction(unsigned int id, float frictionCoef)
{
	rigidBody* body = &this->rigidBodies[id];
	rp3d::Material *bodyMat = &body->collider->getMaterial();
	bodyMat->setFrictionCoefficient(frictionCoef);
	body->collider->setMaterial(*bodyMat);
}

void PhysicsWorld::lockBodyRotationAxis(unsigned int id, glm::vec3 locked)
{
	rigidBody* body = &this->rigidBodies[id];
	body->body->setAngularLockAxisFactor(rp3d::Vector3(locked.x, locked.y, locked.z));
}

void PhysicsWorld::changeColliderOrigin(unsigned int id, glm::vec3 directionalChange) 
{
	rigidBody* body = &this->rigidBodies[id];
	rp3d::Vector3 position(directionalChange.x, directionalChange.y, directionalChange.z);
		rp3d::Quaternion rotation = rp3d::Quaternion::identity();
		rp3d::Transform newTransform(position, rotation);
	body->collider->setLocalToBodyTransform(newTransform);
}

//concave rigid body does not work as of right now, indices are incorrect i believe
unsigned int PhysicsWorld::createConcaveRigidbody(glm::vec3 position, glm::quat rotation, std::vector <glm::vec3> vertices, std::vector <unsigned int> indices)
{
	unsigned int newId = getUniqueID();
	int numVerts = vertices.size();
	int numTriangles = indices.size()/3;

	reactphysics3d::Vector3 Position(position.x, position.y, position.z);
	rp3d::Quaternion orientation = rp3d::Quaternion::identity();

	reactphysics3d::Transform transform(Position, orientation);

	rigidBody RigidBody;

	this->rigidBodies[newId] = RigidBody;
	this->rigidBodies[newId].vertices = vertices;
	this->rigidBodies[newId].indices = indices;

	reactphysics3d::RigidBody* newBody = this->world->createRigidBody(transform);
	this->rigidBodies[newId].body = newBody;



	rp3d::TriangleVertexArray* triangleArray = new rp3d::TriangleVertexArray(numVerts,&this->rigidBodies[newId].vertices[0],sizeof(glm::vec3),numTriangles,&this->rigidBodies[newId].indices[0],
		3 * sizeof(unsigned int), rp3d::TriangleVertexArray::VertexDataType::VERTEX_FLOAT_TYPE,rp3d::TriangleVertexArray::IndexDataType::INDEX_INTEGER_TYPE);

	std::vector <rp3d::Message> messages;
	rp3d::TriangleMesh* triangleMesh = this->physicsCommon->createTriangleMesh(*triangleArray,messages);

	if (messages.size() > 0) {

		for (const rp3d::Message& message : messages) {

			std::string messageType;
			switch (message.type) {
			case rp3d::Message::Type::Information:
				messageType = "info";
				break;
			case rp3d::Message::Type::Warning:
				messageType = "warning";
				break;
			case rp3d::Message::Type::Error:
				messageType = "error";
				break;
			}

			std::cout << "Message (" << messageType << "): " << message.text << std::endl;
		}
	}

	assert(triangleMesh != nullptr);

	rp3d::ConcaveMeshShape* meshShape = this->physicsCommon->createConcaveMeshShape(triangleMesh,rp3d::Vector3(1.0,1.0,1.0));

	rp3d::Transform identity = rp3d::Transform::identity();

	rigidBodies[newId].collider = rigidBodies[newId].body->addCollider(meshShape, identity);
	this->rigidBodies[newId].body->setType(rp3d::BodyType::STATIC);

	return newId;
}
//----------------------------------------------------------------------------------------------------------------------------------------

int PhysicsWorld::getUniqueID()
{
	this->physicsWorldObjects++;
	return this->physicsWorldObjects;
}

glm::vec3 PhysicsWorld::getBodyPosition(unsigned int id)
{
	rp3d::Transform tempTransform = this->rigidBodies[id].body->getTransform();
	rp3d::Vector3 pos = tempTransform.getPosition();
	return glm::vec3(pos.x, pos.y, pos.z);
}

glm::vec3 PhysicsWorld::getConcaveBodyPosition(unsigned int id)
{
	rp3d::Transform tempTransform = this->concaveRigidBodies[id].body->getTransform();
	rp3d::Vector3 pos = tempTransform.getPosition();
	return glm::vec3(pos.x, pos.y, pos.z);
}

glm::quat PhysicsWorld::getBodyRotation(unsigned int id)
{
	rp3d::Transform tempTransform = this->rigidBodies[id].body->getTransform();
	rp3d::Quaternion orient = tempTransform.getOrientation();
	return glm::quat(orient.w,orient.x, orient.y, orient.z);
}

glm::quat PhysicsWorld::getConcaveBodyRotation(unsigned int id)
{
	rp3d::Transform tempTransform = this->concaveRigidBodies[id].body->getTransform();
	rp3d::Quaternion orient = tempTransform.getOrientation();
	return glm::quat(orient.w, orient.x, orient.y, orient.z);
}

std::vector <debugTriangles> PhysicsWorld::debugRenderer()
{
	rp3d::DebugRenderer& debugRenderer = this->world->getDebugRenderer();
	debugRenderer.setIsDebugItemDisplayed(rp3d::DebugRenderer::DebugItem::COLLISION_SHAPE,true);
	debugRenderer.setIsDebugItemDisplayed(rp3d::DebugRenderer::DebugItem::COLLIDER_BROADPHASE_AABB, true);

	const int numlines = debugRenderer.getNbLines(); //number of lines;
	const int numTriangles = debugRenderer.getNbTriangles();
	std::vector <debugLines> debugData;
	std::vector <debugTriangles> triangleData;

	for(unsigned int i = 0; i < numTriangles; i++)
	{
		debugTriangles newTriangle;
		const rp3d::Array <rp3d::DebugRenderer::DebugTriangle> triangles = debugRenderer.getTriangles();
		
		newTriangle.vertex = glm::vec3(triangles[i].point1.x, triangles[i].point1.y, triangles[i].point1.z);
		newTriangle.vertex2 = glm::vec3(triangles[i].point2.x, triangles[i].point2.y, triangles[i].point2.z);;
		newTriangle.vertex3 = glm::vec3(triangles[i].point3.x, triangles[i].point3.y, triangles[i].point3.z);;
		

		switch(triangles[i].color1)
		{
		case(0xff0000): //RED
			newTriangle.color = glm::vec3(255, 0, 0);
			break;
		case(0x00ff00): //Green
			newTriangle.color = glm::vec3(0, 255, 0);
			break;
		case(0x0000ff): //BLUE
			newTriangle.color = glm::vec3(0, 0, 255);
			break;
		case(0x000000): //BLACK
			newTriangle.color = glm::vec3(0, 0, 0);
			break;
		case(0xffffff): //WHITE
			newTriangle.color = glm::vec3(255, 255, 255);
			break;
		case(0xffff00): //YELLOW
			newTriangle.color = glm::vec3(255, 255, 0);
			break;
		case(0xff00ff): //MAGENTA
			newTriangle.color = glm::vec3(255, 0, 255);
			break;
		case(0x00ffff): //CYAN
			newTriangle.color = glm::vec3(0, 255, 255);
			break;
		}

		switch (triangles[i].color2)
		{
		case(0xff0000): //RED
			newTriangle.color2 = glm::vec3(255, 0, 0);
			break;
		case(0x00ff00): //Green
			newTriangle.color2 = glm::vec3(0, 255, 0);
			break;
		case(0x0000ff): //BLUE
			newTriangle.color2 = glm::vec3(0, 0, 255);
			break;
		case(0x000000): //BLACK
			newTriangle.color2 = glm::vec3(0, 0, 0);
			break;
		case(0xffffff): //WHITE
			newTriangle.color2 = glm::vec3(255, 255, 255);
			break;
		case(0xffff00): //YELLOW
			newTriangle.color2 = glm::vec3(255, 255, 0);
			break;
		case(0xff00ff): //MAGENTA
			newTriangle.color2 = glm::vec3(255, 0, 255);
			break;
		case(0x00ffff): //CYAN
			newTriangle.color2 = glm::vec3(0, 255, 255);
			break;
		}

		switch (triangles[i].color3)
		{
		case(0xff0000): //RED
			newTriangle.color2 = glm::vec3(255, 0, 0);
			break;
		case(0x00ff00): //Green
			newTriangle.color2 = glm::vec3(0, 255, 0);
			break;
		case(0x0000ff): //BLUE
			newTriangle.color2 = glm::vec3(0, 0, 255);
			break;
		case(0x000000): //BLACK
			newTriangle.color2 = glm::vec3(0, 0, 0);
			break;
		case(0xffffff): //WHITE
			newTriangle.color2 = glm::vec3(255, 255, 255);
			break;
		case(0xffff00): //YELLOW
			newTriangle.color2 = glm::vec3(255, 255, 0);
			break;
		case(0xff00ff): //MAGENTA
			newTriangle.color2 = glm::vec3(255, 0, 255);
			break;
		case(0x00ffff): //CYAN
			newTriangle.color2 = glm::vec3(0, 255, 255);
			break;
		}

		triangleData.push_back(newTriangle);
	}

	return triangleData;
}








