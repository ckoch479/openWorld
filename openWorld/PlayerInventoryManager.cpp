#include "PlayerInventoryManager.h"

PlayerInventoryManager::PlayerInventoryManager()
{

}

PlayerInventoryManager::~PlayerInventoryManager()
{

}

void PlayerInventoryManager::equipItem(Slot slot, item* newItem)
{
	this->equippedItems[slot].storeItem(newItem);
	updatePlayerState();
}

void PlayerInventoryManager::unEquipItem(Slot slot)
{
	this->equippedItems[slot].removeItem();
	updatePlayerState();
}

item* PlayerInventoryManager::getEquipedItem(Slot slot)
{
	item* inventoryItem = this->equippedItems[slot].getItem();
	if(inventoryItem)
	{
		return inventoryItem;
	}
	else
	{
		return nullptr;
	}
}

void PlayerInventoryManager::updatePlayerState()
{

}

void PlayerInventoryManager::updatePlayerAnimations()
{

}

//void PlayerInventoryManager::equipSlot()
//{
//	
//}

//void PlayerInventoryManager::updateInventoryStatus()
//{
//	/*glm::mat4 leftHandMat = this->currentPlayer->getLeftHandTransform();
//	glm::mat4 rightHandMat = this->currentPlayer->getRightHandTransform();
//	transform* playerTransform = this->currentPlayer->getPlayersTransform();
//
//	rightHandMat = rightHandMat * glm::inverse(this->currentPlayer->getRightHandOffsetMatrix());
//
//	this->leftHand->updatePosition(this->currentScene, leftHandMat, *playerTransform);
//	this->rightHand->updatePosition(this->currentScene, rightHandMat, *playerTransform);*/
//}