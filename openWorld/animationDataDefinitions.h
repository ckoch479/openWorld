#pragma once
#include "includes/glm/glm.hpp"
#include "Includes/glm/gtc/type_ptr.hpp"

#include <vector>
#include <string>
#include <map>
#include <unordered_map>

struct KeyPosition
{
	glm::vec3 position;
	float timeStamp;
};

struct keyRotation
{
	glm::quat orientation;
	float timeStamp;
};

struct keyScale
{
	glm::vec3 scale;
	float timeStamp;
};

struct animBone
{
	std::string name;
	int id;
	glm::mat4 localTransform;

	int numPositions;
	int numRotations;
	int numScales;

	std::vector <KeyPosition> positions;
	std::vector <keyRotation> rotations;
	std::vector <keyScale> scales;

	// bellow was added due to issues with timesteps in animation hopefully will be resolved
	int currentPosition = 0;
	int currentRotation = 0;
	int currentScale = 0;

	void stepPosition()
	{
		this->currentPosition++;
		if (this->currentPosition > numPositions)
		{
			this->currentPosition = 0;
		}
	};
	void stepRotation()
	{
		this->currentRotation++;
		if (this->currentRotation > numRotations)
		{
			this->currentRotation = 0;
		}
	};
	void stepScale()
	{
		this->currentScale++;
		if (this->currentScale > numScales)
		{
			this->currentScale = 0;
		}
	};

};

struct AssimpNodeData
{
	glm::mat4 transformation;
	std::string name;
	int childrenCount;
	std::vector <AssimpNodeData> children;
};

struct animation
{
	float duration;
	int ticksPerSecond;
	std::string name;
	AssimpNodeData rootNode;
	std::vector <animBone> bones;
	std::unordered_map <std::string, animBone*> animBones;
	float currentTime = 0.0;
};

struct inverseKinematicChain
{
	std::vector <Bone*> bones;
	Bone* endEffector;
	glm::vec3 targetPosition;
};