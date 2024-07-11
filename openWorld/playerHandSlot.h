#pragma once

#include "includes/glm/glm.hpp"
#include "Includes/glm/gtc/type_ptr.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/quaternion.hpp"
#include "includes/glm/gtx/quaternion.hpp"

#include "item.h"
#include "gameObjectManager.h"

#include "handGun.h"

#ifndef PLAYERHANDSLOT_H
#define PLAYERHANDSLOT_H
class playerHandSlot
{
public:

	playerHandSlot(glm::mat4 boneOffsetMatrix);
	~playerHandSlot();

	void addItem(std::shared_ptr<item> newItem, scene* scene, Shader* shader); //same as equiping the item

	void updatePosition(scene* scene, glm::mat4& handTransform, transform& playerTransform);

	void removeItem(); //clear the current item

	void useItem(); //in most cases this should be either shoot or attack with the item

	std::shared_ptr <item> swapItem(std::shared_ptr<item> newItem); //swap current item with a different item

private:

	glm::mat4 getHandTransform(transform& playerTransform, glm::mat4& boneTransform);

	std::shared_ptr<item> currentItem;
	glm::mat4 boneOffsetMat;

};

#endif