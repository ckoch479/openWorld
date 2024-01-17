#pragma once

#include <iostream>
#include <vector>
#include <map>

#include "includes/glm/glm.hpp"
#include "Includes/glm/gtc/type_ptr.hpp"

#ifndef COLLIDER_H
#define COLLIDER_H
class Collider //default collider is an AABB
{
public:

	Collider();
	~Collider();

	virtual void createCollider(glm::vec3 newPosition, float halfWidth, float halfHeight, float halfDepth);

	virtual glm::vec3 returnPosition();

	virtual std::vector <glm::vec3> returnVertices();
	
	glm::vec3 position;
private:

	float halfWidth;
	float halfHeight;
	float halfDepth;

};

class orientedBoundingBox : public Collider
{
public:

	orientedBoundingBox();

	~orientedBoundingBox();

	void createCollider(glm::mat4 transform, glm::vec3 position, float halfWidth, float halfHeight, float halftDepth);

	void updateTransform(glm::mat4 transform);

	glm::vec3 returnPosition();

	std::vector <glm::vec3> returnVertices();

private:

	glm::mat4 transform;

	float halfWidth;
	float halfHeight;
	float halfDepth;

};

class meshCollider : public Collider
{
public:

	meshCollider();
	~meshCollider();

	void createCollider(std::vector <glm::vec3> vertices, std::vector <glm::vec3> vertexNormals);

	glm::vec3 returnPosition();

	std::vector <glm::vec3> returnVertices();

private:

	std::vector <glm::vec3> vertices;
	std::vector <glm::vec3> vertexNormals;

};

class sphereCollider : public Collider
{
public:
	sphereCollider();
	~sphereCollider();

	void createCollider(glm::vec3 position, float radius);

	glm::vec3 returnPosition();

	float returnRadius();

	float radius;

private:

	

};

#endif