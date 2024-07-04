#include "playerHandSlot.h"

void playerHandSlot::addItem(std::shared_ptr<item> newItem, glm::mat4 transf)
{
	this->currentItem = newItem;
	updatePosition(transf);

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

void playerHandSlot::updatePosition(glm::mat4 transf)
{
	this->transf = transf;
	updateTransform();
}

void playerHandSlot::updateTransform()
{
	if (auto weapon = std::dynamic_pointer_cast<handGun> (this->currentItem))
	{

		
		weapon->setTransform(this->transf);
	}


}
