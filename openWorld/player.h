#pragma once

#include <iostream>
#include <vector>
#include <map>

#include "includes/glm/glm.hpp"
#include "Includes/glm/gtc/type_ptr.hpp"
#include "Includes/glm/gtc/quaternion.hpp"

#include "Entity.h"

#include "ResourceManager.h"

#include "playerRenderer.h"
#include "characterController.h"
#include "objAnimator.h"
#include "playerCollider.h"
#include "playerAnimationController.h"
#include "playerMotionController.h"
#include "playerCameraController.h"
#include "playerActions.h"
#include "Model.h"
#include "skeleton.h"


#ifndef PLAYER_H
#define PLAYER_H

class player : public Entity
{
public:

	player();
	~player();

	void update(float dt);

private:

	playerActions currentAction; //set by character controller
	std::string currentAnimation; //set by animation controller

	Model* playerModel; //eventually will be replaced by a vector or array of models for each individual part
	skeleton* playerSkeleton;

	//these variables are stored in the Entity class under protected but are placed here for clarity (mainly for me because im sorta dumb)
	glm::vec3* position;
	glm::quat* orientation;
	glm::vec3* scale;

	std::string* name;

	// player classes
	// playerHealthManager
	// playerCameraController
	// 

	objAnimator* playerAnimator; //needs player Model in constructor and Dt during updates
	playerRenderer* renderer; //needs shader, sceneObj, and model in constructor, also needs transform and animation matrices
	characterController* playerController; //needs window manager passed into the constructor, returns player action during update
	playerCollider* collider; //needs player skeleton, physics world, boneTransforms, and maybe more
	playerAnimationController* animationController; //needs playerAnimator and playerAction(currentAction) in constructor and playerAction during state changes
	playerMotionController* motionController; //needs player action, physicsWorld, and colliders
	playerCameraController* cameraController; //needs inputs, scene, and to either create or be given a camera object
	
};

#endif // !PLAYER_H