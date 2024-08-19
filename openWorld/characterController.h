#pragma once

#include <iostream>
#include <vector>
#include <unordered_map>

#include "includes/glm/glm.hpp"
#include "Includes/glm/gtc/type_ptr.hpp"
#include "glm/gtc/quaternion.hpp"

#include "windowManager.h"
#include "playerActions.h"

//class for handling player movement and world collisions, will also automatically update the player transforms in physics world and pass transform to player entity
class characterController
{
public:
	
	characterController(windowManager* manager);

	~characterController();

	playerActions updateController();

private:

	void updateInputs();

	void setDefaultMappings();

	void checkCombinationKeys();

	windowManager* inputManager;
	
	//unorderd map is used to map keys to actions so the keymapping can be redone to the players liking
	std::unordered_map<int, playerActions> keyMap; //this does nothing right now
	std::unordered_map<int, bool> keyStates;
};

