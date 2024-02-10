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
PlayerRight,
PlayerBack
};

class player
{
public:
	player();
	~player();

	glm::vec3 GetCurrentPosition();

	float GetRotationAngle();

	void LoadPlayerModel(const std::string filepath, std::string playername, Scene* scene, PhysicsWorld* world, Shader& shader);

	void AddAnimationtoPlayer(AnimationData* animation, std::string name);

	void AddAnimationtoPlayer(std::string filepath, std::string name); 

	std::string getCurrentAnimation();

	void setCurrentAnimation(std::string animationName); //can be used to reference the animation either by the resource manager or the scene

	void setPosition(glm::vec3 position); //if you need to set the character position manually

	void setRotationAngle(float angle); 

	void setRelativePosition(playerRelativePosition relativePosition, float deltaTime);

	void setPlayerFront(glm::vec3 front);

	void setMovementSpeed(float speed);

	void setPlayerYaw(float yaw);

	void renderPlayer(float dt, Scene* scene, PhysicsWorld* world);

private:

	void calculateVectors();

	void setActiveAnimation(std::string animationName);

	glm::vec3 position = glm::vec3(0.0);
	glm::vec3 rotationAxis = glm::vec3(0,1,0);
	float rotationAngle = 0;
	glm::vec3 scale = glm::vec3(1.0f);

	glm::vec3 playerFront;
	glm::vec3 playerRight;
	glm::vec3 playerUp;

	float yaw = 0;
	float pitch = 0;

	float movementSpeed;
	

	std::vector <std::string> SavedAnimations;
	std::vector <AnimationData*> Animations;
	std::string playerName;

	ModelData* playerModel;

	AnimationData* currentAnimation;
	std::string currentAnimationName;

	std::map <std::string, AnimationData*> animationMap;

	ID sceneModelID;
	ID sceneTransformID;
	ID sceneObjectID;
	ID rigidBodyID;
	ID physicsWorldObjectID;

	std::vector <ID> animationIDs;
	std::map <std::string, ID> animationIDmap;


	//utility
	Scene* scenePtr;
	Shader* shaderPtr;
	PhysicsWorld* worldPtr;


};

#endif // !PLAYER_H