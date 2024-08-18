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

	Collider() {};
	~Collider() {};

	virtual glm::vec3 returnPosition() { return glm::vec3(0.0f); };

	virtual glm::quat returnOrientation() { return glm::quat(1.0, 0.0, 0.0, 0.0); };

	virtual std::vector <glm::vec3> returnPoints() { return std::vector <glm::vec3> {glm::vec3(0.0f)}; }; //for OBB returns it's vertices, for raycast returns point A and point B
private:


};

//class orientedBoundingBox : public Collider
//{
//public:
//
//	orientedBoundingBox();
//
//	~orientedBoundingBox();
//
//	void createCollider(glm::mat4 transform, glm::vec3 position, float halfWidth, float halfHeight, float halftDepth);
//
//	void updateTransform(glm::mat4 transform);
//
//	glm::vec3 returnPosition();
//
//	std::vector <glm::vec3> returnVertices();
//
//private:
//
//	glm::mat4 transform;
//
//	float halfWidth;
//	float halfHeight;
//	float halfDepth;
//
//};

#endif