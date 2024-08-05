#pragma once


#include "PhysicsWorld.h"
#include "Scene.h"
#include "playerEntity.h"
#include "windowManager.h"

#include "Level.h"

#include "includes/glm/glm.hpp"
#include "Includes/glm/gtc/type_ptr.hpp"

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

	PhysicsWorld* world;
	playerEntity* player; //for transforms and current action references


	Camera* playerCamera; //in the character controller cause the camera should usually follow the player unless in free cam
	float pitch = 0, yaw = 0;
	double cursorX = 0, cursorY = 0;

	//for referencing the physicsWorld Object
	unsigned int physicsId;

	glm::vec3 playerVelocity = glm::vec3(0.0f);
	float playerMass = 60;

	bool cameraForward = false;
	bool cameraBackWard = false;
	bool cameraRight = false;
	bool cameraLeft = false;

	
};

