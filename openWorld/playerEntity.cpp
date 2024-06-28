#include "playerEntity.h"

playerEntity::playerEntity(std::string playerFilePath)
{
	this->playerModel = ResourceManager::loadModel(playerFilePath,"player");
	loadPlayerAnimations(playerFilePath);

	transform newTransform;
	newTransform.position = glm::vec3(2, 10, -2);
	newTransform.orientation = glm::quat(1.0, 0.0, 0.0, 0.0);
	newTransform.scale = glm::vec3(1.0f);

	this->currentTransform = newTransform;//default transform for now
	//all set to new since its a new player being made (born if you will)
	this->meshChange = true;
	this->actionChange = true;
	this->animationChange = true;
	this->currentAnimation = this->animations["idle"];
	animator::addAnimation(this->playerModel, this->currentAnimation);
	updateEntity();
}

//not all animations added yet and no error checking yet really
void playerEntity::loadPlayerAnimations(std::string playerFilePath)
{
	//idle //found
	this->animations["idle"] = ResourceManager::loadAnimation("resources/player/animations/idle.gltf", "playerIdle", "player");
	this->actionDebugger.push_back(idle);
	//idlePistol //found
	this->animations["idlePistol"] = ResourceManager::loadAnimation("resources/player/animations/pistolIdle.gltf", "playerIdlePistol", "player");
	this->actionDebugger.push_back(idlePistol);
	//idleRifle //found
	this->animations["idleRifle"] = ResourceManager::loadAnimation("resources/player/animations/rifleIdle.gltf", "playerIdleRifle", "player");
	this->actionDebugger.push_back(idleRifle);
	//walking //found
	this->animations["walking"] = ResourceManager::loadAnimation("resources/player/animations/walking.gltf", "playerWalking", "player");
	this->actionDebugger.push_back(walking);
	
	//sideWalkLeft
	//sideWalkRight
	//walkingBack
	
	//walkingPistolLowered
	
	//walkingPistolRaised //found
	this->animations["walkPistolRaised"] = ResourceManager::loadAnimation("resources/player/animations/pistolWalkForward.gltf", "playerWalkPistolRaised", "player");
	this->actionDebugger.push_back(walkingPistolRaised);

	//walkingRifleLowered
	
	//walkingRifleRaise //found
	this->animations["walkRifleRaised"] = ResourceManager::loadAnimation("resources/player/animations/rifleWalkForward.gltf", "playerWalkRifleRaised", "player");
	this->actionDebugger.push_back(walkingRifleRaised);
	//leftTurn
	//rightTurn

	//jogging //found
	this->animations["jogging"] = ResourceManager::loadAnimation("resources/player/animations/jogging.gltf", "playerJogging", "player");
	this->actionDebugger.push_back(jogging);
	//sideJogLeft
	//sideJogRight
	
	//joggingPistolLowered
	//joggingRifleLowered

	//leftJoggingTurn
	//rightJoggingTurn

	//running //found
	this->animations["running"] = ResourceManager::loadAnimation("resources/player/animations/running.gltf", "playerRunning", "player");
	this->actionDebugger.push_back(running);

	//leftRunninggTurn
	//rightRunningTurn

	//crouching
	//crouchingPistol
	//crouchingRifle //found
	this->animations["crouchingRifle"] = ResourceManager::loadAnimation("resources/player/animations/rifleCrouchedAiming.gltf", "playerCrouchingRifle", "player");
	this->actionDebugger.push_back(crouchingRile);

	//crouchWalking
	 
	//crouchWalkingPistolLowered
	//crouchWalkingPistolRaised
	
	//crouchWalkingRifleLowered
	//crouchWalkingRifleRaise //found
	this->animations["crouchWalkingRifle"] = ResourceManager::loadAnimation("resources/player/animations/rifleWalkForward.gltf", "playerCrouchWalkingRifle", "player");
	this->actionDebugger.push_back(crouchWalkingRifleRaise);

	//jumping //found
	this->animations["jumping"] = ResourceManager::loadAnimation("resources/player/animations/jump.gltf", "playerJumping", "player");
	this->actionDebugger.push_back(jumping);

	//diveRight
	//diveLeft
	//jumpBack
	//diveForward

	//climbingSmall
	//climingTall

	//falling

	//dying //found
	this->animations["dying"] = ResourceManager::loadAnimation("resources/player/animations/dying.gltf", "playerDying", "player");
	this->actionDebugger.push_back(dying);
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
void playerEntity::setPlayerMeshes(playerParts part, Mesh* newMesh)
{
	this->playersParts[part] = newMesh;
	this->meshChange = true;
	updateEntity();
}

void playerEntity::debugAnimations()
{
	if (stepper >= actionDebugger.size()) { stepper = 0; }
	setPlayerAction(actionDebugger[stepper]);
	updateEntity();
	stepper++;

}

void playerEntity::updateEntity()
{
	if (meshChange)
	{
		//update meshes in the scene or whatever
	}

	if (actionChange)
	{
		//update action parameters
		updateActions();
		actionChange = false;
	}

	if (animationChange)
	{
		//update to the new animation, after action change check because thats what should set new animations and nothing else
		animator::changeAnimation(this->playerModel, this->currentAnimation);
		animationChange = false;
	}

}

Model* playerEntity::getPlayerModel()
{
	return this->playerModel;
}

void playerEntity::updateActions()
{
	
	switch(this->currentAction)
	{
	case(idle):
		this->currentAnimation = this->animations["idle"];
		this->animationChange = true;
		break;

	case(idlePistol):
		this->currentAnimation = this->animations["idlePistol"];
		this->animationChange = true;
		break;

	case(idleRifle):
		this->currentAnimation = this->animations["idleRifle"];
		this->animationChange = true;
		break;

	case(walking):
		this->currentAnimation = this->animations["walking"];
		this->animationChange = true;
		
		//move forward as well by however much
		break;

	case(walkingPistolRaised):
		this->currentAnimation = this->animations["walkPistolRaised"];
		this->animationChange = true;
		//move forward as well by however much
		break;

	case(walkingRifleRaised):
		this->currentAnimation = this->animations["walkRifleRaised"];
		this->animationChange = true;
		//move forward as well by however much
		break;

	case(jogging):
		this->currentAnimation = this->animations["jogging"];
		this->animationChange = true;
		//move forward as well by however much
		break;

	case(running):
		this->currentAnimation = this->animations["running"];
		this->animationChange = true;
		//move forward as well by however much
		break;

	case(crouchWalkingRifleRaise):
		this->currentAnimation = this->animations["crouchingRifle"];
		this->animationChange = true;
		//move forward as well by however much
		break;

	case(jumping):
		this->currentAnimation = this->animations["jumping"];
		this->animationChange = true;
		//jump (duh), move up and down a lil bit
		break;

	case(dying):
		this->currentAnimation = this->animations["dying"];
		this->animationChange = true;
		//die, thats pretty much it
		break;


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

void playerEntity::setPlayerTransform(transform newTransform)
{
	this->currentTransform = newTransform;
}

transform* playerEntity::getPlayersTransform()
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

void playerEntity::calculateRelTransform()
{
	glm::quat tempQuat = this->currentTransform.orientation;

	glm::vec3 front;
	front.x = 2 * (tempQuat.x * tempQuat.z + tempQuat.w * tempQuat.y);
	front.y = 2 * (tempQuat.y * tempQuat.z - tempQuat.w * tempQuat.x);
	front.z = 1 - 2 * (tempQuat.x * tempQuat.x + tempQuat.y + tempQuat.y);

	glm::vec3 right = glm::vec3(0,0,0);
	glm::vec3 up = glm::vec3(0,0,0);

	this->relativeTransf.front = front;
	this->relativeTransf.up = up;
	this->relativeTransf.right = right;
}