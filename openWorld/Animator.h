#pragma once
#ifndef ANIMATOR_H
#define ANIMATOR_H

#include "includes/glm/glm.hpp"
#include "Includes/glm/gtc/type_ptr.hpp"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/string_cast.hpp>

#include <unordered_map>

#include "renderingInfoDefinitions.h"
#include "animationDataDefinitions.h"

#include "Shader.h"

//this is the last animation key used for the current animation
struct animationKey
{
	KeyPosition position;
	keyRotation rotation;
	keyScale scale;
};

struct blendedAnimation
{
	animation* anim1;
	animation* anim2;
	float blendFactor;
};

class animator
{
public:

	static void addAnimation(Model* model, animation* animation);

	static void removeAnimation(Model* model, animation* animation);

	static void changeAnimation(Model* model, animation* newAnimation);

	static void setAnimationMatrices(Model* model, Shader* shader);

	static void updateAnimations(float dt);

	static void stepAnimation(animation* anim);

private:

	static glm::mat4 stepAnimations(float currentTime, animBone* bone);

	animator() {};

	static void updateAnimation(animation* animation, float dt, Model* model);

	static void CalculateBoneTransforms(AssimpNodeData* Node, glm::mat4 parentTransform, animation* anim, Model* model);

	static glm::mat4 calculateLocalBoneTransform(float currentTime, animBone* bone);

	static glm::mat4 interpolatePosition(float animationTime, animBone* bone);
	static glm::mat4 interpolateRotation(float animationTime, animBone* bone);
	static glm::mat4 interpolateScale(float animationTime, animBone* bone);

	static float calculateScaleFactor(float lastTimeStamp, float nextTimeStamp, float currentTime);

	static	std::unordered_map<Model*, animation*> activeAnimations;
	static	std::unordered_map<animation*, std::vector <glm::mat4>> animationMatrices;

	static std::vector <Model*> activeModels;

	static int stepper;
};

#endif // !ANIMATOR_H
