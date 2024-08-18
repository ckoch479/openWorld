#include "characterController.h"

characterController::characterController(playerEntity* newPlayer, PhysicsWorld* newWorld, Camera* newCamera)
{
	this->player = newPlayer;
	this->world = newWorld;
	this->playerCamera = newCamera;
	addPlayerToWorld();
}


characterController::~characterController()
{

}

void characterController::updateInputs(windowManager* manager)
{
	this->player->resetDirectionalActionMods();
	//if player is in the third person camera view (free cam is for debugging)
	if(this->playerCamera->isThirdPerson())
	{
		//check for walking, jogging or sprinting and set that action
		if(manager->checkKey(this->forwardMov)) //W
		{
			this->player->setActionModifier(forward, true);
			if(manager->checkKey(this->sprint)) //if shift is being pressed
			{
				this->player->setPlayerAction(sprinting);
			}
			//if walking toggle is true
			else if(this->walkT)
			{
				this->player->setPlayerAction(walking);
			}
			else //if player isnt walking or sprinting the gotta be jogging
			{
				this->player->setPlayerAction(jogging);
			}
		}
		
		if (manager->checkKey(back)) //s
		{
			this->player->setActionModifier(backward, true);

			if (this->walkT)
			{
				this->player->setPlayerAction(walking);
			}
			else //if player isnt walking or sprinting the gotta be jogging
			{
				this->player->setPlayerAction(jogging);
			}
		};

		if(manager->checkKey(left)) //a
		{
			this->player->setActionModifier(leftWards, true);

			if (this->walkT)
			{
				this->player->setPlayerAction(walking);
			}
			else //if player isnt walking or sprinting the gotta be jogging
			{
				this->player->setPlayerAction(jogging);
			}
		}

		if(manager->checkKey(right)) //d
		{
			this->player->setActionModifier(rightWards, true);

			if (this->walkT)
			{
				this->player->setPlayerAction(walking);
			}
			else //if player isnt walking or sprinting the gotta be jogging
			{
				this->player->setPlayerAction(jogging);
			}
		}

		//check for action modifiers (crawling, crouching, aiming, shooting)
		if(manager->checkKey(togWalk)) //check for walking toggle button is pressed (capsLock)
		{
			if(walkT == false)
			{
				this->walkT = true;
			}
			else
			{
				this->walkT = false;
			}
			this->player->setActionModifier(walkToggle, this->walkT);
		}

		if(manager->checkKey(crouchT))
		{
			if(crouchToggle == false)
			{
				crouchToggle = true;
			}
			else
			{
				crouchToggle = false;
			}
			this->player->setActionModifier(crouch, this->crouchToggle);
			//std::cout << "crouch toggle is: " << this->crouchToggle << std::endl;
		}

		/*if (manager->checkKey(69)) //E
		{
			this->player->setActionModifier(aim, true);
		}
		if (manager->checkKey(81)) Q
		{
			this->player->setActionModifier(aim, false);
		}*/

		if(manager->rightClick()) //found the issue with aiming, animation modifiers do not update animations
		{
				this->aiming = true;
				this->player->setActionModifier(aim, true);
				this->playerCamera->Zoom = 25.0f;
		}
		if(!manager->rightClick())
		{
				this->aiming = false;
				this->player->setActionModifier(aim, false);
				this->playerCamera->Zoom = 45.0f;
		}
		if (manager->checkKey(32)) //space
		{
			this->player->setPlayerAction(jumping);
		}

		

	}

	//idle was the issue because it checked only if w wasnt pressed and really should only work when nothing has been pressed
	if (!manager->checkKey(87) && !manager->checkKey(69) && !manager->checkKey(65) && !manager->checkKey(83) && !manager->checkKey(68) && !manager->checkKey(32) && !manager->checkKey(81) && !manager->rightClick() && !manager->leftClick()) //w
	{
		this->player->setPlayerAction(idle);
	}

	//camera control
	if (manager->checkKey(49))//1 key
	{
		playerCamera->setCameraFreeCam();
	}
	if (manager->checkKey(50))//2 key
	{
		playerCamera->setCameraThirdPerson(2.6);
	}

	if (!playerCamera->isThirdPerson())
	{
		if (manager->checkKey(65)) //a
		{
			this->cameraLeft = true;
		}

		if (manager->checkKey(83)) //s
		{
				this->cameraBackWard = true;
		};

		if (manager->checkKey(68)) //d
		{
			this->cameraRight = true;
		};

		if (manager->checkKey(87)) //w
		{
				this->cameraForward = true;
		};
	}

	//third person camera controls---------------------------------------------------------
	//mouse position;
	float lastx = cursorX;
	float lasty = cursorY;

	manager->getMousePosition(&cursorX, &cursorY);

	float xOffset = cursorX - lastx;
	float yOffset = lasty - cursorY;
	playerCamera->ProcessMouseMovement(xOffset, yOffset, true, glm::vec3(0, 1.5, 0) + this->player->getPlayersTransform()->position , 0);

	if (playerCamera->isThirdPerson())
	{
		transform* newTransform = this->player->getPlayersTransform();
		newTransform->orientation = glm::rotate(glm::toMat4(newTransform->orientation), xOffset * 0.01f, glm::vec3(0, 1, 0));
		this->player->setPlayerTransform(*newTransform);

		if (this->aiming == true)
		{
			this->pitch += yOffset * -0.001f; //not a good solution but sorta works need to tie it into the camera instead
			if (this->pitch > 1.0f)
			{
				this->pitch = 1.0f;
			}
			if (this->pitch < 0.0f)
			{
				this->pitch = 0.0f;
			}
			
			this->player->aimUpDownBlend = this->pitch;// *0.1;
			this->player->aimingUp = true;
		
		
		}
	}

	

}


