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

void player::LoadPlayerModel(const std::string filepath, std::string playername)
{
	this->playerName = playername;
	this->playerModel = ResourceManager::loadModel(filepath,playername);
}

void player::AddAnimationtoPlayer(AnimationData* animation, std::string name)
{

}

void player::AddAnimationtoPlayer(std::string filepath, std::string name) //for if you loaded the animation into the scene manually
{

}

std::string player::getCurrentAnimation()
{
	return this->currentAnimationName;
}

void player::setCurrentAnimation(std::string animationName)
{
	this->currentAnimationName = animationName;
}

void player::setPosition(glm::vec3 position)
{
	this->position = position;
}

void player::setRotationAngle(float angle)
{
	this->rotationAngle = angle;
}

void player::setRelativePosition(playerRelativePosition relativePosition, float distance)
{

}

void player::setPlayerFront(glm::vec3 front)
{
	this->playerFront = front;
}

void player::calculatePlayerFront()
{

}

void player::setCurrentAnimationActive(std::string animationName)
{

}