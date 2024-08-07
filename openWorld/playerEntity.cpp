#include "playerEntity.h"

playerEntity::playerEntity(std::string playerFilePath)
{
	this->playerModel = ResourceManager::loadModel(playerFilePath,"player");
	
	transform newTransform;
	newTransform.position = glm::vec3(0, 2, 0);
	newTransform.orientation = glm::quat(1.0, 0.0, 0.0, 0.0);
	newTransform.scale = glm::vec3(1.0f);

	this->currentTransform = newTransform;//default transform for now
	relTransform newTransf;
	newTransf.front = glm::vec3(0,0,-1);
	newTransf.up = glm::vec3(0,1,0);
	newTransf.right = glm::vec3(1,0,0);
	this->relativeTransf = newTransf;
	calculateRelTransform();

	//all set to new since its a new player being made (born if you will)
	this->meshChange = true;
	this->actionChange = true;
	this->animationChange = true;

	this->playerAnimator = new objAnimator(this->playerModel);
	this->playerAnimator->setSkeleton(this->playerModel->skeleton);

	loadPlayerAnimations(playerFilePath);

	this->activeAnim = "idle";
	this->playerAnimator->playAnimation(this->activeAnim);

	updateEntity();
}

//not all animations added yet and no error checking yet really
void playerEntity::loadPlayerAnimations(std::string playerFilePath)
{
	//idle //found
	std::string name = "idle";
	std::string Path = "resources/player/animations/idle.gltf"; //for some reason i have to do it this way

	this->playerAnimator->loadAnimation(name, Path, true);
	this->actionDebugger.push_back(idle);

	//idlePistol //found
	name = "idlePistol";
	Path = "resources/player/animations/pistolIdle.gltf";
	this->playerAnimator->loadAnimation(name, Path, true);
	this->actionDebugger.push_back(idlePistol);

	//idleRifle //found
	name = "idleRifle";
	Path = "resources/player/animations/rifleIdle.gltf";
	this->playerAnimator->loadAnimation(name, Path, true);
	this->actionDebugger.push_back(idleRifle);

	//aimingPistol
	name = "aimingPistol";
	Path = "resources/player/animations/pistolAim.gltf";
	this->playerAnimator->loadAnimation(name, Path, true);
	this->actionDebugger.push_back(aimingPistol);

	//aimingRifle
	//this->animations["aimingRifle"] = ResourceManager::loadAnimation("resources/player/animations/rifleAim.gltf", "playerAimRifle", "player");
	name = "aimingRifle";
	Path = "resources/player/animations/rifleAim.gltf";
	this->playerAnimator->loadAnimation(name, Path, true);
	this->actionDebugger.push_back(aimingRifle);

	//walking //found
	//this->animations["walking"] = ResourceManager::loadAnimation("resources/player/animations/walking.gltf", "playerWalking", "player");
	name = "walking";
	Path = "resources/player/animations/walking.gltf";
	this->playerAnimator->loadAnimation(name, Path, true);
	this->actionDebugger.push_back(walking);
	
	//sideWalkLeft
	//sideWalkRight
	//walkingBack
	
	//walkingPistolLowered
	
	//walkingPistolRaised //found
	//this->animations["walkPistolRaised"] = ResourceManager::loadAnimation("resources/player/animations/pistolWalkForward.gltf", "playerWalkPistolRaised", "player");
	name = "walkPistolRaised";
	Path = "resources/player/animations/pistolWalkForward.gltf";
	this->playerAnimator->loadAnimation(name, Path, true);
	this->actionDebugger.push_back(walkingPistolRaised);

	//walkingRifleLowered
	
	//walkingRifleRaise //found
	//this->animations["walkRifleRaised"] = ResourceManager::loadAnimation("resources/player/animations/rifleWalkForward.gltf", "playerWalkRifleRaised", "player");
	name = "walkRifleRaised";
	Path = "resources/player/animations/rifleWalkForward.gltf";
	this->playerAnimator->loadAnimation(name, Path, true);
	this->actionDebugger.push_back(walkingRifleRaised);
	//leftTurn
	//rightTurn

	//jogging //found
	//this->animations["jogging"] = ResourceManager::loadAnimation("resources/player/animations/jogging.gltf", "playerJogging", "player");
	name = "jogging";
	Path = "resources/player/animations/jogging.gltf";
	this->playerAnimator->loadAnimation(name, Path, true);
	this->actionDebugger.push_back(jogging);
	//sideJogLeft
	//sideJogRight
	
	//joggingPistolLowered
	//joggingRifleLowered

	//leftJoggingTurn
	//rightJoggingTurn

	//running //found
	//this->animations["running"] = ResourceManager::loadAnimation("resources/player/animations/running.gltf", "playerRunning", "player");
	name = "running";
	Path = "resources/player/animations/running.gltf";
	this->playerAnimator->loadAnimation(name, Path, true);
	this->actionDebugger.push_back(running);

	//leftRunninggTurn
	//rightRunningTurn

	//crouching
	//crouchingPistol
	//crouchingRifle //found
	//this->animations["crouchingRifle"] = ResourceManager::loadAnimation("resources/player/animations/rifleCrouchedAiming.gltf", "playerCrouchingRifle", "player");
	name = "crouchingRifle";
	Path = "resources/player/animations/rifleCrouchedAiming.gltf";
	this->playerAnimator->loadAnimation(name, Path, true);
	this->actionDebugger.push_back(crouchingRile);

	//crouchWalking
	 
	//crouchWalkingPistolLowered
	//crouchWalkingPistolRaised
	
	//crouchWalkingRifleLowered
	//crouchWalkingRifleRaise //found
	//this->animations["crouchWalkingRifle"] = ResourceManager::loadAnimation("resources/player/animations/rifleWalkForward.gltf", "playerCrouchWalkingRifle", "player");
	name = "crouchWalkingRifle";
	Path = "resources/player/animations/rifleWalkForward.gltf";
	this->playerAnimator->loadAnimation(name, Path, true);
	this->actionDebugger.push_back(crouchWalkingRifleRaise);

	//jumping //found
	//this->animations["jumping"] = ResourceManager::loadAnimation("resources/player/animations/jump.gltf", "playerJumping", "player");
	name = "jumping";
	Path = "resources/player/animations/jump.gltf";
	this->playerAnimator->loadAnimation(name, Path, false);
	this->actionDebugger.push_back(jumping);

	//diveRight
	//diveLeft
	//jumpBack
	//diveForward

	//climbingSmall
	//climingTall

	//falling

	//dying //found
	//this->animations["dying"] = ResourceManager::loadAnimation("resources/player/animations/dying.gltf", "playerDying", "player");
	name = "dying";
	Path = "resources/player/animations/dying.gltf";
	this->playerAnimator->loadAnimation(name, Path, false);
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
	if(this->currentAction != action)
	{
		this->currentAction = action;
		this->actionChange = true;
		updateEntity();
	}
}

