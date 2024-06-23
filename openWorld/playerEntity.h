#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>

#include "scene.h"
#include "renderingInfoDefinitions.h"

#include "playerActionDefinitions.h"

#ifndef PLAYERENTITY_H
#define PLAYERENTITY_H

//player entity class is a class that will be used to manage the players current status (what action they are preforming running, climing, walking, ect), as well as
//the important gameplay player stuff such as health, and inventory, this class will also call to then renderer to draw player related U.I components like the hud,
//inventory menu, game map, ect. This class is not responsible for defining when player actions are happening, it is only responsible for moving resources to where they need to be
//after being told the player is preforming an action and preforming the steps needed to make them appear on screen (mainly animations),

class playerEntity
{
public:
	
	 playerEntity(const char* playerFilePath);

	~playerEntity();

	void savePlayerFile();//this will save players data to a .player file that can be used the next time a playerEntity is created

	void setPlayerAction(playerActions action);

	//change player looks/resistances
	void setPlayerMeshes(playerParts part, mesh* newMesh); //allows on the fly update to a player mesh for each body part

	void setPlayerResistance(playerParts part, int newResistance);

	//change health parameters
	void setPlayerInjury(playerParts part, injuryStatus status);

	void setPlayerHealth(int health);

	void setPlayerStamina(int stamina);

	injuryStatus getInjuryStatus(playerParts part);

	int getPlayerHealth();

	int getPlayerStamina();

	int getPlayerResistance(playerParts part);

	//player movement

	void setPlayerTransform(Transform newTransform);

	Transform* getPlayersTransform();

	relTransform* getPlayerRelativeTransform(); //this cannot be set manually and is only updated by the class based on render transform parameters

	void setPlayerMoveSpeed(int newSpeed);

	int getPlayerMoveSpeed();

private:

	void updateEntity(); //this should get called any time something about the player changes to update its data

	//data:
	playerActions currentAction;
	
	float moveSpeed;

	//animation names should exactly match player action name as well key word is should it is me making this thing
	//also animations is only handled by the class you cannot manually change the animations only player actions
	std::unordered_map<std::string, animation*> animations;

	//transforms and movement
	Transform currentTransform; //this is position, orientation, and scaling for renderer
	relTransform relativeTransf; //this is front, up, and right

	//players mesh (changing clothing/gear and such), actual data is stored in resource manager
	std::unordered_map<playerParts, mesh*> playersParts;

	//injuries and health concerns
	std::unordered_map<playerParts, injuryStatus> playerInjuries;
	int health;
	int stamina; //how long the player can preform actions like sprinting, climbing, ect

	//this is armor resistance kinda like thicker clothing and such
	std::unordered_map<playerParts, int> resistance;

	//player file path from .player file format
	std::string playerFilePath;

	Model* playerModel; //this is just a little thing to make rendering easier for myself

	std::string playerName; //this one should be pretty self explanatory

	//helper bools for updating the player on the fly
	bool meshChange = false;
	bool animationChange = false;
	bool actionChange = false;
};

#endif