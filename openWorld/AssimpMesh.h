#pragma once
#include "glad/glad.h"

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

#include "Includes/glm/glm.hpp"
#include "Includes/glm/gtc/type_ptr.hpp"

#define MAX_BONE_INFLUENCE 4

struct AssimpVertex
{
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;

	int BoneIDs[MAX_BONE_INFLUENCE];

	float weights[MAX_BONE_INFLUENCE];
};

#ifndef ASSIMPMESH_H
#define ASSIMPMESH_H
class AssimpMesh
{
public:
	

	AssimpMesh(std::vector <AssimpVertex> vertices, std::vector <unsigned int> indices, std::vector <std::string> textures);

	AssimpMesh(std::vector <AssimpVertex> vertices, std::vector <unsigned int> indices);

	std::vector <glm::vec3> getVertexPositions();

	std::vector <glm::vec3> getVertexNormals();

	std::vector <glm::vec2> getVertexTexCoords();

	std::vector <unsigned int> getIndices();

private:

	std::vector <AssimpVertex> vertices;
	std::vector <unsigned int> indices;

	//texture paths will be stored in the vector
	std::vector <std::string> textures;
};

#endif