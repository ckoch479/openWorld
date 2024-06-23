#include "playerEntity.h"

playerEntity::playerEntity(const char* playerFilePath)
{


	//all set to new since its a new player being made (born if you will)
	this->meshChange = true;
	this->actionChange = true;
	this->animationChange = true;
	updateEntity();
}

playerEntity::~playerEntity()
{

}

void playerEntity::savePlayerFile()
{

}

void playerEntity::setPlayerAction(playerActions action)
{
	this->currentAction = action;
	this->actionChange = true;
	updateEntity();
}

//change player looks/resistances
void playerEntity::setPlayerMeshes(playerParts part, mesh* newMesh)
{
	this->playersParts[part] = newMesh;
	this->meshChange = true;
	updateEntity();
}

void playerEntity::updateEntity()
{
	if(meshChange)
	{
		//update meshes in the scene or whatever
	}

	if(actionChange) 
	{
		//update action parameters
	}

	if (animationChange)
	{
		//update to the new animation, after action change check because thats what should set new animations and nothing else
	}
}

void playerEntity::setPlayerResistance(playerParts part, int newResistance)
{
	this->resistance[part] = newResistance;
}

//change health parameters
void playerEntity::setPlayerInjury(playerParts part, injuryStatus status)
{
	this->playerInjuries[part] = status;
}

void playerEntity::setPlayerHealth(int health)
{
	this->health = health;
}

void playerEntity::setPlayerStamina(int stamina)
{
	this->stamina = stamina;
}

injuryStatus playerEntity::getInjuryStatus(playerParts part)
{
	return this->playerInjuries[part];
}

int playerEntity::getPlayerHealth()
{
	return this->health;
}

int playerEntity::getPlayerStamina()
{
	return this->stamina;
}

int playerEntity::getPlayerResistance(playerParts part)
{
	return resistance[part];
}

//player movement

void playerEntity::setPlayerTransform(Transform newTransform)
{
	this->currentTransform = newTransform;
}

Transform* playerEntity::getPlayersTransform()
{
	return &this->currentTransform;
}

relTransform* playerEntity::getPlayerRelativeTransform()
{
	return &this->relativeTransf;
}

void playerEntity::setPlayerMoveSpeed(int newSpeed)
{
	this->moveSpeed = newSpeed;
}

int playerEntity::getPlayerMoveSpeed()
{
	return this->moveSpeed;
}