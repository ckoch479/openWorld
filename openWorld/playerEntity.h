#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>

#include "renderingInfoDefinitions.h"
#include "animationDataDefinitions.h"

#include "playerActionDefinitions.h"

#include "ResourceManager.h"
#include "objAnimator.h"
#include "Scene.h"
#include "Shader.h"

#include "playerHandSlot.h"

#ifndef PLAYERENTITY_H
#define PLAYERENTITY_H

//player entity class is a class that will be used to manage the players current status (what action they are preforming running, climing, walking, ect), as well as
//the important gameplay player stuff such as health, and inventory, this class will also call to then renderer to draw player related U.I components like the hud,
//inventory menu, game map, ect. This class is not responsible for defining when player actions are happening, it is only responsible for moving resources to where they need to be
//after being told the player is preforming an action and preforming the steps needed to make them appear on screen (mainly animations),

class playerEntity
{
public:
	
	 playerEntity(std::string playerFilePath);

	~playerEntity();

	void savePlayerFile();//this will save players data to a .player file that can be used the next time a playerEntity is created

	void setPlayerAction(playerActions action);

	void setActionModifier(actionModifiers mod, bool setter); //use this to update which modifiers are set to or false

	bool getActionModifier(actionModifiers mod); //used to fetch what state the modifiers are in

	void resetDirectionalActionMods();

	//change player looks/resistances
	void setPlayerMeshes(playerParts part, Mesh* newMesh); //allows on the fly update to a player mesh for each body part

	//player movement

	void setPlayerTransform(transform newTransform);

	transform* getPlayersTransform();

	relTransform* getPlayerRelativeTransform(); //this cannot be set manually and is only updated by the class based on render transform parameters

	Model* getPlayerModel();

	playerActions getPlayerAction();

	void calculateRelTransform();

	void addPlayerToScene(scene* scene, Shader* shader);

	void updatePlayerScene(scene* scene);

	glm::mat4 getLeftHandTransform();
	glm::mat4 getRightHandTransform();

	glm::mat4 getRightHandOffsetMatrix();
	glm::mat4 getLeftHandOffsetMatrix();

	objAnimator* getPlayerAnimator();

	void updateEntity();

	std::vector <Bone*> getBones();

private:

	void setIdleAnimation();

	void setWalkingAnimation();

	void setJoggingAnimation();

	void setTurningAnimation();

	void setSprintingAnimation();

	void setJumpingAnimation();

	void loadPlayerAnimations(std::string playerFilePath); //directory for player animations will be under the players file path in a file named animations

	void updateActions();

	objAnimator* playerAnimator;

	//data:
	
	//animation names should exactly match player action name as well key word is should it is me making this thing
	//also animations is only handled by the class you cannot manually change the animations only player actions

	//transforms and movement
	//this is position, orientation, and scaling for renderer
	relTransform relativeTransf; //this is front, up, and right

	//players mesh (changing clothing/gear and such), actual data is stored in resource manager
	std::unordered_map<playerParts, Mesh*> playersParts;

	//player file path from .player file format
	std::string playerFilePath;

	std::string playerName; //this one should be pretty self explanatory
	
	//helper bools for updating the player on the fly
	//bool leftHandWeapon = false;
	//bool rightHandWeapon = false;
	//bool bothHandWeapon = false;

	//Action modifiers:
	bool walkToggled = false;
	bool sprintToggled = false;
	bool crouching = false;
	bool crawling = false;
	bool aiming = false;
	bool shooting = false;
	bool leftward = false;
	bool rightward = false;
	bool front = false;
	bool back = false;
	bool oneHanded = true;
	bool twoHanded = false;


	//object states/state changes
	bool meshChange = false;
	bool animationChange = false;
	bool actionChange = false;

	bool isInjured = false;

	std::string activeAnim;//current active animation

	playerActions currentAction;

	//rendering data
	Model* playerModel;

	std::string sceneID;

	transform currentTransform;

};

#endif