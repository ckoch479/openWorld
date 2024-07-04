#pragma once

#include "includes/glm/glm.hpp"
#include "Includes/glm/gtc/type_ptr.hpp"

#include "item.h"
#include "handGun.h"
#include "gameObjectManager.h"


#ifndef PLAYERHANDSLOT_H
#define PLAYERHANDSLOT_H
class playerHandSlot
{
public:

	void addItem(std::shared_ptr<item> newItem, glm::mat4 transf); //same as equiping the item

	void removeItem(); //clear the current item

	void useItem(); //in most cases this should be either shoot or attack with the item

	std::shared_ptr <item> swapItem(std::shared_ptr<item> newItem); //swap current item with a different item

	void updatePosition(glm::mat4 transf);

private:

	void updateTransform();

	std::shared_ptr<item> currentItem;
	glm::mat4 transf;

};

#endif