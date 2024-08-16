#pragma once

#include <iostream>
#include <unordered_map>

#include "renderable.h"
#include "animated.h"

#include "wieldable.h"
#include "melee.h"
#include "rangedItem.h"

#include "lightEmitter.h"

#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

//entity manager class, implimented as a singleton, singleton was use so all components were located in one central location
class EntityManager
{
public: 

	static EntityManager* instance;

	static EntityManager* getInstance() 
	{
		if(!instance)
		{
			instance = new EntityManager();
		}
		return instance;
	};

private:
	//private constructor/destructor
	EntityManager();
	~EntityManager();

	EntityManager(EntityManager& other) = delete; // Copy Constructor
	void operator = (const EntityManager&) = delete; //Assignement operator

	//useable methods:

	unsigned int creatNewId();
	

	//data here
	std::unordered_map<std::string, unsigned int> idStringMap; //map that allows unique ids to be assigned to a string provide by the user
	
	unsigned int idCounter = 0;

	//components:

	//animated
	std::unordered_map<unsigned int, animated> animatedModels;
	//renderable
	std::unordered_map<unsigned int, renderable> renderables;

	//simulated
	
	//collidable
	
	//positionable?
	
	//Heath
	
	//wearable
	
	//wieldable
	std::unordered_map<unsigned int, wieldable> wieldables;
	//Melee
	std::unordered_map<unsigned int, melee> meleeItems;
	//ranged
	std::unordered_map<unsigned int, rangedItem> rangedItems;

	//PlayerControllable
	
	//AI controlable
	
	//Storable
	
	//inventory

	//lightEmitter
	std::unordered_map <unsigned int, lightEmitter> lightEmitters;

};

#endif

//simulated/physics world needs:
//
// oriented Bounding Box collider representations
// collision algorythm for OBB vs OBB and OBB vs rayCast
// rayCast representations
// basic collision response (not looking for actual kinematic simulation yet just a response that means the player wont fall through the floor and cant walk through walls)
// damageRaycast representation
// damageOBB representation
// entity messaging system for damage response
// 
//