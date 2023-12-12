#pragma once

#include "glad/glad.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

#include "includes/glm/glm.hpp"
#include "Includes/glm/gtc/type_ptr.hpp"

#include "AssimpModel.h"
#include "Bone.h"

#ifndef ASSIMPSKELETALANIMATION_H
#define ASSIMPSKELETALANIMATION_H

struct AssimpNodeData
{
	glm::mat4 transformation;
	std::string name;
	int childrenCount;
	std::vector<AssimpNodeData> children;
};


//this class is for loading animation data from assimp
class AssimpSkeletalAnimation
{
public:
	AssimpSkeletalAnimation(const std::string animationPath);
	~AssimpSkeletalAnimation();

	Bone* FindBone(const std::string& name);

	float GetTicksPerSecond();

	float GetDuration();

	AssimpNodeData& GetRootNode();

	


private:
	float Duration;
	int ticksPerSecond;
	AssimpNodeData rootNode;

	std::vector <Bone> Bones;
	std::map<std::string, BoneInfo> BoneInfoMap;

	void ReadHierarchyData(AssimpNodeData& dest, const aiNode* src);

	void populateBoneData(const aiAnimation* animation);


};

#endif