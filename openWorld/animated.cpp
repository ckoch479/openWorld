#include "animated.h"

animated::animated(std::string uniqueID, Model* animatedModel)
{
	this->uniqueID = uniqueID;
	this->animatedModel = animatedModel;
	this->objSkeleton = animatedModel->skeleton;

	this->componentAnimator = new objAnimator(this->animatedModel);
}

animated::~animated()
{

}

void animated::addAnimation(std::string filePath, std::string name, bool loopingAnimation)
{
	this->componentAnimator->loadAnimation(name,filePath, loopingAnimation);
}

void animated::playAnimation(std::string name)
{
	this->componentAnimator->playAnimation(name);
}
