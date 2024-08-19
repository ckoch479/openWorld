#include "playerCameraController.h"

playerCameraController::playerCameraController()
{

}

playerCameraController::~playerCameraController()
{

}

void playerCameraController::updateController()
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
}