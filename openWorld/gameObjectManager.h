#pragma once

#include <iostream>
#include <unordered_map>

#include "GameObject.h"

#include "renderingInfoDefinitions.h"
#include "animationDataDefinitions.h"
#include "objTypeDefinitions.h"

#ifndef GAMEOBJECTMANAGER_H
#define GAMEOJBECTMANAGER_H

enum catagories
{
	mags,
	melWep,
	rangeWep,
	health,
	junk,
	phys,
	rendered,
	wearables,
	resources,
	storage,
	animated,
};

class gameObjectManager
{
public:


private:

	unsigned int generateNewID();//generates a new id upon creation, this id is the same no matter which unordered_map it is in so there will never be a repeated id between any of the maps

	std::unordered_map <unsigned int, GameObject> gameObjects; //for the base object itself
	std::unordered_map <GameObject*, std::vector <catagories>> objectCatagories; //what catagories this object is in makes it a little easier on myself to manage where data comes from

	//these below are for subcatagories
	std::unordered_map <unsigned int, magazine> magazines; //dont know if i should keep this or remove it for being a storageItem
	std::unordered_map <unsigned int, meleeWeapon> meleeWeapons;
	std::unordered_map <unsigned int, rangedWeapon> rangedWeapons;
	std::unordered_map <unsigned int, healthItems> healingItems;
	std::unordered_map <unsigned int, renderable> renderableObjects;
	std::unordered_map <unsigned int, renderable2D> sprites;
	std::unordered_map <unsigned int, wearable> clothing;
	std::unordered_map <unsigned int, isAnimated> animatedObjs;
	std::unordered_map <unsigned int, isStorage> storageItems;

		 

};

#endif // !GAMEOBJECTMANAGER_H