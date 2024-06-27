#include "player.h"
player::player() 
{

}

player::~player() 
{

}

glm::vec3 player::GetCurrentPosition() 
{
	return this->position;
}

float player::GetRotationAngle()
{
	return this->rotationAngle;
}

void player::LoadPlayerModel(const std::string filepath, std::string playername, scene* scene, PhysicsWorld* world, Shader& shader)
{
	this->playerName = playername;
	this->playerModel = ResourceManager::loadModel(filepath,playername);

	//this->sceneModelID = scene->createModel(*this->playerModel,shader);
	//this->sceneTransformID = scene->createTransform(this->position,glm::quat(glm::vec3(0,this->rotationAngle,0)), this->scale);

	//this->sceneObjectID = scene->AddInstance(this->sceneModelID,this->sceneTransformID);

	this->scenePtr = scene;
	this->shaderPtr = &shader;
	this->worldPtr = world;
}

void player::AddAnimationtoPlayer(animation* animation, std::string name) //for if you loaded the animation in manually
{

}

void player::AddAnimationtoPlayer(std::string filepath, std::string name) 
{
	std::string animationName = name;
	//animation* animation = ResourceManager::loadAnimation(filepath,name);

	//add animation to the player class for later reference and use
	this->SavedAnimations.push_back(animationName);

	//add animation to the scene for future reference
	//ID newID = this->scenePtr->createAnimation(animation);

	///this->animationIDmap[animationName] = newID;
}

std::string player::getCurrentAnimation()
{
	return this->currentAnimationName;
}

void player::setCurrentAnimation(std::string animationName)
{
	if (this->currentAnimationName != animationName)
	{
		this->currentAnimationName = animationName;
		setActiveAnimation(this->currentAnimationName);
	}
}

void player::setPosition(glm::vec3 position)
{
	this->position = position;
}

void player::setRotationAngle(float angle)
{
	this->rotationAngle = angle;
}

glm::vec3 player::getPlayerFront()
{
	return this->playerFront;
}

glm::vec3 player::getPlayerRight()
{
	return this->playerRight;
}

glm::vec3 player::getPlayerUp()
{
	return this->playerUp;
}

void player::setRelativePosition(playerRelativePosition relativePosition, float deltaTime)
{
	calculateVectors();

	float velocity = this->movementSpeed * deltaTime;
	switch(relativePosition)
	{
	case (PlayerFront):

		this->position += this->playerFront * velocity;

		break;

	case (PlayerLeft):

		this->position -= this->playerRight * velocity;

		break;

	case (PlayerRight):

		this->position += this->playerRight * velocity;
		
		break;

	case (PlayerBack):

		this->position -= this->playerFront * velocity;
		
		break;
	}

	
}

void player::setPlayerFront(glm::vec3 front)
{
	this->playerFront = front;
}

void player::setActiveAnimation(std::string animationName)
{
	//this->scenePtr->UpdateAnimation(this->sceneModelID,this->animationIDmap[animationName]);
}

void player::setMovementSpeed(float speed) 
{
	this->movementSpeed = speed;
}

void player::setPlayerYaw(float yaw)
{
	this->yaw = yaw;
	calculateVectors();
}

void player::calculateVectors()
{

	glm::vec3 Front;
	Front.x = cos(pitch) * sin(yaw);
	Front.y = 0;
	Front.z = cos(pitch) * cos(yaw);

	this->playerFront = glm::normalize(Front);

	// also re-calculate the Right and Up vector
	this->playerRight = glm::normalize(glm::cross(playerFront, glm::vec3(0,1,0)));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	this->playerUp = glm::normalize(glm::cross(playerRight, playerFront));
}

void player::renderPlayer(float dt, scene* scene, PhysicsWorld* world)
{
	//scene->updateTransform(this->sceneTransformID, this->position, glm::quat(glm::vec3(0,this->yaw,0)), this->scale);

}