void characterController::addPlayerToWorld()
{
	this->playerMainColliderID = this->world->createOBB(glm::vec3(0.6, 1.7, 0.6));
	this->world->updateOBBtransform(this->player->getPlayersTransform()->position, this->player->getPlayersTransform()->orientation, this->playerMainColliderID);
	std::vector <Bone*> playerBones = this->player->getBones();
	//create obb of based on the players bones below
	for(int i = 0; i < playerBones.size(); i++)
	{
		Bone* currentBone = playerBones[i];
		std::string boneName = currentBone->getName();
		
		//std::cout << "bone name: " << boneName << std::endl;

		if (boneName == "mixamorig:LeftHandThumb1"  || boneName == "mixamorig:LeftHandThumb2" || boneName == "mixamorig:LeftHandThumb3" || boneName == "mixamorig:LeftHandThumb4")
		{
			continue;
		}
		if (boneName == "mixamorig:LeftHandIndex1" || boneName == "mixamorig:LeftHandIndex2" || boneName == "mixamorig:LeftHandIndex3" || boneName == "mixamorig:LeftHandIndex4")
		{
			continue;
		}
		if (boneName == "mixamorig:LeftHandMiddle1" || boneName == "mixamorig:LeftHandMiddle2" || boneName == "mixamorig:LeftHandMiddle3" || boneName == "mixamorig:LeftHandMiddle4")
		{
			continue;
		}
		if (boneName == "mixamorig:LeftHandRing1" || boneName == "mixamorig:LeftHandRing2" || boneName == "mixamorig:LeftHandRing3" || boneName == "mixamorig:LeftHandRing4")
		{
			continue;
		}
		if (boneName == "mixamorig:LeftHandPinky1" || boneName == "mixamorig:LeftHandPinky2" || boneName == "mixamorig:LeftHandPinky3" || boneName == "mixamorig:LeftHandPinky4")
		{
			continue;
		}
		
		if (boneName == "mixamorig:RightHandThumb1" || boneName == "mixamorig:RightHandThumb2" || boneName == "mixamorig:RightHandThumb3"    || boneName == "mixamorig:RightHandThumb4")
		{
			continue;
		}
		if (boneName == "mixamorig:RightHandIndex1" || boneName == "mixamorig:RightHandIndex2" || boneName == "mixamorig:RightHandIndex3"    || boneName == "mixamorig:RightHandIndex4")
		{
			continue;
		}
		if (boneName == "mixamorig:RightHandMiddle1" || boneName == "mixamorig:RightHandMiddle2" || boneName == "mixamorig:RightHandMiddle3" || boneName == "mixamorig:RightHandMiddle4")
		{
			continue;
		}
		if (boneName == "mixamorig:RightHandRing1" || boneName == "mixamorig:RightHandRing2" || boneName == "mixamorig:RightHandRing3"		 || boneName == "mixamorig:RightHandRing4")
		{
			continue;
		}
		if (boneName == "mixamorig:RightHandPinky1" || boneName == "mixamorig:RightHandPinky2"  || boneName == "mixamorig:RightHandPinky3"   || boneName == "mixamorig:RightHandPinky4")
		{
			continue;
		}

		if (boneName == "rightSocket" || boneName == "leftSocket" || boneName == "mixamorig:LeftToe_End" || boneName == "mixamorig:RightToe_End")
		{
			continue;
		}
		if (boneName == "mixamorig:RightArm" || boneName == "mixamorig:RightForeArm" || boneName == "mixamorig:LeftArm" || boneName == "mixamorig:LeftForeArm")
		{
			unsigned int OBBID = this->world->createOBB(glm::vec3(0.1, 0.3, 0.1));
			this->OBBids.push_back(OBBID);
			this->boneOBBidMap[OBBID] = currentBone->getId();
			continue;
		}
	
		if (boneName == "mixamorig:Hips" || boneName == "mixamorig:Spine" || boneName == "mixamorig:Spine1" || boneName == "mixamorig:Spine2")
		{
			unsigned int OBBID = this->world->createOBB(glm::vec3(0.3, 0.4, 0.1));
			this->OBBids.push_back(OBBID);
			this->boneOBBidMap[OBBID] = currentBone->getId();
			continue;
		}

		if (boneName == "mixamorig:RightHand" || boneName == "mixamorig:LeftHand" || boneName == "mixamorig:HeadTop_End")
		{
			unsigned int OBBID = this->world->createOBB(glm::vec3(0.1, 0.1, 0.1));
			this->OBBids.push_back(OBBID);
			this->boneOBBidMap[OBBID] = currentBone->getId();
			continue;
		}

		if (boneName == "mixamorig:LeftUpLeg" || boneName == "mixamorig:LeftLeg" || boneName == "mixamorig:RightUpLeg" || boneName == "mixamorig:RightLeg")
		{
			unsigned int OBBID = this->world->createOBB(glm::vec3(0.15, 0.35, 0.15));
			this->OBBids.push_back(OBBID);
			this->boneOBBidMap[OBBID] = currentBone->getId();
			continue;
		}

		unsigned int OBBID = this->world->createOBB(glm::vec3(0.2,0.2,0.2));
		this->OBBids.push_back(OBBID);
		this->boneOBBidMap[OBBID] = currentBone->getId();
	}
}

