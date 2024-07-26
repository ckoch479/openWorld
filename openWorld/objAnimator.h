#pragma once

#include "includes/glm/glm.hpp"
#include "Includes/glm/gtc/type_ptr.hpp"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/string_cast.hpp>

#include "renderingInfoDefinitions.h"
#include "animationDataDefinitions.h"

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

	void setSkeleton();
	void addBone(Bone& newBone);


private:

	//data
	//skeleton
	std::unordered_map<std::string, animation*> animations;
	std::map <std::string, glm::quat> forwardKinematicRotations;
	

};

#endif