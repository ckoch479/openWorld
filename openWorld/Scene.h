#pragma once

#include "includes/glad/gl.h"
#include "GLFW/glfw3.h"

#include <iostream>
#include <vector>
#include <map>

#include "includes/glm/glm.hpp"
#include "Includes/glm/gtc/type_ptr.hpp"

struct Material
{
	std::string name;

	float Ambient[3];
	float Diffuse[3];
	float Specular[3];
	float Shininess;
};

struct Mesh 
{
	std::string name;

	GLuint MeshVAO;
	GLuint PositionBO;
	GLuint TexCoordBO;
	GLuint NormalBO;
	GLuint IndexBO;

	GLuint IndexCount;
	GLuint VertexCount;

	//std::vector <GLDrawElementsIndirectCommand>
	std::vector<uint32_t> MaterialIDs;
};

struct Transform 
{
	glm::vec3 Scale;
	glm::vec3 RotationOrigin;
	glm::quat rotation;
	glm::vec3 Translation;
};

struct Instance 
{
	uint32_t MeshID;
	uint32_t TransformID;
};

struct Camera 
{
//view
	glm::vec3 Eye;
	glm::vec3 Target;
	glm::vec3 Up;

	//projection
	float FovY;
	float Aspect;
	float ZNear;
};


class Scene
{
public:

	//tables:
	//materials
	//meshes
	//cameras
	//skeletons
};

