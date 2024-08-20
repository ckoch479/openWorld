#pragma once
#ifndef ASSIMPANIMATIONLOADER_H
#define ASSIMPANIMATIONLOADER_H

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <map>

#include "includes/glm/glm.hpp"
#include "Includes/glm/gtc/type_ptr.hpp"

#include <assimp/Importer.hpp>
#include <Assimp/scene.h>
#include <assimp/postprocess.h>

#include "renderingInfoDefinitions.h"
#include "animationDataDefinitions.h"

#include "Model.h"

#include "assimpGLMConverter.h"



class assimpAnimationLoader
{
public:
	assimpAnimationLoader(const std::string& filePath, Model* model);

	~assimpAnimationLoader();

	animation getAnimation();

	animBone* findBone(const std::string& name);

private:

	void readMissingBones(const aiAnimation* animation, Model* model);

	void readHierarchyData(AssimpNodeData& dest, const aiNode* src);

	animBone createBoneNode(std::string name, int id, const aiNodeAnim* channel);


	float Duration;
	int ticksPerSecond;
	std::string name;
	std::vector <animBone> bones;
	AssimpNodeData rootNode;
	std::map <std::string, Bone> boneInfoMap;
};

#endif

