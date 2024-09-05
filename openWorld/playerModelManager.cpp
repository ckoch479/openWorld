#include "playerModelManager.h"


playerModelManager::playerModelManager(Model* defaultModel, objAnimator* playerAnimator, playerRenderer* renderer)
{
	this->playerModel = defaultModel;
	this->playerAnimator = playerAnimator;
	this->renderer = renderer;
	//add default model to renderer
}

playerModelManager::~playerModelManager()
{

}

void playerModelManager::changePlayerModel(Model* model)
{

}

void playerModelManager::setPlayerTransform(glm::vec3* newPos, glm::quat* newOrient, glm::vec3* newScale)
{
	this->playerTransform = newPos;
	this->playerOrient = newOrient;
	this->playerScale = newScale;
}

void playerModelManager::setEquipedItem(item* newItem)
{
	this->playerHandModel = newItem->getModel();
	this->equipedPos = newItem->getPos();
	this->equipedOrient = newItem->getOrient();
	this->equipedScale = newItem->getScale();
	this->handShader = newItem->getShader();
	renderableModel itemModel(playerHandModel, this->equipedPos, this->equipedOrient, this->equipedScale, this->handShader);
	this->renderer->addRightHandItem(itemModel);
}

void playerModelManager::removeEquipedItem()
{
	this->playerHandModel = nullptr;
	this->equipedPos = nullptr;
	this->equipedOrient = nullptr;
	this->equipedScale = nullptr;
	this->handShader = nullptr;
	//remove from playerRenderer as well
}

void playerModelManager::updateManager()
{

	//update player equipment if it exists //used handModel and shader because these two are absolutely needed
	if (this->playerHandModel && handShader)
	{
		updateEquipedItemTransform();
		this->renderer->updateRightHandTransform(this->equipedPos, this->equipedOrient, this->equipedScale);
	}

	//update player model
	this->renderer->setTransform(this->playerTransform, this->playerOrient, this->playerScale);
	this->renderer->updatePlayerRender();
	

}

//this method is used to update the transform of the item in the players hand
void playerModelManager::updateEquipedItemTransform()
{
	std::string boneName = "rightSocket";
	glm::mat4 rightHandMatrix = this->playerAnimator->getFinalBoneTransform(boneName);
	glm::mat4 rightHandOffset = this->playerModel->skeleton->getBone(boneName)->getOffsetMat();
	
	glm::mat4 localTransform(1.0f); // this is for a local correction transform will be added instead to the item itself and so it can be fixed using a level editor
	localTransform = glm::translate(localTransform, glm::vec3(0, 0, 0));
	localTransform = glm::rotate(localTransform, glm::radians(90.0f), glm::vec3(1, 0, 0)); //95
	localTransform = glm::rotate(localTransform, glm::radians(180.0f), glm::vec3(0, 1, 0)); //185 
	localTransform = glm::rotate(localTransform, glm::radians(90.0f), glm::vec3(0, 0, 1));

	rightHandMatrix = rightHandMatrix * glm::inverse(rightHandOffset);

	glm::mat4 bonePos(1.0f);
	
	glm::mat4 playerMat(1.0f); //create player model matrix (model space to world space)
	playerMat = glm::translate(playerMat, *this->playerTransform);
	playerMat = playerMat * glm::inverse(glm::toMat4(*this->playerOrient));
	playerMat = glm::scale(playerMat, *this->playerScale);
	
	bonePos = playerMat * rightHandMatrix; //mutliply the bone transform (in model local space) with the world space matrix; this is correct
	
	glm::mat4 Transform(1.0f);
	Transform = bonePos * localTransform;
			
	glm::vec3 skew;
	glm::vec4 perspective;
	glm::vec3 scale;
	glm::decompose(Transform, scale, *this->equipedOrient, *this->equipedPos, skew, perspective); //decompose mat4			
		
}