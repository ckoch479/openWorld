#pragma once

#include "includes/glm/glm.hpp"
#include "Includes/glm/gtc/type_ptr.hpp"
#include "Includes/glm/gtc/quaternion.hpp"
#include <glm/gtx/string_cast.hpp>
#include "glm/gtx/matrix_decompose.hpp"

#include "Model.h"
#include "playerRenderer.h"
#include "objAnimator.h"
#include "item.h"



#ifndef PLAYERMODELMANAGER_H
#define PLAYERMODELMANAGER_H

class playerModelManager
{
public:

	playerModelManager(Model* defaultModel, objAnimator* playerAnimator, playerRenderer* renderer);
	~playerModelManager();

	void changePlayerModel(Model* model);

	void setPlayerTransform(glm::vec3* newPos, glm::quat* newOrient, glm::vec3* newScale);

	//this function is called by the playerInventory manager and passes in a new item for use in rendering, 
	//the model manager is in charge of rendering this item and making sure it follows the bone sockets 
	void setEquipedItem(item* newItem); //eventually will be fully implimented properly, mainly will be used for testing, assuming its the right hand

	void removeEquipedItem();

	//sets the animation matrices for the player model (and maybe eventually held items) and set transforms
	void updateManager();

private:

	void updateEquipedItemTransform();

	Model* playerModel;
	glm::vec3* playerTransform;
	glm::quat* playerOrient;
	glm::vec3* playerScale;

	Model* playerHandModel;
	Shader* handShader;
	glm::vec3* equipedPos;
	glm::quat* equipedOrient;
	glm::vec3* equipedScale;

	objAnimator* playerAnimator;
	playerRenderer* renderer;
};

#endif