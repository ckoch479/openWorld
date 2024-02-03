#pragma once

#include"glad/glad.h"
#include "Includes/glm/glm.hpp"
#include "Includes/glm/gtc/matrix_transform.hpp"

#include <vector>
#include <iostream>

#ifndef CAMERA_H
#define CAMERA_H

enum Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

// Default camera values
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

class Camera
{
public:
	  glm::vec3 CameraPosition;
	  glm::vec3 Front;
	  glm::vec3 Up;
	  glm::vec3 Right;
	  glm::vec3 WorldUp;

	  float Yaw;
	  float Pitch;
	  
	  float MovementSpeed;
	  float MouseSensitivity;
	  float Zoom;

	  //constructor with vectors
	  Camera(glm::vec3 position = glm::vec3(0.0, 0.0, 0.0), glm::vec3 up = glm::vec3(0.0, 1.0, 0.0), float yaw = YAW, float pitch = PITCH) : Front(glm::vec3(0.0, 0.0, -1.0)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM) 
	  {
		  CameraPosition = position;
		  WorldUp = up;
		  Yaw = yaw;
		  Pitch = pitch;
		  updateCameraVectors();
	  }

	  //constructor with scala values
	  Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM) 
	  {
		  CameraPosition = glm::vec3(posX, posY, posZ);
		  WorldUp = glm::vec3(upX, upY, upZ);
		  Yaw = yaw;
		  Pitch = pitch;
		  updateCameraVectors();
	  }
	 
	  //returns view matrix calculated using the look at matrix and euler angles
	  glm::mat4 GetViewMatrix();

	  //process input for base camera movement
	  void ProcessKeyboard(Camera_Movement direction, float deltaTime);

	  void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);

	  void ProcessMouseScroll(float yoffset);

	  void setPosition(glm::vec3 position);

	  void setTarget(glm::vec3 focusTarget);

	  void setUp(glm::vec3 cameraUp);

	  void updateCamera(glm::vec3 target, float pitch, float yaw, float Radius);

private:
	void updateCameraVectors();
};

#endif