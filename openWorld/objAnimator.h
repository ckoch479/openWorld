#pragma once

#include "includes/glm/glm.hpp"
#include "Includes/glm/gtc/type_ptr.hpp"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/string_cast.hpp>

#include "renderingInfoDefinitions.h"
#include "animationDataDefinitions.h"

#include "Bone.h"
#include "skeleton.h"

#include "ResourceManager.h"

#ifndef OBJANIMATOR_H
#define OBJANIMATOR_H



class objAnimator
{
public:

	objAnimator(Model* model);

	void loadAnimation(std::string& animationName, std::string& animationFilePath, bool loopingAnimation);

	void playAnimation(std::string& animationName);

	void update(float deltaTime);

	void applyForwardKinematics(std::string& boneName, glm::quat& rotation);

	void applyInverseKinematics(std::string& endEffector, glm::vec3& targetPosition);

	void solveIK();

	void setSkeleton(skeleton* newSkeleton);

	void addBone(Bone& newBone);

	void calculateFKTransforms(AssimpNodeData* node, glm::mat4& parentTransform);

	std::vector <glm::mat4> getAnimationTransforms();
private:

	//data
	Model* animModel; //model that uses these animations and animator
	skeleton* animationSkeleton;
	animation* activeAnimation;
	std::unordered_map<std::string, animation*> animations;
	std::map <std::string, glm::quat> forwardKinematicRotations;
	std::vector <inverseKinematicChain> IKchains;
	std::vector <glm::mat4> finalMatricies; //should be exactly 100 due to max bones being 100

	float currentTimeStep = 0.0f; //in seconds or technically in fractions of a second since its the amount of time between frames

	float currentAnimationTime = 0.0f; //animation is assumed to have 1000 ticks per second 
	//private methods

	void updateForwardKinematics();

	void updateInverseKinematics();

	void blendAnimations();

	glm::mat4 calculateLocalBoneTransform(AssimpNodeData* node);
	
	glm::vec3 Lerp(glm::vec3 valueA, glm::vec3 valueB, float factor);

	glm::quat Slerp(glm::quat rotA, glm::quat rotB, float factor);

	glm::mat4 getLocalTranslation(AssimpNodeData* node);

	glm::mat4 getLocalRotation(AssimpNodeData* node);

	float calculateScaleFactor(float lastTimeStamp, float nextTimeStamp, float currentTime);

};

#endif