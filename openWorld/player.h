#pragma once

#include <iostream>
#include <vector>
#include <map>

#include "includes/glm/glm.hpp"
#include "Includes/glm/gtc/type_ptr.hpp"
#include "Includes/glm/gtc/quaternion.hpp"

#include "Entity.h"

#include "ResourceManager.h"
#include "objAnimator.h"

#include "playerActions.h"
#include "Model.h"
#include "skeleton.h"


#ifndef PLAYER_H
#define PLAYER_H

class player : public Entity
{
public:

	player();
	~player();

	void update(float dt);

private:

	playerActions currentAction;

	Model* playerModel; //eventually will be replaced by a vector or array of models for each individual part
	skeleton* playerSkeleton;

	//these variables are stored in the Entity class under protected but are placed here for clarity (mainly for me because im sorta dumb)
	glm::vec3* position;
	glm::quat* orientation;
	glm::vec3* scale;

	std::string* name;
	
};

#endif // !PLAYER_H