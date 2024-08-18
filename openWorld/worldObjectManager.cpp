#include "worldObjectManager.h"

worldObjectManager::worldObjectManager()
{

}

void worldObjectManager::addWorldEntity(std::string name, Entity* newEntity)
{
	//if this item does not already exist add it to the world
	if(!this->worldEntities[this->nameToIDmap[name]])
	{
		unsigned int newId = createUniqueID();
		worldEntities[newId] = newEntity;
		this->nameToIDmap[name] = newId;
		this->entityIds.push_back(newId);
	}
	else
	{
		std::cout << "ERROR::ENTITY::ALREADY::EXISTS\n";
	}
	
}

Entity* worldObjectManager::getWorldEntity(std::string name)
{
	unsigned int entityID = this->nameToIDmap[name];
	Entity* currentEnt= this->worldEntities[entityID];

	return currentEnt;
}

void worldObjectManager::update(float dt)
{
	for(unsigned int i = 0; i < this->entityIds.size(); i++)
	{
		this->worldEntities[entityIds[i]]->update(dt);
		//std::cout << "updating entities of: " << i << std::endl;
	}
}

unsigned int worldObjectManager::createUniqueID()
{
	this->worldObjects++;
	return this->worldObjects;
}
