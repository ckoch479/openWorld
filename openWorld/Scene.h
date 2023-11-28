#pragma once

#include <glad/glad.h>
#include "GLFW/glfw3.h"

#include <iostream>
#include <vector>
#include <map>

#include "includes/glm/glm.hpp"
#include "Includes/glm/gtc/type_ptr.hpp"

#include "lookup_table.h"
#include "ResourceManager.h"

//struct Material
//{
//	std::string name;
//
//	float Ambient[3];
//	float Diffuse[3];
//	float Specular[3];
//	float Shininess;
//};

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
	float ZFar;
	float Aspect;
	float ZNear;
};


//scene is a database of all objects that need to be drawn. Each object is placed in a table. 
// All parts of each object are contained within tables as well.
//VAOS are stored in the Scene class, basic data such as Vertices, indices, and textures/materials are stored in ResourceManager
class Scene
{
public:

	//tables:
	//materials
	//meshes
	//cameras
	//skeletons

	lookup_table<Instance> Instances;
	lookup_table<Mesh> Meshes;
	lookup_table<Transform> Transforms;
	lookup_table<Material> Materials;

	ID MainCameraID;

	//load mesh to be stored as a scene object using the resource manager, returns MeshID
	ID LoadMesh(const char* filepath);

	//load an instance as a scene object with a mesh ID and a Transform ID, returns an Instance ID
	ID LoadInstance(ID MeshID, ID TransformID);

	//returns an instance ID
	unsigned int AddInstance();

	
	
};

