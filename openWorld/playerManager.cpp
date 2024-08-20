#include "playerManager.h"

playerManager::playerManager(scene* newScene, PhysicsWorld* newWorld, windowManager* newManager, Shader* playerShader,Shader* itemShader, std::string modelFilePath, Camera* newCamera, Level* currentLevel)
{
	this->player = new playerEntity(modelFilePath);
	//this->currentScene = newScene;
	//this->currentWorld = newWorld;
	//this->currentManager = newManager;
	//this->playerShader = playerShader;
	//this->itemShader = itemShader;
	//this->playerCamera = newCamera;
	//this->controller = new characterController(this->player, this->currentWorld, this->playerCamera);
	//this->inventoryManager = new PlayerInventoryManager(this->player,this->currentScene,this->itemShader);

	//player->addPlayerToScene(this->currentScene, this->playerShader);
	//this->currentLevel = currentLevel;

}

playerManager::~playerManager()
{

}

void playerManager::update(float dt)
{
	//this->player->updateEntity();
	
	

	//this->player->getPlayerAnimator()->update(dt);

	if (this->testSignal == true)
	{
		transform playerTransform = *this->player->getPlayersTransform();
		glm::vec3 targetPosition = player->getPlayerRelativeTransform()->front;

		std::string endEffectorName = "mixamorig:RightHand";
		glm::vec3 target = targetPosition;
		this->player->getPlayerAnimator()->applyInverseKinematics(endEffectorName, target);
	}

//	this->player->updatePlayerScene(this->currentScene); //had to be ordered this way because hand items would lag behind if didnt and would not be placed correctly
	//this->inventoryManager->updateInventoryStatus();

	//this->controller->updateInputs(this->currentManager);
	//this->controller->updateController(dt,*currentLevel);
	//this->testSignal = this->controller->ikTest;
}

void playerManager::testItemSlots(std::shared_ptr<item> newItem)
{
	//this->inventoryManager->equipSlot(RIGHTHAND, newItem);
	//this->inventoryManager->equipSlot(LEFTHAND, newItem);
}