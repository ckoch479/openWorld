#include "playerRenderer.h"

playerRenderer::playerRenderer(scene* sceneObj, Shader* playerShader, Model* playerModel)
{
	this->sceneObj = sceneObj;
	this->playerShader = playerShader;
	this->currentPlayerModel = playerModel;
}

playerRenderer::playerRenderer(renderContext* context, Model* playerModel)
{
	this->sceneObj = context->sceneObj;
	this->playerShader = context->shader;
	this->currentPlayerModel = playerModel;

}

playerRenderer::~playerRenderer()
{

}

void playerRenderer::setAnimTransforms(std::vector <glm::mat4>* animMats)
{
	this->animMats = animMats;
	this->currentPlayerModel->animationMatrices = *this->animMats;
}

void playerRenderer::setTransform(glm::vec3* pos, glm::quat* Orient, glm::vec3* scale)
{
	this->playerPos = pos;
	this->playerOrient = Orient;
	this->playerScale = scale;
}

void playerRenderer::changePlayerModel(Model* newModel)
{
	this->currentPlayerModel = newModel;
}

void playerRenderer::addPlayerToScene()
{
	transform playerTransfom;
	playerTransfom.position = *this->playerPos;
	playerTransfom.orientation = *this->playerOrient;
	playerTransfom.scale = *this->playerScale;
	this->sceneId = this->sceneObj->addObjectToScene(this->currentPlayerModel, playerTransfom, this->playerShader);
}

void playerRenderer::updatePlayerRender()
{
	transform playerTransfom;
	playerTransfom.position = *this->playerPos;
	playerTransfom.orientation = glm::inverse(*this->playerOrient); //had to do this due to an error somewhere in my math when it comes to the player camera, player front and mesh orientation
	playerTransfom.scale = *this->playerScale;
	this->sceneObj->updateTransform(this->sceneId, playerTransfom);
}

void playerRenderer::updatePlayerModels()
{

}

void playerRenderer::addRightHandItem(renderableModel newItem)
{
	this->rightHandModel = newItem.model;
	this->handShader = newItem.modelShader;

	this->rightHandPos = newItem.pos;
	this->rightHandOrient = newItem.orient;
	this->rightHandScale = newItem.scale;

	transform handTransform;
	handTransform.position = *this->rightHandPos;
	handTransform.orientation = *this->rightHandOrient;
	handTransform.scale = *this->rightHandScale;

	this->rightHandSceneId = this->sceneObj->addStaticSceneObj(this->rightHandModel, handTransform, this->handShader);
}

void playerRenderer::updateRightHandTransform(glm::vec3* pos, glm::quat* orient, glm::vec3* scale)
{
	this->rightHandPos = pos;
	this->rightHandOrient = orient;
	this->rightHandScale = scale;

	transform handTransform;
	handTransform.position = *this->rightHandPos;
	handTransform.orientation = *this->rightHandOrient;
	handTransform.scale = *this->rightHandScale;

	this->sceneObj->updateTransform(this->rightHandSceneId, handTransform);
}