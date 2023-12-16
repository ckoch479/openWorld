#pragma once
#include <glad/glad.h>
#include "GLFW/glfw3.h"

#include <iostream>
#include <vector>
#include <map>
#include <string>

#include "includes/glm/glm.hpp"
#include "Includes/glm/gtc/type_ptr.hpp"

#include "lookup_table.h"
#include "ResourceManager.h"

#include "Scene.h"



#ifndef ANIMATOR_H
#define ANIMATOR_H
class Animator
{
public:

	Animator();
	~Animator();

	void setCurrentAnimation(RenderAnimation* currentAnimation, RenderModel* currentModel);

	void updateCurrentAnimation(float& deltaTime, float& currentAnimationTime);

	std::vector <glm::mat4> returnFinalMatrices();


private:
	std::vector <glm::mat4> finalMatrices;
	RenderAnimation* currentAnimation;
	RenderModel* currentModel;
	float deltatime;

	void CalculateBonetransforms(AnimationBoneData node, glm::mat4 parentTransform, float& currentAnimationTime);

	glm::mat4 interpolatePosition(float animationTime, AnimationBoneData node);

	glm::mat4 interpolateRotation(float animationTime, AnimationBoneData node);

	glm::mat4 interpolateScale(float animationTime, AnimationBoneData node);

	glm::mat4 getBoneLocalTransform(AnimationBoneData node, float& currentAnimationTime);

	int GetPositionIndex(float animationTime, AnimationBoneData node);

	int GetRotationIndex(float animationTime, AnimationBoneData node);

	int GetScaleIndex(float animationTime, AnimationBoneData node);

	float GetScaleFactor(float lastTimeStamp, float nextTimeStamp, float animationTime);
};

#endif