#include "Collider.h"
Collider::Collider()
{

}

Collider::~Collider()
{

}

void Collider::createCollider(glm::vec3 newPosition, float halfWidth, float halfHeight, float halfDepth)
{
	this->position = newPosition;
	this->halfWidth = halfWidth;
	this->halfHeight = halfHeight;
	this->halfDepth = halfDepth;
}

glm::vec3 Collider::returnPosition()
{
	return this->position;
}

std::vector <glm::vec3> Collider::returnVertices()
{
	std::vector <glm::vec3> vertices;

	glm::vec3 tempVertex1(-halfWidth, -halfHeight, halfDepth);
	glm::vec3 tempVertex2(-halfWidth, halfHeight, halfDepth);
	glm::vec3 tempVertex3(halfWidth, halfHeight, halfDepth);
	glm::vec3 tempVertex4(halfWidth, -halfHeight, halfDepth);

	glm::vec3 tempVertex5(-halfWidth, -halfHeight, -halfDepth);
	glm::vec3 tempVertex6(-halfWidth, halfHeight, -halfDepth);
	glm::vec3 tempVertex7(halfWidth, halfHeight, -halfDepth);
	glm::vec3 tempVertex8(halfWidth, -halfHeight, -halfDepth);

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

//oriented bounding box
//orientedBoundingBox::orientedBoundingBox()
//{
//
//}
//
//orientedBoundingBox::~orientedBoundingBox()
//{
//
//}
//
//void orientedBoundingBox::createCollider(glm::mat4 transform, glm::vec3 position, float halfWidth, float halfHeight, float halftDepth)
//{
//	this->transform = transform;
//	this->position = position;
//	this->halfWidth = halfWidth;
//	this->halfHeight = halfHeight;
//	this->halfDepth = halftDepth;
//}
//
//void orientedBoundingBox::updateTransform(glm::mat4 transform)
//{
//	this->transform = transform;
//}
//
//glm::vec3 orientedBoundingBox::returnPosition()
//{
//	return this->position;
//}
//
//std::vector <glm::vec3> orientedBoundingBox::returnVertices()
//{
//	std::vector <glm::vec3> vertices;
//
//	glm::vec3 tempVertex1(-halfWidth, -halfHeight, halfDepth);
//	glm::vec3 tempVertex2(-halfWidth, halfHeight, halfDepth);
//	glm::vec3 tempVertex3(halfWidth, halfHeight, halfDepth);
//	glm::vec3 tempVertex4(halfWidth, -halfHeight, halfDepth);
//
//	glm::vec3 tempVertex5(-halfWidth, -halfHeight, -halfDepth);
//	glm::vec3 tempVertex6(-halfWidth, halfHeight, -halfDepth);
//	glm::vec3 tempVertex7(halfWidth, halfHeight, -halfDepth);
//	glm::vec3 tempVertex8(halfWidth, -halfHeight, -halfDepth);
//
//	vertices.push_back(tempVertex1);
//	vertices.push_back(tempVertex2);
//	vertices.push_back(tempVertex3);
//	vertices.push_back(tempVertex4);
//
//	vertices.push_back(tempVertex5);
//	vertices.push_back(tempVertex6);
//	vertices.push_back(tempVertex7);
//	vertices.push_back(tempVertex8);
//
//	return vertices;
//}
