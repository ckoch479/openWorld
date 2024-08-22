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

	recalculateDirections();
	determineMovement(dt);
	applyMovement();
}

void playerMotionController::recalculateDirections()
{
	*this->playerFront = glm::normalize(glm::vec4(0, 0, 1, 0.0) * glm::toMat4(*this->playerOrientation));
	*this->playerRight = glm::normalize(glm::vec4(1, 0, 0, 0.0) * glm::toMat4(*this->playerOrientation));
}

void playerMotionController::handleRotation(float dt, Camera* playerCamera)
{
	this->cameraFront = playerCamera->getFront();
	this->cameraRight = playerCamera->getRight();
	this->cameraUp = playerCamera->getUp();
	//get the angle difference between player front and camera front
	//float angleDifference = calculateAngleDifference(cameraFront,this->playerFront);
	
	//check the camera/player front difference
	if(*currentAction == aiming || *currentAction == walkForward || *currentAction == jogForward)
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
		this->movementVector = glm::vec3(this->cameraFront->x,0.0,this->cameraFront->z) * movementSpeed * dt;
		break;
	case(walkLeft):
		this->movementVector = glm::vec3(this->cameraRight->x, 0.0, this->cameraRight->z) * -1.0f * movementSpeed * dt;
		rotatePlayerToCameraFront(&this->movementVector, dt);
		break;

	case(walkRight):
		this->movementVector = glm::vec3(this->cameraRight->x, 0.0, this->cameraRight->z)  * movementSpeed * dt;
		rotatePlayerToCameraFront(&this->movementVector, dt);
		break;

	case(walkBack):
		this->movementVector = glm::vec3(this->cameraFront->x, 0.0, this->cameraFront->z) * -1.0f * movementSpeed * dt;
		rotatePlayerToCameraFront(&this->movementVector, dt);
		break;

	case(walkForwardLeft):
		glm::vec3 frontVec = glm::vec3(this->cameraFront->x, 0.0, this->cameraFront->z);
		glm::vec3 leftVec = glm::vec3(this->cameraRight->x, 0.0, this->cameraRight->z) * -1.0f ;
		this->movementVector = glm::mix(frontVec,leftVec,0.5) * movementSpeed * dt;
		rotatePlayerToCameraFront(&this->movementVector, dt);
		break;

	case(walkForwardRight):
		frontVec = glm::vec3(this->cameraFront->x, 0.0, this->cameraFront->z);
		leftVec = glm::vec3(this->cameraRight->x, 0.0, this->cameraRight->z);
		this->movementVector = glm::normalize(glm::mix(frontVec, leftVec, 0.5)) * movementSpeed * dt;
		rotatePlayerToCameraFront(&this->movementVector, dt);
		break;

	case(walkBackLeft):
		frontVec = glm::vec3(this->cameraFront->x, 0.0, this->cameraFront->z) * -1.0f;
		leftVec = glm::vec3(this->cameraRight->x, 0.0, this->cameraRight->z) * -1.0f;
		this->movementVector = glm::normalize(glm::mix(frontVec, leftVec, 0.5)) * movementSpeed * dt;
		rotatePlayerToCameraFront(&this->movementVector, dt);
		break;

	case(walkBackRight):
		frontVec = glm::vec3(this->cameraFront->x, 0.0, this->cameraFront->z) * -1.0f;
		leftVec = glm::vec3(this->cameraRight->x, 0.0, this->cameraRight->z);
		this->movementVector = glm::normalize(glm::mix(frontVec, leftVec, 0.5)) * movementSpeed * dt;
		rotatePlayerToCameraFront(&this->movementVector, dt);
		break;

	case(jogForwardLeft):
		frontVec = glm::vec3(this->cameraFront->x, 0.0, this->cameraFront->z);
		leftVec = glm::vec3(this->cameraRight->x, 0.0, this->cameraRight->z) * -1.0f;
		this->movementVector = glm::normalize(glm::mix(frontVec, leftVec, 0.5)) * movementSpeed * 2.5f * dt;
		rotatePlayerToCameraFront(&this->movementVector, dt);
		break;

	case(jogForwardRight):
		frontVec = glm::vec3(this->cameraFront->x, 0.0, this->cameraFront->z);
		leftVec = glm::vec3(this->cameraRight->x, 0.0, this->cameraRight->z);
		this->movementVector = glm::normalize(glm::mix(frontVec, leftVec, 0.5)) * movementSpeed * 2.5f * dt;
		rotatePlayerToCameraFront(&this->movementVector, dt);
		break;

	case(jogBackLeft):
		frontVec = glm::vec3(this->cameraFront->x, 0.0, this->cameraFront->z) * -1.0f;
		leftVec = glm::vec3(this->cameraRight->x, 0.0, this->cameraRight->z) * -1.0f;
		this->movementVector = glm::normalize(glm::mix(frontVec, leftVec, 0.5)) * movementSpeed * 2.5f * dt;
		rotatePlayerToCameraFront(&this->movementVector, dt);
		break;

	case(jogBackRight):
		frontVec = glm::vec3(this->cameraFront->x, 0.0, this->cameraFront->z) * -1.0f;
		leftVec = glm::vec3(this->cameraRight->x, 0.0, this->cameraRight->z);
		this->movementVector = glm::normalize(glm::mix(frontVec, leftVec, 0.5)) * movementSpeed * 2.5f * dt;
		rotatePlayerToCameraFront(&this->movementVector, dt);
		break;

	case(turnLeft):
		break;

	case(turnRight):
		break;

	case(jogForward):
		this->movementVector = glm::vec3(this->cameraFront->x, 0.0, this->cameraFront->z) * movementSpeed * 2.5f * dt;

		break;

	case(jogLeft):
		this->movementVector = glm::vec3(this->cameraRight->x, 0.0, this->cameraRight->z) * -1.0f * movementSpeed * 2.5f * dt;
		rotatePlayerToCameraFront(&this->movementVector, dt);
		break;

	case(jogRight):
		this->movementVector = glm::vec3(this->cameraRight->x, 0.0, this->cameraRight->z)  * movementSpeed * 2.5f * dt;
		rotatePlayerToCameraFront(&this->movementVector, dt);
		break;

	case(jogBack):
		this->movementVector = glm::vec3(this->cameraFront->x, 0.0, this->cameraFront->z) * -1.0f * movementSpeed * 2.5f * dt;
		rotatePlayerToCameraFront(&this->movementVector, dt); //this just orients the player to a specific direction over time
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

	case(aiming):
		this->movementVector = glm::vec3(0, 0, 0);
		rotatePlayerToCameraFront(this->cameraFront, dt);
		break;

	case(walkAiming):
		this->movementVector = glm::vec3(this->cameraFront->x, 0.0, this->cameraFront->z) * movementSpeed * dt;
		rotatePlayerToCameraFront(&this->movementVector, dt);
		break;

	case(aimingStepBack):
		this->movementVector = glm::vec3(this->cameraFront->x, 0.0, this->cameraFront->z) * -1.0f * movementSpeed * dt;
		rotatePlayerToCameraFront(this->cameraFront, dt);
		break;

	case(aimingStepLeft):
		this->movementVector = glm::vec3(this->cameraRight->x, 0.0, this->cameraRight->z) * -1.0f * movementSpeed * dt;
		rotatePlayerToCameraFront(this->cameraFront, dt);
		break;

	case(aimingStepRight):
		this->movementVector = glm::vec3(this->cameraRight->x, 0.0, this->cameraRight->z) * movementSpeed * dt;
		rotatePlayerToCameraFront(this->cameraFront, dt);
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
	glm::vec3 cameraDirection = glm::vec3(cameraFront->x, 0.0f, -cameraFront->z);
	*this->playerOrientation = glm::slerp(*playerOrientation, glm::quatLookAt(glm::normalize(cameraDirection), glm::vec3(0, 1, 0)), this->rotationspeed * dt);
}