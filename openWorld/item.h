#pragma once

#include <iostream>


#ifndef ITEM_H
#define ITEM_H


class item
{

public:

	virtual ~item() {}

	virtual std::string getName() const = 0;

	virtual bool isEquipable() const = 0;
	virtual bool isStackable() const = 0;
	virtual bool isConsumable() const = 0;

	virtual float getMass() const = 0;
	virtual float getVolume() const = 0;


private:

	
};

#endif // !ITEM_H