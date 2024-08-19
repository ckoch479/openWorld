#pragma once

#include <iostream>
#include <vector>

#include "Includes/glm/glm.hpp"
#include "Includes/glm/gtc/type_ptr.hpp"
#include "Includes/glm/gtc/quaternion.hpp"

#include "Model.h"
#include "Scene.h"
#include "Shader.h"

#ifndef PLAYERRENDERER_H
#define PLAYERRENDERER_H
class playerRenderer
{
public:
	playerRenderer(scene* sceneObj, Shader* playerShader, Model* playerModel);

	~playerRenderer();

	void setAnimTransforms(std::vector <glm::mat4>* animMats);

	void setTransform(glm::vec3* pos, glm::quat* Orient, glm::vec3* scale);

	void changePlayerModel(Model* newModel);

	void addPlayerToScene();

	void updatePlayerRender();

private:

	std::string sceneId;

	scene* sceneObj;
	Model* currentPlayerModel;
	Shader* playerShader;

	std::vector <glm::mat4>* animMats;

	glm::vec3* playerPos;
	glm::quat* playerOrient;
	glm::vec3* playerScale;
};

#endif