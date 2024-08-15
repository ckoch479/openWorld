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
	}

}


void characterController::addPlayerToWorld()
{
	this->physicsId = this->world->createCapsuleShape(this->player->getPlayersTransform()->position, glm::quat(1.0, 0.0, 0.0, 0.0f), 50, 0.7, 1.3, Kinematic);
	this->world->changeColliderOrigin(this->physicsId, glm::vec3(0.0, 1.5, 0.0));
	this->world->lockBodyRotationAxis(this->physicsId, glm::vec3(1, 1, 1));

	/*std::vector <Bone*> playerSkeleton = this->player->getBones();
	for(int i = 0 ; i < playerSkeleton.size(); i++)
	{
		unsigned int obbID = this->world->createOBB(glm::vec3(0.0f), glm::quat(1.0, 0.0, 0.0, 0.0), glm::vec3(0.2, 0.2, 0.2));
		this->OBBids.push_back(obbID);
		this->boneOBBidMap[obbID] = playerSkeleton[i]->getId();
	}*/

}

void characterController::updateOBBs()
{
	//for(unsigned int i = 0; i < this->OBBids.size(); i++)
	//{
		//orientedBoundingBox* currentBox = &this->world->getBoundingBox(OBBids[i]);
		//int boneId = boneOBBidMap[OBBids[i]];
		//Bone* currentBone = this->player->getPlayerModel()->skeleton->getBone(boneId);
		
		//std::string boneName;
		//glm::mat4 boneTransform = this->player->getPlayerAnimator()->getFinalBoneTransform(currentBone->getName());

		//need to get the player transform then the players bone transform for this bone
	//}

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
	this->world->setBodyPosition(this->physicsId, playerTransform->position);
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
	
}