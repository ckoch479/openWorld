#include "gameObjectManager.h"

unsigned int gameObjectManager::createHandGun(std::string filePath, float baseDamage, glm::vec3 handPoint, std::string name, glm::vec3 barrelPos, glm::vec3 front)
{
	unsigned int id = getUniqueID();

	handGun newHandgun(filePath,baseDamage,handPoint,name,barrelPos,front);
	this->handGuns[id] = newHandgun;
	std::shared_ptr<item> gunPtr = std::make_shared<handGun>(newHandgun);

	this->worldItems[id] = gunPtr;
	return id;
}

unsigned int gameObjectManager::getUniqueID()
{
	unsigned int newId = this->IDCounter;
	this->IDCounter++;

	return newId;
}