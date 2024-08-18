#include "orientedBoundingBox.h"

orientedBoundingBox::orientedBoundingBox()
{

}

orientedBoundingBox::orientedBoundingBox(glm::vec3 halfExtents)
{
	this->halfExtents = halfExtents;
}

orientedBoundingBox::~orientedBoundingBox()
{

}

void orientedBoundingBox::updateTransform(glm::vec3 position, glm::quat orient)
{
	this->position = position;
	this->orientation = orient;
}

void orientedBoundingBox::setHalfExtents(glm::vec3 newExtents)
{
	this->halfExtents = newExtents;
}

glm::vec3 orientedBoundingBox::returnPosition()
{
	return this->position;
}

glm::quat orientedBoundingBox::returnOrientation()
{
	return this->orientation;
}

std::vector <glm::vec3> orientedBoundingBox::returnVertices()
{
	std::vector <glm::vec3> vertices;

	glm::vec3 tempVertex1(-halfExtents.x, -halfExtents.y, halfExtents.z);
	glm::vec3 tempVertex2(-halfExtents.x, halfExtents.y, halfExtents.z);
	glm::vec3 tempVertex3(halfExtents.x, halfExtents.y, halfExtents.z);
	glm::vec3 tempVertex4(halfExtents.x, -halfExtents.y, halfExtents.z);

	glm::vec3 tempVertex5(-halfExtents.x, -halfExtents.y, -halfExtents.z);
	glm::vec3 tempVertex6(-halfExtents.x, halfExtents.y, -halfExtents.z);
	glm::vec3 tempVertex7(halfExtents.x, halfExtents.y, -halfExtents.z);
	glm::vec3 tempVertex8(halfExtents.x, -halfExtents.y, -halfExtents.z);

	vertices.push_back(tempVertex1);
	vertices.push_back(tempVertex2);
	vertices.push_back(tempVertex3);
	vertices.push_back(tempVertex4);

	vertices.push_back(tempVertex5);
	vertices.push_back(tempVertex6);
	vertices.push_back(tempVertex7);
	vertices.push_back(tempVertex8);

	return vertices;
}

bool orientedBoundingBox::checkCollision(orientedBoundingBox* other)
{
	//not implimented yet so returns false

	return false;
}

glm::vec3 orientedBoundingBox::returnHalfExtents()
{
	return this->halfExtents;
}