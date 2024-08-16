#include "rangedItem.h"

rangedItem::rangedItem(std::string uniqueId)
{
	this->uniqueID = uniqueId;
}

rangedItem::~rangedItem()
{

}

void rangedItem::setPosDirection(glm::vec3 position, glm::vec3 direction)
{
	this->position = position;
	this->direction = direction;
}

void rangedItem::setDamageAmount(float amount)
{
	this->damageAmount = amount;
}

void rangedItem::setTotalCapacity(int newCap)
{
	this->maxCapacity = newCap;
}

void rangedItem::useItem(PhysicsWorld* world)
{
	//add functionality to game world for a damage ray
}

void rangedItem::reloadItem(int amount)
{
	this->currentCapacity = amount; //reload the weapon
}