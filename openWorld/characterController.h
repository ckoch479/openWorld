#pragma once


#include "PhysicsWorld.h"
#include "Scene.h"
#include "playerEntity.h"
#include "windowManager.h"

#include "Level.h"

#include "includes/glm/glm.hpp"
#include "Includes/glm/gtc/type_ptr.hpp"

//class for handling player movement and world collisions, will also automatically update the player transforms in scene and physics world
class characterController
{
public:
	
	characterController(playerEntity* newPlayer, scene* newScene, PhysicsWorld* newWorld ,Shader* shader);
	~characterController();

	void updateInputs(windowManager* manager);

	void updateController(float dt, Level currentLevel);

private:

	void addPlayerToScene(Shader* shader);

	void addPlayerToWorld();

	PhysicsWorld* world;
	scene* sceneObj;
	playerEntity* player; //for transforms and current action references
	//for referencing the scene and physicsWorld Objects
	std::string sceneId;
	unsigned int physicsId;

	glm::vec3 playerVelocity = glm::vec3(0.0f);
	float playerMass = 60;
};

