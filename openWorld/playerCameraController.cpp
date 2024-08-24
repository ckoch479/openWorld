#include "playerCameraController.h"

playerCameraController::playerCameraController(Camera* playerCamera, scene* sceneObj, windowManager* inputManager)
{
	this->playerCamera = playerCamera;
	this->sceneObj = sceneObj;
	this->inputManager = inputManager;
}

playerCameraController::playerCameraController(renderContext* context, windowManager* inputManager)
{
	this->playerCamera = context->camera;
	this->sceneObj = context->sceneObj;
	this->inputManager = inputManager;
}

playerCameraController::playerCameraController()
{

}

playerCameraController::~playerCameraController()
{

}

void playerCameraController::updateController(float dt, glm::vec3 playerPos, glm::vec3* playerFront)
{
	//set zoom level:

	float scrollOffset = this->inputManager->getMouseScroll();
	this->mouseScroll = this->lastScroll - scrollOffset;
	this->playerCamera->setZoomLevel(this->mouseScroll);

	//camera position/orientation
	

	float mouseX = inputManager->getMouseX() - lastX;
	float mouseY = inputManager->getMouseY() - lastY;

	this->lastX = inputManager->getMouseX();
	this->lastY = inputManager->getMouseY();


	yaw += mouseX * sensitivity;
	pitch -= mouseY * sensitivity;
	pitch = std::clamp(pitch, -80.0f, 80.0f);
	
	glm::vec3 direction(1.0f);

	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction = glm::normalize(direction);

	glm::vec3 front = direction;
	glm::vec3 right = glm::normalize(glm::cross(front,glm::vec3(0, 1, 0)));
	glm::vec3 up = glm::normalize(glm::cross(front, right));

	this->targetPosition = playerPos + *playerFront * 0.5f + right * 0.4f + glm::vec3(0, 1.4, 0); //fine fine tuning later, doing decent for now

	glm::vec3 cameraPosition = targetPosition - direction * distanceFromTarget + right * 0.4f;// +offset;
	this->playerCamera->setPosition(cameraPosition);
	this->playerCamera->setTarget(this->targetPosition  /*+ (right * 0.3f)*/);
	this->playerCamera->setOrientation(this->yaw, this->pitch);
	this->playerCamera->setZoomLevel(30);


	this->playerCamera->update(dt);

	
	
}

Camera* playerCameraController::getCamera()
{
	return this->playerCamera;
}

glm::vec3* playerCameraController::getTargetPosition()
{
	return &this->targetPosition;
}