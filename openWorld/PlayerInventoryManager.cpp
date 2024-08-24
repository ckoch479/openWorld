#include "PlayerInventoryManager.h"

PlayerInventoryManager::PlayerInventoryManager(playerEntity* newPlayer, scene* newScene, Shader* newShader)
{

}

PlayerInventoryManager::~PlayerInventoryManager()
{

}

void PlayerInventoryManager::equipSlot(inventorySlots slot, std::shared_ptr<item> newItem)
{
	
}

void PlayerInventoryManager::updateInventoryStatus()
{
	/*glm::mat4 leftHandMat = this->currentPlayer->getLeftHandTransform();
	glm::mat4 rightHandMat = this->currentPlayer->getRightHandTransform();
	transform* playerTransform = this->currentPlayer->getPlayersTransform();

	rightHandMat = rightHandMat * glm::inverse(this->currentPlayer->getRightHandOffsetMatrix());

	this->leftHand->updatePosition(this->currentScene, leftHandMat, *playerTransform);
	this->rightHand->updatePosition(this->currentScene, rightHandMat, *playerTransform);*/
}