//change player looks
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
		this->playerAnimator->playAnimation(this->activeAnim);
		animationChange = false;
	}

	this->playerModel->animationMatrices = this->playerAnimator->getAnimationTransforms();

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
		this->activeAnim = "idle";
		this->animationChange = true;
		break;

	case(idlePistol):
		this->activeAnim = "idlePistol";
		this->animationChange = true;
		break;

	case(idleRifle):
		this->activeAnim = "idleRifle";
		this->animationChange = true;
		break;

	case(aimingPistol):
		this->activeAnim = "aimingPistol";
		this->animationChange = true;
		break;

	case(aimingRifle):
		this->activeAnim = "aimingRifle";
		this->animationChange = true;
		break;

	case(walking):
		this->activeAnim = "walking";
		this->animationChange = true;
		
		//move forward as well by however much
		break;

	case(walkingPistolRaised):
		this->activeAnim = "walkPistolRaised";
		this->animationChange = true;
		//move forward as well by however much
		break;

	case(walkingRifleRaised):
		this->activeAnim = "walkRifleRaised";
		this->animationChange = true;
		//move forward as well by however much
		break;

	case(jogging):
		this->activeAnim = "jogging";
		this->animationChange = true;
		//move forward as well by however much
		break;

	case(running):
		this->activeAnim = "running";
		this->animationChange = true;
		//move forward as well by however much
		break;

	case(crouchWalkingRifleRaise):
		this->activeAnim = "crouchingRifle";
		this->animationChange = true;
		//move forward as well by however much
		break;

	case(jumping):
		this->activeAnim = "jumping";
		this->animationChange = true;
		//jump (duh), move up and down a lil bit
		break;

	case(dying):
		this->activeAnim = "dying";
		this->animationChange = true;
		//die, thats pretty much it
		break;


	}
}

