#pragma once

#include <iostream>
#include <unordered_map>

//#include "renderingInfoDefinitions.h" //may change this later and create a bone class instead as well
#include "Bone.h"

#include "includes/glm/glm.hpp"
#include "Includes/glm/gtc/type_ptr.hpp"

#ifndef SKELETON_H
#define SKELETON_H

class skeleton
{
public:

	skeleton();

	skeleton(std::vector <Bone> bones);

	int addBone(Bone newBone); //returns id

	Bone* getBone(int& id); //get a bone if you know it's id

	Bone* getBone(std::string& name); //get a bone if you only know it's name and not id

	int getBoneCount();

	Bone* getRootBone();

	void setChildren();

private:

	void insertBone();

	int getNewId();

	

	Bone* rootBone;
	std::vector <Bone> bones;
	std::unordered_map<int, Bone> boneMap; //bone map for easier look up uses ids for hopefully better preformance
	std::unordered_map<std::string, int> boneNameIDMap; //should really only be used if you cannot find or do not know the id of the bone

	//i think as of right now i have incorrectly gotten the skeleton's heirarchy from the animation and not from the bones themselves using assimp and intend to correct that here

	int numBones = 0;
};

#endif