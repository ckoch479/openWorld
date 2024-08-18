#pragma once

#include <iostream>

#include "playerEntity.h"
#include "characterController.h"
#include "PlayerInventoryManager.h"

#include "Scene.h"
#include "PhysicsWorld.h"
#include "Camera.h"
#include "Level.h"

#include "Entity.h"


#ifndef PLAYERMANAGER_H
#define PLAYERMANAGER_H

//this class is used to manage all of the players components such as the players inventory manager, health manager, entity class for rendering and ect

class playerManager : public Entity
{
public:
	playerManager(scene* newScene, PhysicsWorld* newWorld, windowManager* newManager, Shader* playerShader, Shader* itemShader, std::string modelFilePath, Camera* newCamera, Level* currentLevel);
	~playerManager();

	void update(float dt) override;

	void testItemSlots(std::shared_ptr<item> newItem);

	playerEntity* player;

private:

	characterController* controller;
	PlayerInventoryManager* inventoryManager;

	Shader* playerShader;
	Shader* itemShader;

	//current main systems being used for this player
	
	scene* currentScene;
	Camera* playerCamera;
	PhysicsWorld* currentWorld;
	windowManager* currentManager;
	Level* currentLevel;

	bool testSignal = false;


};

#endif // !PLAYERMANAGER_H