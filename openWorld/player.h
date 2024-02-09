#pragma once

#include <iostream>
#include <vector>
#include <map>

#include "includes/glm/glm.hpp"
#include "Includes/glm/gtc/type_ptr.hpp"
#include "Includes/glm/gtc/quaternion.hpp"

#include "ResourceManager.h"
#include "Collider.h"
#include "RigidBody.h"
#include "physicsWorld.h"

#include "Scene.h"

#ifndef PLAYER_H
#define PLAYER_H

enum playerRelativePosition
{
PlayerFront,
PlayerLeft,
PlayerUp,
};

class player
{
public:
	player();
	~player();

	glm::vec3 GetCurrentPosition();

	float GetRotationAngle();

	void LoadPlayerModel(const std::string filepath, std::string playername);

	void AddAnimationtoPlayer(AnimationData* animation, std::string name);

	void AddAnimationtoPlayer(std::string filepath, std::string name); 

	std::string getCurrentAnimation();

	void setCurrentAnimation(std::string animationName); //can be used to reference the animation either by the resource manager or the scene

	void setPosition(glm::vec3 position);

	void setRotationAngle(float angle);

	void setRelativePosition(playerRelativePosition relativePosition, float distance);

	void setPlayerFront(glm::vec3 front);

private:

	void calculatePlayerFront();

	void setCurrentAnimationActive(std::string animationName);

	glm::vec3 position;
	glm::vec3 rotationAxis;
	float rotationAngle;

	glm::vec3 playerFront;
	glm::vec3 playerLeft;
	glm::vec3 playerUp;

	float yaw;
	

	std::vector <std::string> SavedAnimations;
	std::vector <AnimationData*> Animations;
	std::string playerName;

	ModelData* playerModel;

	AnimationData* currentAnimation;
	std::string currentAnimationName;


};

#endif // !PLAYER_H