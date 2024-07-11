#include "playerHandSlot.h"

playerHandSlot::playerHandSlot(glm::mat4 boneOffsetMatrix)
{
	this->boneOffsetMat = boneOffsetMatrix;
}

playerHandSlot::~playerHandSlot()
{

}

void playerHandSlot::addItem(std::shared_ptr<item> newItem, scene* scene, Shader* shader)
{
	if(newItem->isEquipable()) //if this item can be used in the players hands then add it if not dont do that
	{
		this->currentItem = newItem;

		if (auto weapon = std::dynamic_pointer_cast<handGun>(this->currentItem)) //if this item is a handgun
		{
			weapon->addToScene(scene, shader);
			std::cout << "adding handgun to scene\n";
		}
	}

	if (!newItem->isEquipable())
	{
		std::cout << "ERROR::NON::EQUIPABLE::ITEM::CAN::NOT::BE::EQUIPED!\n";
	}
}

void playerHandSlot::updatePosition(scene* scene, glm::mat4& handTransform, transform& playerTransform)
{
	if(this->currentItem) //if there is a current item update its position
	{
		if (auto weapon = std::dynamic_pointer_cast<handGun>(this->currentItem)) //if this item is a handgun
		{
			transform newTransform;

			glm::mat4 bonePos = getHandTransform(playerTransform, handTransform);

			glm::vec4 objectBonePosition = glm::inverse(bonePos) * glm::vec4(playerTransform.position, 1.0);

			newTransform.position = objectBonePosition + glm::vec4(playerTransform.position, 1.0f);

			/*glm::vec3 scale;
			scale.x = sqrt((bonePos[0][0] * bonePos[0][0]) + (bonePos[0][1] * bonePos[0][1]) + (bonePos[0][2] * bonePos[0][2]));
			scale.y = sqrt((bonePos[1][0] * bonePos[1][0]) + (bonePos[1][1] * bonePos[1][1]) + (bonePos[1][2] * bonePos[1][2]));
			scale.z = sqrt((bonePos[2][0] * bonePos[2][0]) + (bonePos[2][1] * bonePos[2][1]) + (bonePos[2][2] * bonePos[2][2]));

			glm::quat baseQuat(1.0, 0.0, 0.0, 0.0);
			baseQuat.w = sqrt(1 + (bonePos[0][0] / scale.x) + (bonePos[1][1] / scale.y) + (bonePos[2][2] / scale.z)) / 2;
			baseQuat.x = (bonePos[2][1] / scale.y) - (bonePos[1][2] /scale.z) / (4 * baseQuat.w);
			baseQuat.y = (bonePos[0][2] / scale.z) - (bonePos[2][0] / scale.x) / (4 * baseQuat.w);
			baseQuat.z = (bonePos[1][0] / scale.x) - (bonePos[0][1] / scale.y) / (4 * baseQuat.w);

			baseQuat = glm::normalize(baseQuat);
			
			glm::quat objectBoneRotation = glm::toQuat(glm::inverse(bonePos)) * playerTransform.orientation;
			objectBoneRotation = glm::normalize(objectBoneRotation);*/

			newTransform.orientation = glm::quat(1.0, 0.0, 0.0, 0.0) * playerTransform.orientation;
			newTransform.scale = glm::vec3(1.0f);

			weapon->updateTransform(scene, newTransform);
		}
	}
}

//this returns the position of the hand bones in world space of the hand bone, not a rotation or scaling
glm::mat4 playerHandSlot::getHandTransform(transform& playerTransform, glm::mat4& boneTransform)
{
	glm::mat4 handMat(1.0f);

	glm::mat4 playerMat(1.0f);
	playerMat = glm::translate(playerMat, playerTransform.position);
	playerMat = playerMat * glm::toMat4(playerTransform.orientation);
	playerMat = glm::scale(playerMat, playerTransform.scale);

	handMat = playerMat * this->boneOffsetMat * glm::inverse(boneTransform);
	handMat = handMat * glm::inverse(glm::toMat4(playerTransform.orientation));

	return handMat; //multiply the object by this matrix to move it to the players hand bone space
}

void playerHandSlot::removeItem()
{
	this->currentItem.reset();
}

void playerHandSlot::useItem()
{
	//if(auto weapon = std::dynamic_pointer_cast<handGun>(this->currentItem))
	//{
	//	//shoot pew pew pew pew
	//}
}

std::shared_ptr <item> playerHandSlot::swapItem(std::shared_ptr<item> newItem)
{
	std::shared_ptr <item> oldItem = this->currentItem;
	this->currentItem = newItem;
	return oldItem;
}




