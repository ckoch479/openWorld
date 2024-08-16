#include "lightEmitter.h"

lightEmitter::lightEmitter(std::string uniqueId, lightType type)
{
	this->uniqueId = uniqueId;
	this->type = type;


}

lightEmitter::~lightEmitter()
{

}

void lightEmitter::setLighting(glm::vec3 position, glm::vec3 direction, glm::vec3 ambientColor, glm::vec3 specularColor, glm::vec3 diffuseColor)
{
	this->position = position;
	this->direction = direction;
	this->ambientColor = ambientColor;
	this->specularColor = specularColor;
	this->diffuseColor = diffuseColor;

}

void lightEmitter::addLightingToScene(scene* sceneObj)
{
	this->sceneObj = sceneObj;

	//add functionality to add light types to the scene
}

void lightEmitter::removeLightingFromScene(scene* scenObj)
{
	//add functionality to remove lights from the scene
}

void lightEmitter::updateSceneLighting()
{
	//add functionality to change scene lighting that has been passed through already
}