#pragma once

#include <iostream>

#include "item.h"

#ifndef INVENTORYSLOT_H
#define INVENTORYSLOT_H

//single inventory slot, an array of these can be used for a large inventory but doing one slot at a time allows it to be used in a large range
class inventorySlot
{
public:
	
	void addItem(const std::shared_ptr<item> newItem);

	void removeItem();

	void useItem();

	std::shared_ptr <item> swapItem(std::shared_ptr<item> newItem); 
	//return the current item in this slot and takes the method argument and places it in the currentItem slot

private:
	std::shared_ptr<item> currentItem; //item, if one that currently occupies this slot

};

#endif // !INVENTORYSLOT_H