#pragma once

#include "Scene.h"
#include "Shader.h"
#include "renderingInfoDefinitions.h"
#include "animationDataDefinitions.h"
#include "ResourceManager.h"

#include "includes/glm/glm.hpp"
#include "includes/glm/gtc/type_ptr.hpp"
#include "includes/glm/gtc/quaternion.hpp"
//#include "includes/glm/gtx/quaternion.hpp"

#ifndef RENDERABLE_H
#define RENDERABLE_H

class renderable
{
public:

	renderable(std::string uniqueID);
	~renderable();

	void loadModel(std::string filePath);

	void addToScene(Shader* shader, scene* sceneObj);

	void addToScene(Shader* shader, scene* sceneObj, bool isAnimated);

	void removeFromScene();

	void setIsAnimated(bool setter);

	void updateSceneTransform(glm::vec3 position, glm::quat orientation, glm::vec3 scale);

private:

	bool animated = false;
	Model* objModel = nullptr;
	scene* sceneObj = nullptr;
	Shader* objShader = nullptr;
	std::string uniqueID = "NULL"; //id used by the EntityManager
	std::string sceneID = "NULL";
};

#endif