#pragma once

#include <iostream>
#include <vector>
#include <unordered_map>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/quaternion.hpp"
#include "includes/glm/gtx/quaternion.hpp"

#include "player.h"

#include "item.h"
#include "itemSlot.h"

#ifndef PLAYERINVENTORYMANAGER_H
#define PLAYERINVENTORYMANAGER_H

class PlayerInventoryManager
{
public:

	enum class Slot
	{
	Head,
	Torso,
	Legs,
	Hands,
	Feet,
	RightHand,
	LeftHand,
	Back,
	};

	PlayerInventoryManager();
	~PlayerInventoryManager();

	void equipItem(Slot slot, item* newItem);

	void unEquipItem(Slot slot);

	item* getEquipedItem(Slot slot);

	void updatePlayerState();

private:

	void updatePlayerAnimations();

	std::unordered_map<Slot, itemSlot> equippedItems;

};

#endif // !PLAYERINVENTORYMANAGER_H
