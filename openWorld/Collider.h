#pragma once

#include <iostream>
#include <vector>
#include <map>

#include "includes/glm/glm.hpp"
#include "Includes/glm/gtc/type_ptr.hpp"

#ifndef COLLIDER_H
#define COLLIDER_H
class Collider
{
public:

	virtual bool checkCollision(const Collider& other);

private:

};

//axis aligned bounding box collider
class AABB : public Collider
{
public:

	AABB();
	~AABB();

	glm::vec3 colliderPosition;
	glm::vec3 size; // instead of three distinct floats size contains the width, depth, and height of the box, x = width, y = height, and z = depth

	//not calculated in free time to hopefully be less calculations and instead is just stored in memory
	float minX;
	float minY;
	float minZ;

	float maxX;
	float maxY;
	float maxZ;


	bool checkCollision(const AABB& other);


private:


};

class SphereCollider : public Collider
{
public:

	glm::vec3 position;
	float radius;

	bool checkCollision(const SphereCollider& other);
};

class OBB : public Collider //oriented bounding box
{
	float halfWidth;
	float halfHeight;
	float halfDepth;

	glm::mat4 transform;

	bool checkCollision(const OBB& other);
};

class CapsuleCollider : public Collider
{
	glm::vec3 PointA;
	glm::vec3 PointB;
	float radius;

	bool checkCollision(const CapsuleCollider& other);
};

#endif