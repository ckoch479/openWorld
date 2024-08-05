#include "npcManager.h"

npcManager::npcManager(scene* newScene, PhysicsWorld* newWorld, Shader* npcShader, std::string modelFilePath, std::string npcName)
{
	this->NPC = new npcEntity(modelFilePath,npcName);
	this->currentScene = newScene;
	this->currentWorld = newWorld;
	this->npcShader = npcShader;
	this->controller = new npcController(this->NPC,this->currentWorld);

	this->NPC->addToScene(this->currentScene, npcShader);
}

npcManager::~npcManager()
{

}

void npcManager::updateManager(float dt, Level* currentLevel)
{
	this->NPC->updateEntity();
	this->NPC->getAnimator()->update(dt);

	this->NPC->updateScene(this->currentScene);

	//update npc controller
	this->controller->updateController(dt, *currentLevel);
}