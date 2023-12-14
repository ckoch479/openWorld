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
#include "lookup_table.h"

#include "AssimpModel.h"
#include "AssimpMesh.h"
#include "Bone.h"
#include "AssimpSkeletalAnimation.h"
#include "ResourceManager.h"

void DebugBoneTrees(AnimationBoneData& bone,std::string& boneAndNodeData)
{
	glm::mat4 boneTransform;
	std::string name = bone.name;

	boneAndNodeData += name + "\n";
	int childrencount;

	std::vector <AnimationBoneData> children;

	std::vector <KeyPosition> Positions;
	std::vector <KeyRotation> Rotations;
	std::vector <KeyScale> Scalings;

	int numPositions;
	int numRotations;
	int numScalings;

	for (int i = 0; i < bone.childrenCount; i++) 
	{
		AnimationBoneData childBone = bone.children[i];
		DebugBoneTrees(childBone, boneAndNodeData);
	}
}

void debugAnimationData(AnimationData& animation)
{
	float animationDuration = animation.duration;
	int TPS = animation.ticksPerSecond;

	std::string boneAndNodeData;

	DebugBoneTrees(animation.rootBone, boneAndNodeData);


}