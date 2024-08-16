#pragma once

#include <iostream>
#include <vector>

#include "renderingInfoDefinitions.h"
#include "animationDataDefinitions.h"

#include "objAnimator.h"
#include "skeleton.h"
#include "Bone.h"

#ifndef ANIMATED_H
#define ANIMATED_H

class animated
{
public:

	animated(std::string uniqueID, Model* animatedModel);

	~animated();

	void addAnimation(std::string filePath, std::string name, bool loopingAnimation);

	void playAnimation(std::string name);

private:

	Model* animatedModel; //for reference to the skeleton of the model, a model is absolutely needed for an object to be animated, currently animation matrices are set in the model, may need to change
	objAnimator* componentAnimator;
	skeleton* objSkeleton;

	std::vector <std::string> animations; //animations currently loaded and usable

	std::string uniqueID = "NULL";
	//may need to add a default animation
};

#endif