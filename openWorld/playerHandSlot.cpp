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

void playerHandSlot::updatePosition(scene* scene, glm::mat4& handTransform, transform& playerTransform, glm::vec3 boneDirection)
{
	if(this->currentItem) //if there is a current item update its position
	{
		if (auto weapon = std::dynamic_pointer_cast<handGun>(this->currentItem)) //if this item is a handgun
		{
			transform newTransform;
			transform objectTransform = weapon->getTransform();

			glm::mat4 bonePos = getHandTransform(playerTransform, handTransform, boneDirection);

			glm::vec4 objectBonePosition = glm::inverse(bonePos) * glm::vec4(playerTransform.position, 1.0);

			newTransform.position = objectBonePosition + glm::vec4(playerTransform.position, 1.0f);

			glm::vec3 front = glm::normalize(boneDirection);
			glm::vec3 up = glm::normalize(glm::cross(front, glm::vec3(0,1,0)));
			glm::vec3 right = glm::normalize(glm::cross(front,up));

			glm::mat4 localRot(1.0f);
			localRot[0][0] = front.x; localRot[0][1] = front.y; localRot[0][2] = front.z;
			localRot[1][0] = up.x;    localRot[1][1] = up.y;    localRot[1][2] = up.z;
			localRot[2][0] = right.x; localRot[2][1] = right.y; localRot[2][2] = right.z;

			glm::quat correctionQuat(1.0f, 0.0, 0.0, 0.0 );

			glm::mat4 rotateMat(1.0f);
			rotateMat = glm::rotate(rotateMat, 2.0f, glm::vec3(1, 0, 0));//x
			rotateMat = glm::rotate(rotateMat, 2.0f, glm::vec3(0, 1, 0)); //y
			rotateMat = glm::rotate(rotateMat, 0.0f, glm::vec3(0, 0, 1));//z 
			correctionQuat = glm::toQuat(rotateMat);

			newTransform.orientation = glm::toMat4(correctionQuat) * glm::inverse(localRot) * glm::toMat4(playerTransform.orientation);
			newTransform.scale = glm::vec3(1.0f);

			weapon->updateTransform(scene, newTransform);
		}
	}
}

//this returns the position of the hand bones in world space of the hand bone, not a rotation or scaling
glm::mat4 playerHandSlot::getHandTransform(transform& playerTransform, glm::mat4& boneTransform, glm::vec3 boneDirection)
{
	glm::mat4 handMat(1.0f);

	glm::mat4 playerMat(1.0f);
	playerMat = glm::translate(playerMat, playerTransform.position);
	playerMat = playerMat * glm::toMat4(playerTransform.orientation);
	playerMat = glm::scale(playerMat, playerTransform.scale);

	handMat = playerMat * this->boneOffsetMat * glm::inverse(boneTransform); // from origin to model space, to bone space, then apply anim transform


	handMat = handMat * glm::inverse(glm::toMat4(playerTransform.orientation)); //this makes the object rotate in relation to the body in world space


	return handMat; //multiply the object by this matrix to move it to the players hand bone space
}

void playerHandSlot::removeItem()
{
	this->currentItem.reset();
}

void playerHandSlot::useItem()
{
	if(auto weapon = std::dynamic_pointer_cast<handGun>(this->currentItem))
	{
		//shoot pew pew pew pew
		
	}
}

std::shared_ptr <item> playerHandSlot::swapItem(std::shared_ptr<item> newItem)
{
	std::shared_ptr <item> oldItem = this->currentItem;
	this->currentItem = newItem;
	return oldItem;
}




