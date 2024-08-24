#pragma once

#include <iostream>
#include <vector>

#include "Includes/glm/glm.hpp"
#include "Includes/glm/gtc/type_ptr.hpp"
#include "Includes/glm/gtc/quaternion.hpp"

#include "Model.h"
#include "Scene.h"
#include "Shader.h"
#include "renderContext.h"
#include "renderableModel.h"

#ifndef PLAYERRENDERER_H
#define PLAYERRENDERER_H
class playerRenderer
{
public:
	playerRenderer(scene* sceneObj, Shader* playerShader, Model* playerModel);
	
	playerRenderer(renderContext* context, Model* playerModel);

	~playerRenderer();

	void setAnimTransforms(std::vector <glm::mat4>* animMats);

	void setTransform(glm::vec3* pos, glm::quat* Orient, glm::vec3* scale);

	void changePlayerModel(Model* newModel);

	void addPlayerToScene();

	void updatePlayerRender();

	void updatePlayerModels();

	void addRightHandItem(renderableModel newItem);

	void updateRightHandTransform(glm::vec3* pos, glm::quat* orient, glm::vec3* scale);

private:

	std::string sceneId;

	scene* sceneObj;
	Model* currentPlayerModel;
	Shader* playerShader;

	std::vector <glm::mat4>* animMats;

	glm::vec3* playerPos;
	glm::quat* playerOrient;
	glm::vec3* playerScale;


	//more for testing purposes down here just left and right hand models for now, i want to ensure my math is correct when i try to apply the transforms before implimenting multiple models
	//in the case of a onehanded item being in the players hand that can be held with both hands the dominant hand (rightHand) holds the data and non dominant is left alone
	Shader* handShader; //uses the static add scene object for now no items are animated at least not yet
	glm::vec3* leftHandPos;
	glm::quat* leftHandOrient;
	glm::vec3* leftHandScale;
	Model* leftHandModel;
	std::string leftHandSceneId;

	

	glm::vec3* rightHandPos;
	glm::quat* rightHandOrient;
	glm::vec3* rightHandScale;
	Model* rightHandModel;
	std::string rightHandSceneId;

};

#endif