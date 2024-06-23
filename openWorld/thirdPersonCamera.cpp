#include "thirdPersonCamera.h"

thirdPersonCamera::thirdPersonCamera()
{
	glm::vec3 cameraPosition = glm::vec3(0.0f);
	float Yaw = 0.0;
	float Pitch = 0.0;
	float zoom = 0.0;

	float cameraSensitivity = 0.1;
	float lastCursorX = 0;
	float lastCursorY = 0;

	float radiusFromPoint = 5;
	float cameraFreeRotationAngle = 0;

	glm::vec3 Front = glm::vec3(0.0,0.0,-1.0);
	glm::vec3 Up = glm::vec3(0.0,1.0,0.0);
	glm::vec3 Right = glm::vec3(1.0,0.0,0.0);
	glm::vec3 WorldUp = glm::vec3(0.0,1.0,0.0);
}

thirdPersonCamera::~thirdPersonCamera()
{

}

glm::vec3 thirdPersonCamera::getPosition()
{
	return this->cameraPosition;
}

float thirdPersonCamera::getYaw()
{
	return this->Yaw;
}

float thirdPersonCamera::getPitch()
{
	return this->Pitch;
}

void thirdPersonCamera::calculateCameraPosition(glm::vec3 playerPosition, glm::vec3 playerRotation)
{
	float horizontalFromPlayer = radiusFromPoint * cos(Pitch);
	float verticalDistance = radiusFromPoint * sin(Pitch);
	this->Yaw = 180 - playerRotation.y + this->cameraFreeRotationAngle;
	float Xoffset = horizontalFromPlayer * sin(playerRotation.y + cameraFreeRotationAngle);
	float Zoffset = horizontalFromPlayer * cos(playerRotation.y + cameraFreeRotationAngle);
	this->cameraPosition.x = playerPosition.x - Xoffset;
	this->cameraPosition.y = playerPosition.y + verticalDistance;
	this->cameraPosition.z = playerPosition.z - Zoffset;
}

void thirdPersonCamera::updateCameraRotation(float cursorX, float cursorY)
{
	
	if (firstUpdate == true)
	{
		lastCursorX = cursorX;
		lastCursorY = cursorY;
		firstUpdate = false;
	}

	float xoffset = cursorX - this->lastCursorX; //create an offset value from where the mouse last was for relative camera movement
	float yoffset = this->lastCursorY - cursorY;

	xoffset *= cameraSensitivity;
	yoffset *= cameraSensitivity;

	Pitch += yoffset * 0.01;

	this->cameraFreeRotationAngle += xoffset * 0.01;

	if (Pitch > 89.0f)
	{
		Pitch = 89.0f;
	}
	if (Pitch < -89.0f)
	{
		Pitch = -89.0f;
	}

	if (Yaw > 360.0f)
	{
		this->cameraFreeRotationAngle = 360.0f;
	}
	if (Yaw < -360.0f)
	{
		this->cameraFreeRotationAngle = -360.0f;
	}
}
