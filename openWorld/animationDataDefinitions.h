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
	float duration; //in ticks
	int ticksPerSecond; //should be 1000
	std::string name;
	AssimpNodeData rootNode;
	std::vector <animBone> bones;
	std::unordered_map <std::string, animBone*> animBones;
	float currentTime = 0.0; //can get rid of this with the new animator
	bool looping = true; //if looping is true this animation is continuous (walking, running) if not the animation will end after it's duration
};

struct inverseKinematicChain
{
	std::vector <Bone*> bones; //list of bones that need to be modified to achieve the end movement
	Bone* endEffector; //main bone that needs to be modified
	glm::vec3 targetPosition; //target point for the bone
};