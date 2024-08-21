#pragma once

#include <iostream>
#include <vector>

#include "includes/glm/glm.hpp"
#include "Includes/glm/gtc/type_ptr.hpp"
#include "Includes/glm/gtc/quaternion.hpp"

#include "PhysicsWorld.h"
#include "orientedBoundingBox.h"

#include "playerActions.h"




#ifndef PLAYERMOTIONCONTROLLER_H
#define PLAYERMOTIONCONTROLLER_H

class playerMotionController
{
public:

	playerMotionController(orientedBoundingBox* playerCollider, playerActions* currentAction);

	~playerMotionController();

	void setPlayerTransforms(glm::vec3* pos, glm::quat* orient, glm::vec3* scale, glm::vec3* front, glm::vec3* right, glm::vec3* up);

	void updatePlayerMotion(float dt, playerActions* newAction);

	void changeMovementSpeed(float speed);

	void handleRotation(float dt, Camera* playerCamera);

private:

	void determineMovement(float dt);

	void applyMovement();

	void resolveCollisions();

	float calculateAngleDifference(glm::vec3* cameraFront, glm::vec3* playerFront);

	void rotatePlayerToCameraFront(glm::vec3* cameraFront, float dt);

	//base player speed
	float movementSpeed = 2.0f;
	glm::vec3 movementVector;

	glm::vec3* playerPosition;
	glm::quat* playerOrientation;
	glm::vec3* playerScale;

	glm::vec3* playerFront;
	glm::vec3* playerRight;
	glm::vec3* playerUp;

	glm::vec3* cameraFront;

	float rotationspeed = 2.0f;
	float freeRotationSlop = 2.0f;

	orientedBoundingBox* playerMainColldier;
	playerActions* currentAction;

};

#endif