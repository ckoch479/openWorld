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

#ifndef OBJANIMATOR_H
#define OBJANIMATOR_H



class objAnimator
{
public:

	objAnimator();

	void loadAnimation(std::string& animationName, std::string& animationFilePath);

	void playAnimation(std::string& animationName);

	void update(float deltaTime);

	void applyForwardKinematics(std::string& boneName, glm::quat& rotation);

	void applyInverseKinematics(std::string& endEffector, glm::vec3& targetPosition);

	void solveIK();

	void setSkeleton(skeleton* newSkeleton);

	void addBone(Bone& newBone);


private:

	//data
	skeleton* animationSkeleton;
	std::unordered_map<std::string, animation*> animations;
	std::map <std::string, glm::quat> forwardKinematicRotations;
	std::vector <inverseKinematicChain> IKchains;

	//private methods

	void updateForwardKinematics();

	void updateInverseKinematics();

	void blendAnimations();
	
	glm::vec3 Lerp(glm::vec3 valueA, glm::vec3 valueB, float factor);

};

#endif