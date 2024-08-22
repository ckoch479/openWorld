#pragma once

#include <iostream>
#include <vector>
#include <map>

#include "includes/glm/glm.hpp"
#include "Includes/glm/gtc/type_ptr.hpp"
#include "Includes/glm/gtc/quaternion.hpp"
#include <glm/gtx/string_cast.hpp>

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
#include "renderContext.h"
#include "PhysicsWorld.h"

#include "debugger.h"
#ifndef PLAYER_H
#define PLAYER_H

class player : public Entity
{
public:

	player(renderContext context, Model* newModel, windowManager* inputManager, PhysicsWorld* world);

	~player();

	void update(float dt);

	void debugDirections(debugger* debug);

private:

	playerActions currentAction; //set by character controller
	playerActions secondaryAction;

	std::string currentAnimation; //set by animation controller

	Model* playerModel; //eventually will be replaced by a vector or array of models for each individual part
	skeleton* playerSkeleton;
	renderContext renderData;

	//these variables are stored in the Entity class under protected but are placed here for clarity (mainly for me because im sorta dumb)
	glm::vec3* positionPtr;
	glm::quat* orientationPtr;
	glm::vec3* scalePtr;

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

	//
	// playerAnimator - should already be mostly done for testing purposes at least, animations are really fast for some reason(fixed, was updating the player twice per frame)
	// renderer -works now for testing purposes at least, should be mostly good
	// playerController -has some basic implimentation able to test and use
	// collider implimented player now has one main collider and a vector of colliders that follow bones from animation
	// animationController -has some very basic implimentation
	// motionController -needs implimentation
	// cameraController -has most implimentation for basics done, can be used for testing properly
	//
	
};

#endif // !PLAYER_H