void characterController::updateOBBs()
{
	//update large player collider
	this->world->updateOBBtransform(this->player->getPlayersTransform()->position + glm::vec3(0,0.85,0), this->player->getPlayersTransform()->orientation, this->playerMainColliderID);

	objAnimator* playerAnimator = this->player->getPlayerAnimator();

	transform playerTransform = *this->player->getPlayersTransform();
	glm::mat4 playerMat(1.0f); //create player model matrix (model space to world space)
	playerMat = glm::translate(playerMat, playerTransform.position);
	playerMat = playerMat * glm::toMat4(playerTransform.orientation);
	playerMat = glm::scale(playerMat, playerTransform.scale);
	
	for(int i = 0; i < this->OBBids.size(); i++)
	{
		int boneId = this->boneOBBidMap[OBBids[i]];
		Bone* currentBone = this->player->getPlayerModel()->skeleton->getBone(boneId);
		
		glm::mat4 boneTransform(1.0f);
		boneTransform = playerAnimator->getFinalBoneTransform(currentBone->getName());
		boneTransform = boneTransform * glm::inverse(currentBone->getOffsetMat());

		glm::mat4 handMat(1.0f);
		handMat = playerMat * boneTransform; 
		
		glm::vec3 skew;
		glm::vec4 perspective;
		glm::vec3 position;
		glm::quat orientation;
		glm::vec3 scale;
		glm::decompose(handMat, scale, orientation, position, skew, perspective); //decompose mat4

		this->world->updateOBBtransform(position, orientation, OBBids[i]);
	}
}


