#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/quaternion.hpp"
#include "includes/glm/gtx/quaternion.hpp"

#include "playerEntity.h"

#include "item.h"
#include "gameObjectManager.h"
#include "playerHandSlot.h"
#include "inventorySlot.h"

#include "scene.h"
#include "shader.h"

#ifndef PLAYERINVENTORYMANAGER_H
#define PLAYERINVENTORYMANAGER_H

enum inventorySlots
{
	LEFTHAND,
	RIGHTHAND,
};

class PlayerInventoryManager
{
public:

	PlayerInventoryManager(playerEntity* newPlayer, scene* newScene, Shader* newShader);
	~PlayerInventoryManager();

	void equipSlot(inventorySlots slot, std::shared_ptr<item> newItem);

	void updateInventoryStatus();

private:

	playerEntity* currentPlayer;
	Shader* itemShader;
	scene* currentScene;

	//player slots:

	playerHandSlot* leftHand;
	playerHandSlot* rightHand;


};

#endif // !PLAYERINVENTORYMANAGER_H
