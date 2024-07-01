#include "characterController.h"

characterController::characterController(playerEntity* newPlayer, scene* newScene, PhysicsWorld* newWorld, Shader* shader)
{
	this->player = newPlayer;
	this->sceneObj = newScene;
	this->world = newWorld;
	addPlayerToScene(shader);
	addPlayerToWorld();
}

characterController::~characterController()
{

}

void characterController::updateInputs(windowManager* manager)
{
	if (manager->checkKey(87)) //w
	{
		if(manager->checkKey(340))//left shift
		{
			this->player->setPlayerAction(jogging);
		}
		else
		{
			this->player->setPlayerAction(walking);
		}
		

	};

	if (!manager->checkKey(87))
	{
		this->player->setPlayerAction(idle);
	}

	if (manager->checkKey(65)) //a
	{
		this->player->setPlayerAction(sideWalkLeft);
	};

	if (manager->checkKey(83)) //s
	{
		this->player->setPlayerAction(walkingBack);
	};

	if (manager->checkKey(68)) //d
	{
		this->player->setPlayerAction(sideWalkRight);
	};

	if (manager->checkKey(32)) //space
	{
		this->player->setPlayerAction(jumping);
	}

	if(manager->leftClick())
	{
		this->player->setPlayerAction(aimingRifle);
	}

	if(manager->rightClick())
	{
		this->player->setPlayerAction(aimingPistol);
	}
}



void characterController::addPlayerToScene(Shader* shader)
{
	transform* playerTranform = this->player->getPlayersTransform();
	Model* playerModel = this->player->getPlayerModel();
	Shader* playerShader = shader;

	this->sceneId = this->sceneObj->addObjectToScene(playerModel,*playerTranform,shader);
}

void characterController::addPlayerToWorld()
{
	this->physicsId = this->world->createCapsuleShape(this->player->getPlayersTransform()->position, glm::quat(1.0, 0.0, 0.0, 0.0f), 50, 0.8, 1.5, Dynamic);
	this->world->changeColliderOrigin(this->physicsId, glm::vec3(0.0, 1.7, 0.0));
	this->world->lockBodyRotationAxis(this->physicsId, glm::vec3(1, 1, 1));
}



void characterController::updateController(float dt, Level currentLevel)
{
	bool groundContact = false;
	//calculate new postions/orientations
	transform* playerTransform = player->getPlayersTransform();
	glm::vec3 newPosition(1.0f);// = playerTransform->position;// world->getBodyPosition(physicsId);// playerTransform->position;
	glm::vec3 physWorldPos = playerTransform->position;// this->world->getBodyPosition(this->physicsId);

	//checking for ground collision and applying gravity
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
		playerTransform->position = glm::vec3(physWorldPos.x, playerTransform->position.y, physWorldPos.z) + glm::vec3(relativeFront.x,0, relativeFront.z) * (float)player->getPlayerMoveSpeed() * dt;
	}
	if(this->player->getPlayerAction() == jogging)
	{
		glm::vec3 relativeFront = player->getPlayerRelativeTransform()->front;
		playerTransform->position = glm::vec3(physWorldPos.x, playerTransform->position.y, physWorldPos.z) + glm::vec3(relativeFront.x, 0, relativeFront.z) * (float)player->getPlayerMoveSpeed() * 2.0f * dt;
	}
	
	if (this->player->getPlayerAction() == jumping) //not working quite yet
	{
		if (groundContact)
		{
			
		}
	} 
	

	this->world->setBodyPosition(this->physicsId, playerTransform->position);
	this->sceneObj->updateTransform(this->sceneId, *playerTransform);
	this->player->setPlayerTransform(*playerTransform);
	player->calculateRelTransform();
	//update orientation too momentarily
}