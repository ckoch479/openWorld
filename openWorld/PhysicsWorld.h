#pragma once

#include <iostream>
#include <vector>
#include <map>

#include "lookup_table.h"

#include "includes/glm/glm.hpp"
#include "Includes/glm/gtc/type_ptr.hpp"

#include <reactphysics3d/reactphysics3d.h>
#include "reactPhysicsListener.h"


#ifndef PHYSICSWORLD_H
#define PHYSICSWORLD_H


struct physicsObject
{
	ID rigidBodyID;
};
enum rigidBodyType
{	Static,    //dont move at all
    Kinematic, //moved manually by player or program
    Dynamic,   //simulated according to physics world
};

struct rigidBody
{
	reactphysics3d::RigidBody* body;
	rp3d::Collider* collider;
	std::vector<glm::vec3> vertices; //replace this later with a pointer to vertices in the resource manager
	std::vector<unsigned int> indices;// same with this
};

struct concaveRigidBody 
{
	//glm::vec3 position;
	//glm::quat orientation;
	reactphysics3d::RigidBody* body;
	reactphysics3d::ConcaveMeshShape* meshConcave;
	reactphysics3d::ConcaveShape* shape;
	rp3d::TriangleMesh* triangleMesh;
	rp3d::Collider* collider;
};

struct WorldSettings //these values are needed prior to world creation
{
	int VelocitySolverIterations;
	bool enableSleeping;
	glm::vec3 worldGravity;
	bool debugRendering;
};

struct mRigidBody
{
	reactphysics3d::RigidBody* body;
	std::vector < rp3d::Collider*> bodyColliders;
	rigidBodyType type;
	unsigned int ID;
};

enum ColliderTypes
{
	convexMesh,
	ConcaveMesh,
	Box,
	Capsule,
	Sphere
};

struct debugLines
{
	glm::vec3 pointA;
	glm::vec3 pointB;
	glm::vec3 colorA;
	glm::vec3 colorB;
};

struct debugTriangles
{
	glm::vec3 vertex;
	glm::vec3 color;
	glm::vec3 vertex2;
	glm::vec3 color2;
	glm::vec3 vertex3;
	glm::vec3 color3;
};

class PhysicsWorld
{
public:

	PhysicsWorld();
	~PhysicsWorld();

	//ID createRigidBody();

	unsigned int createRigidBody(glm::vec3 position, glm::quat rotation, float mass, std::vector <glm::vec3> vertices, rigidBodyType type); //convex mesh

	void addCollidertoRigidBody(unsigned int ID, std::vector <glm::vec3>& vertices, glm::vec3 relativePos, glm::quat relOrientation);

	unsigned int createBoxCollider(glm::vec3 postion, glm::vec3 rotation, glm::vec3 halfExtents, rigidBodyType type);

	unsigned int createSphereCollider(glm::vec3 position, float radius, rigidBodyType type);

	unsigned int createCapsuleShape(glm::vec3 position, glm::quat rotation,float mass, float radius, float height, rigidBodyType type);

	void setBodyPosition(unsigned int id, glm::vec3 pos);

	void addForceToBody(unsigned int id, glm::vec3 force);

	void changeBodyVelocity(unsigned int id, glm::vec3 newVel);

	void changeBodyFriction(unsigned int id, float frictionCoef);

	void lockBodyRotationAxis(unsigned int id, glm::vec3 locked);

	void changeColliderOrigin(unsigned int id, glm::vec3 directionalChange);

	unsigned int CreateRigidBody();

	void attachConcaveColliderToBody(ColliderTypes type, glm::vec3 relPosition, glm::quat relOrient, std::vector <glm::vec3> vertices,std::vector <unsigned int> indices, unsigned int id);

	//these below are always Static------------------------------------
	//concave rigid body does not work as of right now, indices are incorrect i believe
	unsigned int createConcaveRigidbody(glm::vec3 position, glm::quat rotation, std::vector <glm::vec3> vertices, std::vector <unsigned int> indices);

	//unsigned int createHeightMap(std::vector <glm::vec3> vertices);
	//-----------------------------------------------------------------

	glm::vec3 getBodyPosition(unsigned int id);

	glm::vec3 getConcaveBodyPosition(unsigned int id);

	glm::quat getBodyRotation(unsigned int id);

	glm::quat getConcaveBodyRotation(unsigned int id);

	std::vector <debugTriangles> debugRenderer();

	void rayCast(glm::vec3 startPoint,glm::vec3 endPoint);

	void setTrigger();

	void setCollidertoQuery();

	//ID createPhysicsObject(std::vector <glm::vec3> &meshData, glm::vec3 startingPosition, glm::quat rotation);

	//void deletePhysicsObject(ID objectID);

	//void addTerrainMeshVertices(std::vector <glm::vec3> verts);

	//manipulate object------------------------------------------

	//void applyForce(ID objectID,glm::vec3 force);

	//void setPosition(ID bodyID, glm::vec3 position);

	//void setRotation(ID bodyID, glm::quat rotation);

	////get data from object------------------------------------

	//glm::vec3 getBodyPosition(ID bodyID);

	//glm::quat getBodyOrientation(ID bodyID);
	
	void stepSimulation(float dt);

private:

	float physicsWorldObjects = 0;

	int getUniqueID();
	
	//std::vector <ID> worldObjectIDs;
	//lookup_table <physicsObject> objects;

	std::map <unsigned int, rigidBody> rigidBodies; //a map used to store/look up info about rigid bodies with convex meshes
	std::map <unsigned int, mRigidBody> RigidBodies;
	std::map <unsigned int, concaveRigidBody> concaveRigidBodies;

	reactphysics3d::PhysicsCommon* physicsCommon;
	reactphysics3d::PhysicsWorld* world;

	reactphysics3d::PhysicsWorld::WorldSettings settings; //current settings for the physics world
	reactPhysicsListener* worldListener;
	
};


#endif