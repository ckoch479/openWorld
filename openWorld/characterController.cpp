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
		this->player->setPlayerAction(walking);
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
	this->physicsId = this->world->createCapsuleShape(this->player->getPlayersTransform()->position, glm::quat(1.0, 0.0, 0.0, 0.0f), 50, 0.6, 1.5, Dynamic);
	this->world->changeColliderOrigin(this->physicsId, glm::vec3(0.0, 1.5, 0.0));
	this->world->lockBodyRotationAxis(this->physicsId, glm::vec3(0, 1, 0));
}



void characterController::updateController(float dt)
{
	//calculate new postions/orientations
	transform* playerTransform = player->getPlayersTransform();
	glm::vec3 newPosition = world->getBodyPosition(physicsId);// playerTransform->position;
	//glm::quat newOrientation = playerTransform->orientation;

	//do fun and cool math stuff here 
	rayCastIntersectInfo newInfo;
	newInfo = this->world->rayCast(newPosition + glm::vec3(0,-0.1,0), glm::vec3(newPosition.x, -20, newPosition.z));
	
	if(newInfo.hit == true) 
	{
		std::cout << "raycast hit found!\n";
		std::cout << newInfo.worldPositionHitPoint.x << " , " << newInfo.worldPositionHitPoint.y << " , " << newInfo.worldPositionHitPoint.z << std::endl;
		playerTransform->position.y = newInfo.worldPositionHitPoint.y; +0.01;
	}

	if(!newInfo.hit)
	{
		std::cout << "no hit detected\n";
	}
	//update scene and physicsWorld with positions;

	this->sceneObj->updateTransform(this->sceneId, *playerTransform);
	//this->world->setBodyPosition(this->physicsId,playerTransform->position);

	this->player->setPlayerTransform(*playerTransform);
	//update orientation too momentarily
}