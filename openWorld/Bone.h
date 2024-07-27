#pragma once

#include <iostream>
#include <vector>

#include "includes/glm/glm.hpp"
#include "Includes/glm/gtc/type_ptr.hpp"

#ifndef BONE_H
#define BONE_H

class Bone
{
public:
	
	Bone();

	Bone(int id, std::string name, glm::mat4 offset);

	Bone(int id, std::string name, glm::mat4 offset, int parent, std::vector <int> children);

	int getId();

	int getParent();

	std::vector <int> getChildren();

	glm::mat4 getOffsetMat();

	int getNumChildren();

	std::string getName();

	void addChild(int bone);

	void setParent(int bone);

private:

	int id = -1;
	glm::mat4 offsetMatrix = glm::mat4(1.0f);
	std::string name = "NO::BONE";

	int numChildren = 0;
	std::vector <int> childrenIds; //children Ids

	int parentBoneId = NULL; //parent id

};

#endif