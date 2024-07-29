#include "playerManager.h"

playerManager::playerManager(scene* newScene, PhysicsWorld* newWorld, windowManager* newManager, Shader* playerShader,Shader* itemShader, std::string modelFilePath, Camera* newCamera)
{
	this->player = new playerEntity(modelFilePath);
	this->currentScene = newScene;
	this->currentWorld = newWorld;
	this->currentManager = newManager;
	this->playerShader = playerShader;
	this->itemShader = itemShader;
	this->playerCamera = newCamera;
	this->controller = new characterController(this->player, this->currentWorld, this->playerCamera);
	this->inventoryManager = new PlayerInventoryManager(this->player,this->currentScene,this->itemShader);

	player->addPlayerToScene(this->currentScene, this->playerShader);

}

playerManager::~playerManager()
{

}

void playerManager::updateManager(float dt, Level* currentLevel)
{
	this->player->updatePlayerScene(this->currentScene); //had to be ordered this way because hand items would lag behind if didnt and would not be placed correctly
	this->inventoryManager->updateInventoryStatus();

	this->controller->updateInputs(this->currentManager);
	this->controller->updateController(dt,*currentLevel);
	this->player->getPlayerAnimator()->update(dt);
}

void playerManager::testItemSlots(std::shared_ptr<item> newItem)
{
	this->inventoryManager->equipSlot(RIGHTHAND, newItem);
	//this->inventoryManager->equipSlot(LEFTHAND, newItem);
}