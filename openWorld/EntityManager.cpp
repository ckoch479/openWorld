#include "EntityManager.h"

EntityManager::EntityManager()
{

}

EntityManager::~EntityManager()
{

}

unsigned int EntityManager::creatNewId()
{
	this->idCounter++;
	unsigned int newID = this->idCounter;
	return newID;
}