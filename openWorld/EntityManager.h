#pragma once

#include <iostream>
#include <unordered_map>

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
	//renderable
	//simulated
	//positionable?
	//Heath
	//wearable
	//wieldable
	//Melee
	//ranged
	//PlayerControllable
	//AI controlable
	//Storable
	//inventory


};

#endif