void playerEntity::addPlayerToScene(scene* scene, Shader* shader)
{
	this->sceneID = scene->addObjectToScene(this->playerModel, this->currentTransform, shader);
}

void playerEntity::updatePlayerScene(scene* scene)
{
	scene->updateTransform(this->sceneID, this->currentTransform);
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

playerActions playerEntity::getPlayerAction()
{
	return this->currentAction;
}

void playerEntity::calculateRelTransform()
{
	glm::quat tempQuat = this->currentTransform.orientation;

	glm::vec3 front;
	//front.x = 2 * (tempQuat.x * tempQuat.z + tempQuat.w * tempQuat.y);
	//front.y = 2 * (tempQuat.y * tempQuat.z - tempQuat.w * tempQuat.x);
	//front.z = 1 - 2 * (tempQuat.x * tempQuat.x + tempQuat.y + tempQuat.y);

	front = tempQuat * glm::vec3(0, 0, 1);

	glm::vec3 right = glm::vec3(0,0,0);
	glm::vec3 up = glm::vec3(0,0,0);
	
	//std::cout << "player front: " << glm::to_string(front) << std::endl;

	this->relativeTransf.front = glm::normalize(front);

	//std::cout << "player fron normalized: " << glm::to_string(glm::normalize(front)) << std::endl;
	this->relativeTransf.up = up;
	this->relativeTransf.right = right;

	
}

glm::mat4 playerEntity::getLeftHandTransform()
{
	glm::mat4 handTransform(1.0f);

	//Bone* bone = &this->playerModel->boneMap["mixamorig:LeftHand"];
	//Bone* bone = &this->playerModel->boneMap["leftSocket"];
	
	handTransform = this->playerAnimator->getFinalBoneTransform("leftSocket");

	return handTransform;
}

glm::mat4 playerEntity::getRightHandTransform()
{
	glm::mat4 handTransform(1.0f);

	//std::string boneName = "mixamorig:RightHand";
	//std::string boneName = "rightSocket";
	
	//handTransform = this->playerAnimator->getFinalBoneTransform("mixamorig:RightHand");
	handTransform = this->playerAnimator->getFinalBoneTransform("rightSocket");

	return handTransform;
}

glm::mat4 playerEntity::getRightHandOffsetMatrix()
{
	glm::mat4 handOffset(1.0f);

	//handOffset = this->playerModel->boneMap["mixamorig:RightHand"].offsetMatrix;
	//handOffset = this->playerModel->boneMap["rightSocket"].offsetMatrix;

	std::string boneName = "rightSocket";
	handOffset = playerModel->skeleton->getBone(boneName)->getOffsetMat();

	return handOffset;
}

glm::mat4 playerEntity::getLeftHandOffsetMatrix()
{
	glm::mat4 handOffset(1.0f);

	//handOffset = this->playerModel->boneMap["mixamorig:LeftHand"].offsetMatrix;
	//handOffset = this->playerModel->boneMap["leftSocket"].offsetMatrix;

	std::string boneName = "leftSocket";
	handOffset = playerModel->skeleton->getBone(boneName)->getOffsetMat();

	return handOffset;
}

objAnimator* playerEntity::getPlayerAnimator()
{
	return this->playerAnimator;
}
