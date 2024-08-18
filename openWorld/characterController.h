#pragma once


#include "PhysicsWorld.h"
#include "Scene.h"
#include "playerEntity.h"
#include "windowManager.h"

#include "Level.h"

#include "includes/glm/glm.hpp"
#include "Includes/glm/gtc/type_ptr.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/quaternion.hpp"
#include "includes/glm/gtx/quaternion.hpp"
#include "Includes/glm/gtx/matrix_decompose.hpp"

//class for handling player movement and world collisions, will also automatically update the player transforms in physics world and pass transform to player entity
class characterController
{
public:
	
	characterController(playerEntity* newPlayer, PhysicsWorld* newWorld, Camera* newCamera);

	~characterController();

	void updateInputs(windowManager* manager);

	void updateController(float dt, Level currentLevel);

	bool ikTest = false;

private:

	void addPlayerToWorld();

	void updateOBBs();

	PhysicsWorld* world;
	playerEntity* player; //for transforms and current action references


	Camera* playerCamera; //in the character controller cause the camera should usually follow the player unless in free cam
	float pitch = 0.0f, yaw = 0;
	double cursorX = 0, cursorY = 0;

	//for referencing the physicsWorld Object
	unsigned int physicsId;

	glm::vec3 playerVelocity = glm::vec3(0.0f);
	float playerMass = 60;

	//user input keys set like this so they can be remapped as needed
	int forwardMov = 87; //W
	int left = 65; //A
	int right = 68; //D
	int back = 83; //S

	int jump = 32; //Space

	int crouchT = 341; //Lctrl
	int sprint = 340; //Lshift

	int togWalk = 280;//capsLock
	int inventory = 258; //Tab

	//map that uses the input keys above as the key and a bool to determine it has been pressed or not

	std::unordered_map<int, bool> playerKeys;

	bool cameraForward = false;
	bool cameraBackWard = false;
	bool cameraRight = false;
	bool cameraLeft = false;

	bool walkT = false;
	bool crouchToggle = false;
	bool crawlToggle = false;

	bool aiming = false;
	bool shooting = false;

	std::vector <unsigned int> OBBids;
	std::unordered_map<unsigned int, int> boneOBBidMap;
	unsigned int playerMainColliderID;
};

