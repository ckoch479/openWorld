#pragma once

#include <iostream>
#include <vector>
#include <list>

#include <assimp/scene.h>

#include "Includes/glm/glm.hpp"
#define GLM_ENABLE_EXPERIMENTAL
#include "Includes/glm/gtx/quaternion.hpp"

#include "assimp_glm_helpers.h"

#ifndef BONE_H
#define BONE_H

struct KeyPosition
{
	glm::vec3 position;
	float timestamp;
};

struct KeyRotation
{
	glm::quat rotation;
	float timestamp;
};

struct KeyScale
{
	glm::vec3 scale;
	float timestamp;
};

//Animation data for each bone is stored in this class 
class Bone
{
public:

	Bone(const std::string& name, int ID, const aiNodeAnim* channel);

	~Bone();

	glm::mat4 getLocalTransform();

	std::string getBoneName() const;

	int getBoneID();

	int getNumPositions();

	int getNumRotations();

	int getNumScalings();

	std::vector <KeyPosition> getPositions();

	std::vector <KeyRotation> getRotations();

	std::vector <KeyScale> getScalings();

private:
	std::vector <KeyPosition> Positions;
	std::vector <KeyRotation> Rotations;
	std::vector <KeyScale> Scalings;

	int numPositions;
	int numRotations;
	int numScalings;

	glm::mat4 localTransform;
	std::string name;
	int boneID;

};

#endif