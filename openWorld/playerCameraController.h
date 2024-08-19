#pragma once

#include "includes/glm/glm.hpp"
#include "Includes/glm/gtc/type_ptr.hpp"
#include "glm/gtc/quaternion.hpp"

#include "Scene.h"
#include "Camera.h"

#ifndef PLAYERCAMERACONTROLLER_H
#define PLAYERCAMERACONTROLLER_H

class playerCameraController
{
public:

	playerCameraController();
	~playerCameraController();

	void updateController();

private:

	Camera* playerCamera;
	scene* sceneObj;
};

#endif