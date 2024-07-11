#pragma once

#include <iostream>

#include "playerEntity.h"
#include "characterController.h"
#include "PlayerInventoryManager.h"

#include "Scene.h"
#include "PhysicsWorld.h"
#include "Camera.h"


#ifndef PLAYERMANAGER_H
#define PLAYERMANAGER_H

//this class is used to manage all of the players components such as the players inventory manager, health manager, entity class for rendering and ect

class playerManager
{
public:
	playerManager(scene* newScene, PhysicsWorld* newWorld, windowManager* newManager,Shader* playerShader, Shader* itemShader, std::string modelFilePath, Camera* newCamera);
	~playerManager();

	void updateManager(float dt, Level* currentLevel);

	void testItemSlots(std::shared_ptr<item> newItem);

private:

	playerEntity* player;
	characterController* controller;
	PlayerInventoryManager* inventoryManager;

	Shader* playerShader;
	Shader* itemShader;

	//current main systems being used for this player
	
	scene* currentScene;
	Camera* playerCamera;
	PhysicsWorld* currentWorld;
	windowManager* currentManager;


};

#endif // !PLAYERMANAGER_H