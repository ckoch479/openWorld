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
	if (manager->checkKey(87)) //w
	{
		if (playerCamera->isThirdPerson())
		{
			if (manager->checkKey(340))//left shift
			{
				this->player->setPlayerAction(jogging);
			}
			else
			{
				this->player->setPlayerAction(walking);
			}
		}
		
		if (!playerCamera->isThirdPerson()) 
		{
			this->cameraForward = true;
		}

	};

	if(manager->checkKey(69)) //e
	{
		if (playerCamera->isThirdPerson())
		{
			this->player->setPlayerAction(dying);
		}
	}

	if (manager->checkKey(81)) //q
	{
		this->player->setPlayerAction(idlePistol);
	}

	//idle was the issue because it checked only if w wasnt pressed and really should only work when nothing has been pressed
	if (!manager->checkKey(87) && !manager->checkKey(69) && !manager->checkKey(65) && !manager->checkKey(83) && !manager->checkKey(68) && !manager->checkKey(32) && !manager->checkKey(81) && !manager->rightClick() && !manager->leftClick()) //w
	{
		this->player->setPlayerAction(idle);
	}

	if (manager->checkKey(65)) //a
	{
		if (playerCamera->isThirdPerson())
		{
			this->player->setPlayerAction(sideWalkLeft);
		}

		if (!playerCamera->isThirdPerson())
		{
			this->cameraLeft = true;
		}
	};

	if (manager->checkKey(83)) //s
	{
		if (playerCamera->isThirdPerson())
		{
			this->player->setPlayerAction(walkingBack);
		}

		if (!playerCamera->isThirdPerson())
		{
			this->cameraBackWard = true;
		}
	};

	if (manager->checkKey(68)) //d
	{
		if (playerCamera->isThirdPerson())
		{
			this->player->setPlayerAction(sideWalkRight);
		}

		if (!playerCamera->isThirdPerson())
		{
			this->cameraRight = true;
		}
	};

	if (manager->checkKey(32)) //space
	{
		if (playerCamera->isThirdPerson())
		{
			this->player->setPlayerAction(jumping);
		}
	}

	if(manager->leftClick())
	{
		this->player->setPlayerAction(aimingRifle);
	}

	if(manager->rightClick())
	{
		this->player->setPlayerAction(aimingPistol);
		this->playerCamera->Zoom = 25.0f;
	}
	if(!manager->rightClick())
	{
		this->playerCamera->Zoom = 45.0f;
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
	this->physicsId = this->world->createCapsuleShape(this->player->getPlayersTransform()->position, glm::quat(1.0, 0.0, 0.0, 0.0f), 50, 0.7, 1.5, Kinematic);
	this->world->changeColliderOrigin(this->physicsId, glm::vec3(0.0, 1.5, 0.0));
	this->world->lockBodyRotationAxis(this->physicsId, glm::vec3(1, 1, 1));
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
	if(this->player->getPlayerAction() == walking)
	{
		glm::vec3 relativeFront = player->getPlayerRelativeTransform()->front;
		playerTransform->position = glm::vec3(newPosition.x, playerTransform->position.y, newPosition.z) + glm::vec3(relativeFront.x,0, relativeFront.z) * (float)4.0 * dt;
	}
	if(this->player->getPlayerAction() == jogging)
	{
		glm::vec3 relativeFront = player->getPlayerRelativeTransform()->front;
		playerTransform->position = glm::vec3(newPosition.x, playerTransform->position.y, newPosition.z) + glm::vec3(relativeFront.x, 0, relativeFront.z) * (float)4.0 * 2.0f * dt;
	}
	
	if (this->player->getPlayerAction() == jumping) //not working quite yet
	{
		if (groundContact)
		{
			
		}
	} 
	

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