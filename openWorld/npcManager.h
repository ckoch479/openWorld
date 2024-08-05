#pragma once

#include <iostream>

#include "npcEntity.h"
#include "npcController.h"

#include "Scene.h"
#include "PhysicsWorld.h"
#include "Level.h"


#ifndef NPCMANAGER_H
#define NPCMANAGER_H


class npcManager
{
public:
	npcManager(scene* newScene, PhysicsWorld* newWorld, Shader* npcShader, std::string modelFilePath,std::string npcName);
	~npcManager();

	void updateManager(float dt, Level* currentLevel);

private:

	npcEntity* NPC;
	npcController* controller;

	Shader* npcShader;

	//current main systems being used for this NPC
	scene* currentScene;
	PhysicsWorld* currentWorld;
	
};

#endif