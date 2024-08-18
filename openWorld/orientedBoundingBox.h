#pragma once

#include <iostream>
#include <vector>
#include <map>

#include "includes/glm/glm.hpp"
#include "Includes/glm/gtc/type_ptr.hpp"

#include "Collider.h"


#ifndef ORIENTEDBOUNDINGBOX_H
#define ORIENTEDBOUNDINGBOX_H
class orientedBoundingBox : public Collider
{
	public:

		orientedBoundingBox();
	orientedBoundingBox(glm::vec3 halfExtents);

	~orientedBoundingBox();

	void updateTransform(glm::vec3 position, glm::quat orient);

	void setHalfExtents(glm::vec3 newExtents);

	//glm::vec3 returnPosition();

	//glm::quat returnOrientation();

	std::vector <glm::vec3> returnVertices();

	glm::vec3 returnHalfExtents();

	//check if another OBB and this one are colliding, if not returns false
	bool checkCollision(orientedBoundingBox* other);

	glm::vec3 returnPosition() override;

	glm::quat returnOrientation() override;

	std::vector <glm::vec3> returnPoints() override { return this->returnVertices(); };

private:

	glm::vec3 position;
	glm::quat orientation;
	glm::vec3 halfExtents;

};

#endif