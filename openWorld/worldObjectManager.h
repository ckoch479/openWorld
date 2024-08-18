#pragma once

#include <iostream>
#include <vector>
#include <unordered_map>

#include "Entity.h"

#ifndef WORLDOBJECTMANAGER_H
#define WORLDOBJECTMANAGER_H

class worldObjectManager
{
public:

	worldObjectManager();

	void addWorldEntity(std::string name, Entity* newEntity);

	Entity* getWorldEntity(std::string name);

	void update(float dt);

private:

	unsigned int createUniqueID();

	unsigned int worldObjects = 0;

	std::unordered_map <unsigned int,Entity*> worldEntities; //unorderedMap of all world entities
	std::unordered_map<std::string, unsigned int> nameToIDmap;

	std::vector <unsigned int> entityIds;
};

#endif