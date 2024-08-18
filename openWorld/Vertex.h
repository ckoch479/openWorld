#pragma once

#include "includes/glm/glm.hpp"
#include "Includes/glm/gtc/type_ptr.hpp"

struct Vertex
{
	glm::vec3 vertexPosition;
	glm::vec3 normal;
	glm::vec2 textureCoordinates;

	glm::vec3 tangent;
	glm::vec3 bitTangent;

	int boneIDs[4];
	float boneWeights[4];
};