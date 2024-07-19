#include "PlayerInventoryManager.h"

PlayerInventoryManager::PlayerInventoryManager(playerEntity* newPlayer, scene* newScene, Shader* newShader)
{
	this->currentPlayer = newPlayer;
	this->currentScene = newScene;
	this->itemShader = newShader;

	glm::mat4 leftHandMat = newPlayer->getLeftHandOffsetMatrix();
	glm::mat4 rightHandMat = newPlayer->getRightHandOffsetMatrix();

	this->leftHand = new playerHandSlot(leftHandMat);
	this->rightHand = new playerHandSlot(rightHandMat);
}

PlayerInventoryManager::~PlayerInventoryManager()
{

}

void PlayerInventoryManager::equipSlot(inventorySlots slot, std::shared_ptr<item> newItem)
{
	switch(slot)
	{
	case(LEFTHAND):
		this->leftHand->addItem(newItem,this->currentScene,this->itemShader);
		break;

	case(RIGHTHAND):
		this->rightHand->addItem(newItem, this->currentScene, this->itemShader);
		break;
	}
}

void PlayerInventoryManager::updateInventoryStatus()
{
	glm::mat4 leftHandMat = this->currentPlayer->getLeftHandTransform();
	glm::mat4 rightHandMat = this->currentPlayer->getRightHandTransform();
	transform* playerTransform = this->currentPlayer->getPlayersTransform();

	glm::vec3 rightHandDirection(1.0f);
	rightHandDirection = this->currentPlayer->getRightHandDirection();
	glm::vec3 leftHandDirection(1.0f);
	leftHandDirection = this->currentPlayer->getLeftHandDireciton();

	this->leftHand->updatePosition(this->currentScene, leftHandMat, *playerTransform, leftHandDirection);
	this->rightHand->updatePosition(this->currentScene, rightHandMat, *playerTransform, rightHandDirection);
}