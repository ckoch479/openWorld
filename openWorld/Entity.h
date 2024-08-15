#pragma once

#include <iostream>

#ifndef ENTITY_H
#define ENTITY_H

class Entity
{
public:
	
	//a name will need to be assigned to all entities however does not need to be assigned upon creation can be added later
	Entity(std::string name);
	Entity();

	~Entity();

	//update will update the entity state (could be rendering, animation, simulation, health, ect)
	void update();

private:

	//posible components:
	
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