#pragma once

#include <iostream>
#include <unordered_map>

#include "item.h"

#include "renderingInfoDefinitions.h"
#include "animationDataDefinitions.h"

#include "item.h"
#include "handGun.h"
#include "inventorySlot.h"

#ifndef GAMEOBJECTMANAGER_H
#define GAMEOJBECTMANAGER_H


class gameObjectManager
{
public:

	gameObjectManager() {};
	~gameObjectManager() {};

	/*unsigned int createHandGun(std::string filePath, std::string name, float mass, float volume);
	
	std::shared_ptr<item> getItemPTR(unsigned int id) { return worldItems[id]; }*/

private:

	/*unsigned int IDCounter = 0;

	unsigned int getUniqueID();

	std::unordered_map <unsigned int, handGun> handGuns;

	std::unordered_map <unsigned int, std::shared_ptr<item>> worldItems;*/
		 

};

#endif // !GAMEOBJECTMANAGER_H