#pragma once
#include <iostream>

#include "includes/glm/glm.hpp"
#include "includes/glm/gtc/type_ptr.hpp"
#include "includes/glm/gtc/quaternion.hpp"

#include "renderingInfoDefinitions.h"
#include "animationDataDefinitions.h"
#include "objAnimator.h"

#ifndef WIELDABLE_H
#define WIELDABLE_H

class wieldable
{
public:

	wieldable(std::string uniqueId);
	~wieldable();

	void attachToModel(Model* entityModel, objAnimator* entityAnimator, std::string boneName, bool isTwoHanded, std::string secondaryBoneName);

	void calculateHandPosition(glm::vec3 entityPos, glm::quat entityOrient, glm::vec3 entityScale);

	void setLocalTransform(glm::vec3 pos, glm::quat orient, glm::vec3 scale);

	glm::vec3 getWorldPos();
	glm::quat getWorldOrient();
	glm::vec3 getWorldScale();

private:

	//in world space
	glm::vec3 position;
	glm::quat orientation;
	glm::vec3 scale;

	//local adjustments
	glm::vec3 localPos;
	glm::quat localOrient;
	glm::vec3 localScale;

	std::string uniqueID;
	std::string boneName; //name of the socket bone that this item attaches to

	bool twoHanded = false;
	std::string secondaryBoneName;

	//model this object is wielded by, is required for wieldable items
	Model* entityModel;
	//animator for the entity and it's model is also required due to wieldable items attaching to socket bones added in modeling software
	objAnimator* entityAnimator;
};

#endif