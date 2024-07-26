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
}

int skeleton::addBone(Bone newBone)
{
	
	std::string boneName = newBone.getName();
	int boneId = newBone.getId();

	this->bones.push_back(newBone);
	this->boneNameIDMap[boneName] = boneId;
	this->boneMap[boneId] = &bones[numBones];

	this->numBones++;
}

Bone* skeleton::getBone(int& id)
{
	if(this->boneMap[id])
	{
		return this->boneMap[id];
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
	if (this->boneMap[id])
	{
		return this->boneMap[id];
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