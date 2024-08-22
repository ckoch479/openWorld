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
	playerTransfom.orientation = glm::inverse(*this->playerOrient); //inversing this does work for the mesh but still not the colliders
	playerTransfom.scale = *this->playerScale;
	this->sceneObj->updateTransform(this->sceneId, playerTransfom);
}