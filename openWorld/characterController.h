#pragma once


#include "PhysicsWorld.h"
#include "Scene.h"
#include "playerEntity.h"
#include "windowManager.h"

#include "includes/glm/glm.hpp"
#include "Includes/glm/gtc/type_ptr.hpp"

//class for handling player movement and world collisions, will also automatically update the player transforms in scene and physics world
class characterController
{
public:
	
	characterController(playerEntity* newPlayer, scene* newScene, PhysicsWorld* newWorld ,Shader* shader);
	~characterController();

	void updateInputs(windowManager* manager);

	void updateController(float dt);

private:

	void addPlayerToScene(Shader* shader);

	void addPlayerToWorld();

	PhysicsWorld* world;
	scene* sceneObj;
	playerEntity* player;
	//for referencing the scene and physicsWorld Objects
	std::string sceneId;
	unsigned int physicsId;
};

