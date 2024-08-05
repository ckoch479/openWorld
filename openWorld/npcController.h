#pragma once

#include "PhysicsWorld.h"
#include "Scene.h"

#include "npcEntity.h"
#include "Level.h"

#include "Includes/glm/glm.hpp"
#include "Includes/glm/gtc/type_ptr.hpp"

#ifndef NPCCONTROLLER_H
#define NPCCONTROLLER_H

class npcController
{
public:

	npcController(npcEntity* newNPC, PhysicsWorld* newWorld);

	~npcController();

	//void updateInputs(windowManager* manager);

	void updateController(float dt, Level currentLevel);
private:

	void addNpcToWorld();

	PhysicsWorld* world;
	npcEntity* NPC; //for transforms and current action references

	//for referencing the physicsWorld Object
	unsigned int physicsId;

	glm::vec3 velocity = glm::vec3(0.0f);
	float mass = 60;
};

#endif