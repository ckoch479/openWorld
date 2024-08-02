#include "skeleton.h"

skeleton::skeleton()
{

}

skeleton::skeleton(std::vector <Bone> bones)
{
	for(unsigned int i = 0; i < bones.size(); i++)
	{
		addBone(bones[i]);
	}
	//std::cout << "setting children:" << std::endl;
	setChildren();

}

int skeleton::addBone(Bone newBone)
{
	
	std::string boneName = newBone.getName();
	int boneId = newBone.getId();

	this->bones.push_back(newBone);
	this->boneNameIDMap[boneName] = boneId;
	this->boneMap[boneId] = newBone;

	this->numBones++;
	return boneId;
}

Bone* skeleton::getBone(int& id)
{
	if(&this->boneMap[id])
	{
		return &this->boneMap[id];
	}
	else
	{
		return NULL;
		std::cout << "ERROR::INVALID::BONE::ID::REFERENCED::IN::SKELETON " << std::endl;
	}
}

Bone* skeleton::getBone(std::string& name)
{
	int id = this->boneNameIDMap[name];
	if (&this->boneMap[id])
	{
		return &this->boneMap[id];
	}
	else
	{
		return NULL;
		std::cout << "ERROR::INVALID::BONE::NAME::REFERENCED::IN::SKELETON " << std::endl;
	}
}

void skeleton::insertBone()
{

}

int skeleton::getNewId()
{
	this->numBones++;
	return this->numBones;
}

void skeleton::setChildren()
{
	for(unsigned int i = 0; i < this->bones.size(); i++)
	{
		Bone* currentBone = &this->bones[i];
		int currentBoneId = currentBone->getId();
		std::vector <int> childrenIds;

		std::cout << "current bone: " << currentBone->getName() << " current bone parent: " << currentBone->getParent() << std::endl;

		for(unsigned int j = 0; j < this->bones.size(); j++)
		{
			Bone* iteratorBone = &this->bones[j];
			if(iteratorBone->getParent() == currentBoneId)
			{
				std::cout << "child bone ID: " << iteratorBone->getId() << std::endl;
				//currentBone->addChild(iteratorBone->getId());
				childrenIds.push_back(iteratorBone->getId());
			}
		}
		currentBone->setChildren(childrenIds);

	}

}

int skeleton::getBoneCount()
{
	return this->numBones;
}

Bone* skeleton::getRootBone()
{
	int id = 0;
	return this->getBone(id);
}