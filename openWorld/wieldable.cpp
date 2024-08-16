#include "wieldable.h"

wieldable::wieldable(std::string uniqueId)
{

}

wieldable::~wieldable()
{

}

void wieldable::attachToModel(Model* entityModel, objAnimator* entityAnimator, std::string boneName, bool isTwoHanded, std::string secondaryBoneName)
{
	this->entityModel = entityModel;
	this->entityAnimator = entityAnimator;
	this->boneName = boneName;
	this->twoHanded = isTwoHanded;
	this->secondaryBoneName = secondaryBoneName;
}

void wieldable::setLocalTransform(glm::vec3 pos, glm::quat orient, glm::vec3 scale)
{
	this->localPos = pos;
	this->localOrient = orient;
	this->scale = scale;
}

void wieldable::calculateHandPosition(glm::vec3 entityPos, glm::quat entityOrient, glm::vec3 entityScale)
{
	//do alot of math here, pull from hand socket class
}

glm::vec3 wieldable::getWorldPos()
{
	return this->position;
}

glm::quat wieldable::getWorldOrient()
{
	return this->orientation;
}

glm::vec3 wieldable::getWorldScale()
{
	return this->scale;
}