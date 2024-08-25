#include "playerModelManager.h"


playerModelManager::playerModelManager(Model* defaultModel, objAnimator* playerAnimator, playerRenderer* renderer)
{
	this->playerModel = defaultModel;
	this->playerAnimator = playerAnimator;
	this->renderer = renderer;

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
	//this->renderer->addRightHandItem();
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
	//update player model first

	this->renderer->setTransform(this->playerTransform, this->playerOrient, this->playerScale);

	//update player equipment if it exists //used handModel and shader because these two are absolutely needed
	if(this->playerHandModel && handShader)
	{
		updateEquipedItemTransform();
		this->renderer->updateRightHandTransform(this->equipedPos, this->equipedOrient, this->equipedScale);
	}

}

//this method is used to update the transform of the item in the players hand
void playerModelManager::updateEquipedItemTransform()
{
	std::string boneName = "rightSocket";
	glm::mat4 rightHandMatrix = this->playerAnimator->getFinalBoneTransform(boneName);
	glm::mat4 rightHandOffset = this->playerModel->skeleton->getBone(boneName)->getOffsetMat();
	
    //		glm::mat4 localTransform = weapon->getTransform(); // this was for a local correction transform

	glm::mat4 bonePos(1.0f);
	
		glm::mat4 playerMat(1.0f); //create player model matrix (model space to world space)
		playerMat = glm::translate(playerMat, *this->playerTransform);
		playerMat = playerMat * glm::toMat4(*this->playerOrient);
		playerMat = glm::scale(playerMat, *this->playerScale);
	
		bonePos = playerMat * rightHandOffset * glm::inverse(rightHandMatrix); // from origin to model space, to bone space, then apply anim transform
	
		bonePos = playerMat * rightHandMatrix; //mutliply the bone transform (in model local space) with the world space matrix; this is correct
	
		glm::mat4 Transform(1.0f);
		Transform = bonePos;// *localTransform;
			
		glm::vec3 skew;
		glm::vec4 perspective;
		glm::decompose(Transform, *this->playerScale, *this->playerOrient, *this->playerTransform, skew, perspective); //decompose mat4			
}