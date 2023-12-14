#include "Animator.h"

Animator::Animator()
{
	for (unsigned int i = 0; i < 100; i++)
	{
		this->finalMatrices.push_back(glm::mat4(1.0f));
	}
}

Animator::~Animator()
{

}

void Animator::setCurrentAnimation(RenderAnimation* currentAnimation, RenderMesh* currentMesh)
{
	this->currentAnimation = currentAnimation;
	

	this->currentMesh = currentMesh;

	for(unsigned int i = 0; i < 100; i++)
	{
		this->finalMatrices[i] = glm::mat4(1.0f);
	}
}

void Animator::updateCurrentAnimation(float& deltaTime, float& currentAnimationTime)
{
	//this->deltatime = deltaTime;

	if(this->currentAnimation)
	{
		currentAnimationTime += currentAnimation->animationData.ticksPerSecond * deltaTime;
		currentAnimationTime = fmod(currentAnimationTime,this->currentAnimation->animationData.duration);
		CalculateBonetransforms(this->currentAnimation->animationData.rootBone, glm::mat4(1.0f),currentAnimationTime);
	}
}

std::vector <glm::mat4> Animator::returnFinalMatrices()
{
	return this->finalMatrices;
}

void Animator::CalculateBonetransforms(AnimationBoneData node, glm::mat4 parentTransform, float& currentAnimationTime)
{
	std::string nodeName = node.name;
	glm::mat4 transform = node.localTransformation;

	if(node.boneNode == true)
	{
		//update / interpolate bone transforms
		glm::mat4 updatedBoneTransform = getBoneLocalTransform(node,currentAnimationTime); // this will be changed to an interpolated position later
		transform = updatedBoneTransform;
		
	}

	glm::mat4 globalTransform = parentTransform * transform;

	auto boneInfoMap = this->currentMesh->boneMap;
	if (boneInfoMap.find(nodeName) != boneInfoMap.end())
	{
		int index = boneInfoMap[nodeName].BoneId;
		glm::mat4 offset = boneInfoMap[nodeName].boneMatrix;
		this->finalMatrices[index] = globalTransform * offset;
	}

	

	for (int i = 0; i < node.childrenCount; i++)
	{
		CalculateBonetransforms(node.children[i], globalTransform, currentAnimationTime);
	}

}

glm::mat4 Animator::interpolatePosition(float animationTime, AnimationBoneData node)
{
	if(1 == node.numPositions)
	{
		return glm::translate(glm::mat4(1.0f), node.Positions[0].position);
	}

	int p0Index = GetPositionIndex(animationTime,node);
	int p1Index = p0Index + 1;
	float scaleFactor = GetScaleFactor(node.Positions[p0Index].timestamp,
		node.Positions[p1Index].timestamp, animationTime);
	glm::vec3 finalPosition = glm::mix(node.Positions[p0Index].position, node.Positions[p1Index].position
		, scaleFactor);
	return glm::translate(glm::mat4(1.0f), finalPosition);
}

glm::mat4 Animator::interpolateRotation(float animationTime, AnimationBoneData node)
{
	if (1 == node.numRotations)
	{
		auto rotation = glm::normalize(node.Rotations[0].rotation);
		return glm::toMat4(rotation);
	}

	int p0Index = GetRotationIndex(animationTime,node);
	int p1Index = p0Index + 1;
	float scaleFactor = GetScaleFactor(node.Rotations[p0Index].timestamp,
		node.Rotations[p1Index].timestamp, animationTime);
	glm::quat finalRotation = glm::slerp(node.Rotations[p0Index].rotation, node.Rotations[p1Index].rotation, scaleFactor);

	finalRotation = glm::normalize(finalRotation);
	return glm::toMat4(finalRotation);
}

glm::mat4 Animator::interpolateScale(float animationTime, AnimationBoneData node)
{
	if (1 == node.numScalings)
		return glm::scale(glm::mat4(1.0f), node.Scalings[0].scale);

	int p0Index = GetScaleIndex(animationTime,node);
	int p1Index = p0Index + 1;
	float scaleFactor = GetScaleFactor(node.Scalings[p0Index].timestamp,
		node.Scalings[p1Index].timestamp, animationTime);
	glm::vec3 finalScale = glm::mix(node.Scalings[p0Index].scale, node.Scalings[p1Index].scale
		, scaleFactor);
	return glm::scale(glm::mat4(1.0f), finalScale);
}

float Animator::GetScaleFactor(float lastTimeStamp, float nextTimeStamp, float animationTime)
{
	float scaleFactor = 0.0f;
	float midWayLength = animationTime - lastTimeStamp;
	float framesDiff = nextTimeStamp - lastTimeStamp;
	scaleFactor = midWayLength / framesDiff;
	return scaleFactor;
}

int Animator::GetPositionIndex(float animationTime, AnimationBoneData node)
{
	for (int index = 0; index < node.numPositions - 1; ++index)
	{
		if (animationTime < node.Positions[index + 1].timestamp)
			return index;
	}
	assert(0);
}

int Animator::GetRotationIndex(float animationTime, AnimationBoneData node)
{
	for (int index = 0; index < node.numRotations - 1; ++index)
	{
		if (animationTime < node.Rotations[index + 1].timestamp)
			return index;
	}
	assert(0);
}

int Animator::GetScaleIndex(float animationTime, AnimationBoneData node)
{
	for (int index = 0; index < node.numScalings - 1; ++index)
	{
		if (animationTime < node.Scalings[index + 1].timestamp)
			return index;
	}
	assert(0);
}

glm::mat4 Animator::getBoneLocalTransform(AnimationBoneData node,float& currentAnimationTime) 
{
	glm::mat4 translation = interpolatePosition(currentAnimationTime,node);
	glm::mat4 rotation = interpolateRotation(currentAnimationTime, node);
	glm::mat4 scale = interpolateScale(currentAnimationTime, node);

	glm::mat4 localTransformation = translation * rotation * scale;

	return localTransformation;
}