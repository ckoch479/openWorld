#pragma once

#include <iostream>

#include "includes/glm/glm.hpp"
#include "Includes/glm/gtc/type_ptr.hpp"
#include "Includes/glm/gtc/quaternion.hpp"
#include <glm/gtx/string_cast.hpp>

#include "Entity.h"

#include "Model.h"

#ifndef ITEM_H
#define ITEM_H


class item
{

public:



protected:
	
	glm::vec3* positionPtr;
	glm::quat* orientPtr;
	glm::vec3* scalePtr;

	Model* itemModel;

private:

	
};

#endif // !ITEM_H