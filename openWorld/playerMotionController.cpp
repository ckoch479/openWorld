#include "playerMotionController.h"

playerMotionController::playerMotionController(orientedBoundingBox* playerCollider, playerActions* currentAction)
{
	this->playerMainColldier = playerCollider;
	this->currentAction = currentAction;

	this->movementVector = glm::vec3(0.0f, 0.0f, 0.0f);
}

playerMotionController::~playerMotionController()
{

}

void playerMotionController::setPlayerTransforms(glm::vec3* pos, glm::quat* orient, glm::vec3* scale, glm::vec3* front, glm::vec3* right, glm::vec3* up)
{
	this->playerPosition = pos;
	this->playerOrientation = orient;
	this->playerScale = scale;

	this->playerFront = front;
	this->playerRight = right;
	this->playerUp = up;
}

void playerMotionController::updatePlayerMotion(float dt, playerActions* newAction)
{
	this->currentAction = newAction;

	determineMovement(dt);
	applyMovement();
}

void playerMotionController::handleRotation(float dt, Camera* playerCamera)
{
	this->cameraFront = playerCamera->getFront();
	//get the angle difference between player front and camera front
	float angleDifference = calculateAngleDifference(cameraFront,this->playerFront);
	
	//check the camera/player front difference
	if(abs(angleDifference) > freeRotationSlop || *currentAction == aimPistol)
	{
		rotatePlayerToCameraFront(this->cameraFront,dt);
	}
	
	//if true rotate player to face the camera direction
}

void playerMotionController::determineMovement(float dt)
{
	switch(*this->currentAction)
	{
	case(idle):
		//do nothing youre idling
		this->movementVector = glm::vec3(0, 0, 0);
		break;
	case(walkForward):
		this->movementVector = *this->playerFront * movementSpeed * dt;
		break;
	case(walkLeft):
		this->movementVector = *this->playerRight * -1.0f * movementSpeed * dt;
		break;

	case(walkRight):
		this->movementVector = *this->playerRight * movementSpeed * dt;
		break;

	case(walkBack):
		this->movementVector = *this->playerFront * -1.0f * movementSpeed * dt;
		break;

	case(turnLeft):
		break;

	case(turnRight):
		break;

	case(jogForward):
		this->movementVector = *this->playerFront * movementSpeed * 2.0f * dt;
		break;

	case(jogLeft):
		this->movementVector = *this->playerRight * -1.0f * movementSpeed * 2.0f * dt;
		break;

	case(jogRight):
		this->movementVector = *this->playerRight * movementSpeed * 2.0f * dt;
		break;

	case(jogBack):
		this->movementVector = *this->playerFront * -1.0f * movementSpeed * 2.0f * dt;
		break;

	case(sprintForward):
		break;

	case(sprintLeft):
		break;

	case(sprintRight):
		break;

	case(jumpForward):
		break;

	case(jumpLeft):
		break;

	case(jumpRight):
		break;

	case(jumpBack):
		break;

	case(jump):
		break;

	case(evading):
		break;
	}
}

void playerMotionController::changeMovementSpeed(float speed)
{
	this->movementSpeed = speed;
}

void playerMotionController::applyMovement()
{
	*this->playerPosition += this->movementVector;
}

void playerMotionController::resolveCollisions()
{
	//check physics world for collisions with the player collider

	//get the correction vector from physics world

	//*playerPosition += correctionVector;
}

float playerMotionController::calculateAngleDifference(glm::vec3* cameraFront, glm::vec3* playerFront)
{
	float dotProduct = glm::dot(glm::normalize(*cameraFront), glm::normalize(*playerFront));
	return glm::degrees(acos(glm::clamp(dotProduct, -1.0f, 1.0f)));
}

void playerMotionController::rotatePlayerToCameraFront(glm::vec3* cameraFront, float dt)
{
	*this->playerOrientation = glm::slerp(*playerOrientation, glm::quatLookAt(glm::normalize(*cameraFront), glm::vec3(0, 1, 0)), this->rotationspeed * dt);
}