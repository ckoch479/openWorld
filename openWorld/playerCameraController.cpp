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

void playerCameraController::updateController(float dt, glm::vec3 playerPos)
{
	/*if(inputManager->rightClick())
		{
				this->playerCamera->Zoom = 25.0f;
		}
		if(!inputManager->rightClick())
		{
				this->playerCamera->Zoom = 45.0f;
		}*/

	//third person camera controls---------------------------------------------------------
	//mouse position;
	//float lastx = cursorX;
	//float lasty = cursorY;

	//manager->getMousePosition(&cursorX, &cursorY);

	//float xOffset = cursorX - lastx;
	//float yOffset = lasty - cursorY;
	//playerCamera->ProcessMouseMovement(xOffset, yOffset, true, glm::vec3(0, 1.5, 0) + this->player->getPlayersTransform()->position , 0);

	/*if (playerCamera->isThirdPerson())
	{
		transform* newTransform = this->player->getPlayersTransform();
		newTransform->orientation = glm::rotate(glm::toMat4(newTransform->orientation), xOffset * 0.01f, glm::vec3(0, 1, 0));
		this->player->setPlayerTransform(*newTransform);

	}*/

	//camera control
	//if (inputManager->checkKey(49))//1 key
	//{
	//	playerCamera->setCameraFreeCam();
	//}
	//if (inputManager->checkKey(50))//2 key
	//{
	//	playerCamera->setCameraThirdPerson(2.6);
	//}

	//if (!playerCamera->isThirdPerson())
	//{
	//	if (inputManager->checkKey(65)) //a
	//	{
	//		this->cameraLeft = true;
	//	}

	//	if (inputManager->checkKey(83)) //s
	//	{
	//		this->cameraBackWard = true;
	//	};

	//	if (inputManager->checkKey(68)) //d
	//	{
	//		this->cameraRight = true;
	//	};

	//	if (inputManager->checkKey(87)) //w
	//	{
	//		this->cameraForward = true;
	//	};
	//}

	//set zoom level:

	float scrollOffset = this->inputManager->getMouseScroll();
	this->mouseScroll = this->lastScroll - scrollOffset;
	this->playerCamera->setZoomLevel(this->mouseScroll);

	//camera position/orientation
	this->targetPosition = playerPos;

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
	glm::vec3 right = glm::normalize(glm::cross(glm::vec3(0, 1, 0), front));
	glm::vec3 up = glm::normalize(glm::cross(front, right));

	glm::vec3 cameraPosition = targetPosition - direction * distanceFromTarget;// +offset;
	this->playerCamera->setPosition(cameraPosition);
	this->playerCamera->setTarget(this->targetPosition + glm::vec3(0,1.3,0) + (right * -0.2f));

	this->playerCamera->update(dt);
	
}

Camera* playerCameraController::getCamera()
{
	return this->playerCamera;
}