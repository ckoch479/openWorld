#pragma once

#include <iostream>
#include <algorithm>
#include <cstdint>

#include "includes/glm/glm.hpp"
#include "Includes/glm/gtc/type_ptr.hpp"
#include "glm/gtc/quaternion.hpp"

#include "Scene.h"
#include "Camera.h"
#include "windowManager.h"
#include "renderContext.h"

#ifndef PLAYERCAMERACONTROLLER_H
#define PLAYERCAMERACONTROLLER_H

class playerCameraController
{
public:

	playerCameraController(Camera* playerCamera, scene* sceneObj, windowManager* inputManager);
	
	playerCameraController(renderContext* context, windowManager* inputManager);

	playerCameraController();


	~playerCameraController();

	void updateController(float dt, glm::vec3 playerPos);

private:

	Camera* playerCamera;
	scene* sceneObj;
	windowManager* inputManager;
	

	float distanceFromTarget = 5.0f;

	float pitch = 10.0f;
	float yaw = -90.0f;

	float sensitivity = 0.1f;
	glm::vec3 offset = glm::vec3(0,2,distanceFromTarget);
	glm::vec3 targetPosition = glm::vec3(0,0,0);
};

#endif