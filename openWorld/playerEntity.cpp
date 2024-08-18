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
	//unarmed:
	std::string name = "idle"; 
	std::string Path = "resources/player/animations/idle.gltf"; //for some reason i have to do it this way
	this->playerAnimator->loadAnimation(name, Path, true);

	name = "walking";
	Path = "resources/player/animations/walking.gltf";
	this->playerAnimator->loadAnimation(name, Path, true);

	name = "jogging";
	Path = "resources/player/animations/jogging.gltf";
	this->playerAnimator->loadAnimation(name, Path, true);

	name = "running";
	Path = "resources/player/animations/running.gltf";
	this->playerAnimator->loadAnimation(name, Path, true);

	name = "jumping";
	Path = "resources/player/animations/jump.gltf";
	this->playerAnimator->loadAnimation(name, Path, false);

	name = "dying";
	Path = "resources/player/animations/dying.gltf";
	this->playerAnimator->loadAnimation(name, Path, false);





	//oneHanded weapon:
	name = "idlePistol";
	Path = "resources/player/animations/pistolIdle.gltf";
	this->playerAnimator->loadAnimation(name, Path, true);

	//aiming blend tests

	name = "aimingPistol";
	Path = "resources/player/animations/aimingMod/oneHandedIdleAiming.gltf";
	this->playerAnimator->loadAnimation(name, Path, true);

	name = "aimingPistolDown";
	Path = "resources/player/animations/aimingMod/oneHandedIdleAimingDown.gltf";
	this->playerAnimator->loadAnimation(name, Path, true);

	name = "aimingPistolUp";
	Path = "resources/player/animations/aimingMod/oneHandedIdleAimingUp.gltf";
	this->playerAnimator->loadAnimation(name, Path, true);

	//---------------------------------------------------------------------------------------------

	/*name = "aimingPistol";
	Path = "resources/player/animations/pistolAim.gltf";
	this->playerAnimator->loadAnimation(name, Path, true);*/

	name = "walkPistolRaised";
	Path = "resources/player/animations/pistolWalkForward.gltf";
	this->playerAnimator->loadAnimation(name, Path, true);

	name = "pistolIdleCrouchedAiming";
	Path = "resources/player/animations/pistolCrouchedAimingIdle.gltf";
	this->playerAnimator->loadAnimation(name, Path, true);

	name = "pistolIdleCrouched";
	Path = "resources/player/animations/oneHandedIdleCrouch.gltf";
	this->playerAnimator->loadAnimation(name, Path, true);

	name = "pistolWalk";
	Path = "resources/player/animations/pistolWalkLowered.gltf";
	this->playerAnimator->loadAnimation(name, Path, true);

	name = "pistolJog";
	Path = "resources/player/animations/pistolJogLowered.gltf";
	this->playerAnimator->loadAnimation(name, Path, true);




	//Two handed Weapon:
	name = "idleRifle"; 
	Path = "resources/player/animations/rifleIdle.gltf";
	this->playerAnimator->loadAnimation(name, Path, true);

	name = "aimingRifle";
	Path = "resources/player/animations/rifleAim.gltf";
	this->playerAnimator->loadAnimation(name, Path, true);

	name = "walkRifleRaised";
	Path = "resources/player/animations/rifleWalkForward.gltf";
	this->playerAnimator->loadAnimation(name, Path, true);

	name = "crouchingRifleAim";
	Path = "resources/player/animations/rifleCrouchedAiming.gltf";
	this->playerAnimator->loadAnimation(name, Path, true);

	name = "rifleCrouchIdle";
	Path = "resources/player/animations/rifleCrouchedIdle.gltf";
	this->playerAnimator->loadAnimation(name, Path, true);

	name = "rifleCrouchedWalk";
	Path = "resources/player/animations/rifleCrouchedWalk.gltf";
	this->playerAnimator->loadAnimation(name, Path, true);

	name = "rifleCrouchWalkAiming";
	Path = "resources/player/animations/rifleCrouchWalkAiming.gltf";
	this->playerAnimator->loadAnimation(name, Path, true);

	name = "rifleWalk";
	Path = "resources/player/animations/rifleWalkLowered2.gltf";
	this->playerAnimator->loadAnimation(name, Path, true);

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
	if(this->currentAction == idle) //all idle animations
	{
		setIdleAnimation();
	}

	if (this->currentAction == walking) //all walking animations
	{
		setWalkingAnimation();
	}
	if(this->currentAction == jogging) //all jogging animations
	{
		setJoggingAnimation();
	}
	if(this->currentAction == turning) //turning animations
	{
		setTurningAnimation();
	}
	if(this->currentAction == sprinting) //sprinting animations
	{
		setSprintingAnimation();
	}
	if(this->currentAction == jumping)
	{
		setJumpingAnimation();
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

	glm::vec3 right = tempQuat * glm::vec3(1,0,0);
	glm::vec3 up = tempQuat * glm::vec3(0,1,0);
	
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

void playerEntity::setActionModifier(actionModifiers mod, bool setter)
{
	this->animationChange = true;
	updateActions();
	switch(mod)
	{
	case(walkToggle):
		this->walkToggled = setter;
		break;

	case(sprintToggle):
		this->sprintToggled = setter;
		break;

	case(crouch):
		this->crouching = setter;
		break;

	case(crawl):
		this->crawling = setter;
		break;

	case(aim):
		this->aiming = setter;
		//std::cout << "aiming being set to: " << setter << std::endl;
		break;

	case(shoot):
		this->shooting = setter;
		break;

	case(leftWards):
		this->leftward = setter;
		break;

	case(rightWards):
		this->rightward = setter;
		break;

	case(forward):
		this->front = setter;
		break;

	case(backward):
		this->back = setter;
		break;

	case(oneHandEquiped):
		this->oneHanded = setter;
		break;

	case(twoHandEquiped):
		this->twoHanded = setter;
		break;

	}
	
}

bool playerEntity::getActionModifier(actionModifiers mod)
{
	bool modif = false; //default to false in case there are any errors
	switch (mod)
	{
	case(walkToggle):
		modif = this->walkToggled;
		break;

	case(sprintToggle):
		modif = this->sprintToggled;
		break;

	case(crouch):
		modif = this->crouching;
		break;

	case(crawl):
		modif = this->crawling;
		break;

	case(aim):
		modif = this->aiming;
		break;

	case(shoot):
		modif = this->shooting;
		break;

	case(leftWards):
		modif = this->leftward;
		break;

	case(rightWards):
		modif = this->rightward;
		break;

	case(forward):
		modif = this->front;
		break;

	case(backward):
		modif = this->back;
		break;

	case(oneHandEquiped):
		modif = this->oneHanded;
		break;

	case(twoHandEquiped):
		modif = this->twoHanded;
		break;

	}
	return modif;
}

void playerEntity::resetDirectionalActionMods()
{
	this->leftward = false;
	this->rightward = false;
	this->front = false;
	this->back = false;
}

void playerEntity::setIdleAnimation()
{
	if(crouching) //crouching idle animation
	{
		if (oneHanded) //if one handed item is equiped
		{
			if (aiming)
			{
				if (shooting)
				{

				}
				else
				{
					//oneHanded crouch aiming
					this->activeAnim = "pistolIdleCrouchedAiming";
					this->animationChange = true;
				}
			}
			else
			{
				this->activeAnim = "pistolIdleCrouched";
				this->animationChange = true;
			}
		}
		else if (twoHanded) //if two handed item is equiped
		{
			if (aiming)
			{
				if (shooting)
				{

				}
				else
				{
					//crouching aiming two handed
					this->activeAnim = "crouchingRifleAim";
					this->animationChange = true;
				}
			}
			else
			{
				this->activeAnim = "rifleCrouchIdle";
				this->animationChange = true;
			}
		}

		else //unarmed
		{
			//crouched idle unarmed (need to get asset)
		}
	}
	//no crawling animations are currently loaded
	else if(crawling) //crawling idle animation
	{
		if (oneHanded) //if one handed item is equiped
		{
			if (aiming)
			{
				if (shooting)
				{

				}
				else
				{
					
				}
			}
			else
			{

			}
		}
		else if (twoHanded) //if two handed item is equiped
		{
			if (aiming)
			{
				if (shooting)
				{

				}
				else
				{

				}
			}
			else
			{

			}
		}
		else //unarmed
		{

		}
	}

	else //normal idle animation
	{
		
		if (oneHanded) //if one handed item is equiped
		{
			if (aiming)
			{
				if (shooting)
				{
					//one handed shooting animation
				}
				else
				{
					if(this->aimingUp == true)
					{
						this->playerAnimator->playBlendAnimation("aimingPistol", "aimingPistolUp", this->aimUpDownBlend);
						//std::cout << "aiming pistol up!\n";
						//std::cout << "blend factor: " << this->aimUpDownBlend << std::endl;
					}
					if (this->aimingDown == true)
					{
						this->playerAnimator->playBlendAnimation("aimingPistol", "aimingPistolDown", this->aimUpDownBlend);
					}
					else
					{
						this->activeAnim = "aimingPistol";
						this->animationChange = true;
					}
					//one handed aiming animation
					
					
					//std::cout << "aiming pistol!\n";
				}
			}
			else
			{
			//one handed weapon lowered animation
				this->activeAnim = "idlePistol";
				this->animationChange = true;
			}
		}
		else if (twoHanded) //if two handed item is equiped
		{
			if (aiming)
			{
				if(shooting)
				{
					//two handed shooting animation
				}
				else
				{
					//two handed aiming animation
					this->activeAnim = "aimingRifle";
					this->animationChange = true;
				}
			}
			else
			{
			//two handed weapon lowered animation
				this->activeAnim = "idleRifle";
				this->animationChange = true;
			}
		}
		else //unarmed idle animation
		{
			this->activeAnim = "idle";
			this->animationChange = true;
		}
	}
	
}

void playerEntity::setWalkingAnimation()
{
	//if w is pressed
	if (this->front)
	{
		
			if (this->crouching) //if crouching we branch off here
			{	
				//one handed weapon
				if(this->oneHanded)
				{
					if(aiming)
					{
						if(shooting)
						{
							//one handed crouch walking shoot animation (need asset)
						}
						else
						{
							//one handed crouch walking aim animation (need asset)

						}
					}
					//if weapon is not raised
					else
					{
						
					}
				}
				//two handed weapon
				else if(this->twoHanded)
				{
					if(aiming)
					{
						if (shooting)
						{
							//two handed crouch, walking shoot animation
						}
						else
						{
							//two handed crouch walking aim animation
							this->activeAnim = "rifleCrouchWalkAiming";
							this->animationChange = true;
						}
					}
					//if weapon is not raised
					else
					{
						this->activeAnim = "rifleCrouchedWalk";
						this->animationChange = true;
					}
				}
				//unarmed
				else
				{
				//crouch walking unarmed (need asset)
				}
				
			}

			else if (this->crawling) //crawling branches off here, crawling is a modifier to walking and not it's own action, you cannot move and aim while crawling
			{
				if(this->oneHanded)
				{
				//one handed crawling animation
				}
				else if(this->twoHanded)
				{
				//two handed crawling animation
				}
				else
				{
				//unarmed crawling animation
				}
			}

			else //regular walking
			{
				if (oneHanded)
				{
					if (aiming)
					{
						if (shooting)
						{
							//shoot one handed animation
						}
						else
						{
							//aim one handed animation
							this->activeAnim = "walkPistolRaised";
							this->animationChange = true;
						}
					}
					else
					{
						//one handed walking animation
						this->activeAnim = "pistolWalk"; //not working
						this->animationChange = true;
						//std::cout << "pistol walk should happen here!\n";
					}
				}
				else if (twoHanded)
				{
					if (aiming)
					{
						if (shooting)
						{
							//two handed shooting animation
						}
						else
						{
							//aim two handed walking animation
							this->activeAnim = "walkRifleRaised";
							this->animationChange = true;
						}
					}
					else
					{
						//two handed walk animation
						this->activeAnim = "rifleWalk";
						this->animationChange = true;
					}
				}
				else
				{
					this->activeAnim = "walking";
					this->animationChange = true;
				}
			}

	}
	//if a is pressed
	if (this->leftward)
	{

	}
	//if d is pressed
	if (this->rightward)
	{

	}
	//if s is pressed
	if (this->back)
	{

	}
}

void playerEntity::setJoggingAnimation()
{
	if(crouching)
	{
		if (oneHanded)
		{

		}
		else if (twoHanded)
		{

		}
		//unarmed
		else
		{
			
		}
	}
	else //standard jogging
	{
		if (oneHanded)
		{
			this->activeAnim = "pistolJog";
			this->animationChange = true;
		}
		else if (twoHanded)
		{

		}
		//unarmed
		else
		{
			this->activeAnim = "jogging";
			this->animationChange = true;
		}
	}
	
}

void playerEntity::setTurningAnimation()
{
	// to do
}

void playerEntity::setSprintingAnimation()
{
	this->activeAnim = "running";
	this->animationChange = true;
}

void playerEntity::setJumpingAnimation()
{
	this->activeAnim = "jumping";
	this->animationChange = true;
}

std::vector <Bone*> playerEntity::getBones()
{
	int numBones = this->playerModel->skeleton->getBoneCount();
	std::vector <Bone*> playerBones;
	for(int i = 0; i < numBones; i++)
	{
		playerBones.push_back(this->playerModel->skeleton->getBone(i));
	}
	return playerBones;
}