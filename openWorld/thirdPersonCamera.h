#pragma once

#include"glad/glad.h"
#include "Includes/glm/glm.hpp"
#include "Includes/glm/gtc/matrix_transform.hpp"

#ifndef THIRDPERSONCAMERA_H
#define THIRDPERSONCAMERA_H

//class that caclulates a third person camera given player position, direction, and input
class thirdPersonCamera
{
public:

	thirdPersonCamera();
	~thirdPersonCamera();

	glm::vec3 getPosition();

	float getYaw();

	float getPitch();

	void calculateCameraPosition(glm::vec3 playerPosition, glm::vec3 playerRotation);

	//this updates only the camera rotation given an x and y from the cursor
	void updateCameraRotation(float cursorX, float cursorY);

private:

	glm::vec3 cameraPosition;
	float Yaw;
	float Pitch;
	float zoom;

	float cameraSensitivity;
	float lastCursorX;
	float lastCursorY;
	bool firstUpdate = true;

	//radius from whatever our third person camera is attached to i.e. the player in most cases
	float radiusFromPoint;
	//this is a modifier used to allow the camera to move freely around the player without turning the player
	float cameraFreeRotationAngle; 

	glm::vec3 Front;
	glm::vec3 Up;
	glm::vec3 Right;
	glm::vec3 WorldUp;

};

#endif