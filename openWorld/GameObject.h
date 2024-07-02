#pragma once

#include <iostream>
#include <vector>
#include <map>

#include "includes/glm/glm.hpp"
#include "Includes/glm/gtc/type_ptr.hpp"
#include "Includes/glm/gtc/quaternion.hpp"

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

//game objects are any equipable/usable object in game such as healthPacks, weapons, clothing, building resources, ect
//

class GameObject
{
public:

	GameObject(std::string newName, unsigned int newID, bool isEquipable, bool stackable,float mass, float volume, bool isConsumable)
	{
		this->ID = newID;
		this->name = newName;
		this->equipable = isEquipable;
		this->stackable = stackable;
		this->mass = mass;
		this->volume = volume;
		this->consumable = isConsumable;
	}

	GameObject();

	~GameObject();

private:

	std::string name;
	unsigned int ID; //this ID is used in the game object manager for storing itself as well as storing what type of item it is
	bool equipable;
	bool stackable;
	bool consumable;
	float mass; //mass/volume used for inventory management 
	float volume;
};
#endif

