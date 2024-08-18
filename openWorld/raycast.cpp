#include "raycast.h"

raycast::raycast(glm::vec3 pointa, glm::vec3 pointb)
{

}

raycast::~raycast()
{

}

void raycast::addCollision(orientedBoundingBox* colliderBox)
{

}

orientedBoundingBox* raycast::returnFirstCollision()
{
	return nullptr;
}

std::vector <orientedBoundingBox*> raycast::returnAllCollisions()
{
	return this->collidedBoxes;
}

bool raycast::checkCollision(orientedBoundingBox* box)
{
	bool hasCollided = false;


	return hasCollided;
}