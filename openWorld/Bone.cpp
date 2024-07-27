#include "Bone.h"

Bone::Bone()
{
	this->id = -1;
	this->name = "NO::BONE";
	this->offsetMatrix = glm::mat4(1.0f);
	this->childrenIds.push_back(0);
}

Bone::Bone(int id, std::string name, glm::mat4 offset)
{
	this->id = id;
	this->name = name;
	this->offsetMatrix = offset;
	this->childrenIds.push_back(0);
}

Bone::Bone(int id, std::string name, glm::mat4 offset, int parent, std::vector <int> children)
{
	this->id = id;
	this->name = name;
	this->offsetMatrix = offset;
	this->parentBoneId = parent;
	this->childrenIds = children;
}

int Bone::getId()
{
	return this->id;
}

int Bone::getParent()
{
	return this->parentBoneId;
}

std::vector <int> Bone::getChildren()
{
	return this->childrenIds;
}

glm::mat4 Bone::getOffsetMat()
{
	return this->offsetMatrix;
}

int Bone::getNumChildren()
{
	return this->numChildren;
}

std::string Bone::getName()
{
	return this->name;
}

void Bone::addChild(int bone)
{
	this->childrenIds.push_back(bone);
	this->numChildren++;
}

void Bone::setParent(int bone)
{

}