void characterController::updateController(float dt, Level currentLevel)
{
	bool groundContact = false;
	//calculate new postions/orientations
	transform* playerTransform = player->getPlayersTransform();
	glm::vec3 newPosition = playerTransform->position;
	//glm::vec3 physWorldPos = playerTransform->position;

	//checking for ground collision and applying gravity (uses heightmap generated by level.h)
	float height = currentLevel.getHeightAtPosition(playerTransform->position);
	if (playerTransform->position.y > height)
	{
		playerTransform->position.y = newPosition.y - (60 * 9.8) * dt;
		//playerVelocity.y += -((playerMass * 9.8) * dt);
	}

	if (playerTransform->position.y <= height)
	{
		playerTransform->position.y = height;
		playerVelocity.y = 0.0f;
		groundContact = true;
	}

	//change velocity if walking
	if (this->player->getPlayerAction() == walking)
	{
		if (this->player->getActionModifier(forward)) //if player is walking and pressing forward
		{
			glm::vec3 relativeFront = player->getPlayerRelativeTransform()->front;
			playerTransform->position = glm::vec3(newPosition.x, playerTransform->position.y, newPosition.z) + glm::vec3(relativeFront.x, 0, relativeFront.z) * (float)3.0 * dt;
		}; 

		if (this->player->getActionModifier(backward))
		{
			glm::vec3 relativeFront = player->getPlayerRelativeTransform()->front;
			playerTransform->position = glm::vec3(newPosition.x, playerTransform->position.y, newPosition.z) + glm::vec3(relativeFront.x, 0, relativeFront.z) * (float)-3.0 * dt;
		};

		if (this->player->getActionModifier(rightWards))
		{
			glm::vec3 relativeRight = player->getPlayerRelativeTransform()->right;
			playerTransform->position = glm::vec3(newPosition.x, playerTransform->position.y, newPosition.z) + glm::vec3(relativeRight.x, 0, relativeRight.z) * (float)-3.0 * dt;
		};

		if (this->player->getActionModifier(leftWards))
		{
			glm::vec3 relativeRight = player->getPlayerRelativeTransform()->right;
			playerTransform->position = glm::vec3(newPosition.x, playerTransform->position.y, newPosition.z) + glm::vec3(relativeRight.x, 0, relativeRight.z) * (float)3.0 * dt;
		};
	}

	if(this->player->getPlayerAction() == jogging)
	{
		if (this->player->getActionModifier(forward)) //if player is walking and pressing forward
		{
			glm::vec3 relativeFront = player->getPlayerRelativeTransform()->front;
			playerTransform->position = glm::vec3(newPosition.x, playerTransform->position.y, newPosition.z) + glm::vec3(relativeFront.x, 0, relativeFront.z) * (float)4.0 * 1.5f * dt;
		};

		if (this->player->getActionModifier(backward))
		{
			glm::vec3 relativeFront = player->getPlayerRelativeTransform()->front;
			playerTransform->position = glm::vec3(newPosition.x, playerTransform->position.y, newPosition.z) + glm::vec3(relativeFront.x, 0, relativeFront.z) * (float)-4.0 * 1.5f * dt;
		};

		if (this->player->getActionModifier(rightWards))
		{
			glm::vec3 relativeRight = player->getPlayerRelativeTransform()->right;
			playerTransform->position = glm::vec3(newPosition.x, playerTransform->position.y, newPosition.z) + glm::vec3(relativeRight.x, 0, relativeRight.z) * (float)-4.0 * 1.5f * dt;
		};

		if (this->player->getActionModifier(leftWards))
		{
			glm::vec3 relativeRight = player->getPlayerRelativeTransform()->right;
			playerTransform->position = glm::vec3(newPosition.x, playerTransform->position.y, newPosition.z) + glm::vec3(relativeRight.x, 0, relativeRight.z) * (float)4.0 * 1.5f * dt;
		};
	}

	if(this->player->getPlayerAction() == sprinting)
	{
		glm::vec3 relativeFront = player->getPlayerRelativeTransform()->front;
		playerTransform->position = glm::vec3(newPosition.x, playerTransform->position.y, newPosition.z) + glm::vec3(relativeFront.x, 0, relativeFront.z) * (float)5.0 * 1.5f * dt;
	}
	
	if (this->player->getPlayerAction() == jumping) //not working quite yet
	{
		if (groundContact)
		{
			
		}
	} 

	//update transforms
	this->player->setPlayerTransform(*playerTransform);
	player->calculateRelTransform();

	//camera controll (free cam)
	if(cameraForward)
	{
		this->playerCamera->ProcessKeyboard(FORWARD, dt);
		cameraForward = false;
	}

	if (cameraLeft) 
	{
		this->playerCamera->ProcessKeyboard(LEFT, dt);
		cameraLeft = false;
	}

	if (cameraRight)
	{
		this->playerCamera->ProcessKeyboard(RIGHT, dt);
		cameraRight = false;
	}

	if(cameraBackWard)
	{
		this->playerCamera->ProcessKeyboard(BACKWARD, dt);
		cameraBackWard = false;
	}

	updateOBBs();
	
}