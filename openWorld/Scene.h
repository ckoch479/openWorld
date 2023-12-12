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
#include "Shader.h"
#include "Camera.h"

struct RenderMesh 
{

	GLuint MeshVAO;
	GLuint MeshVBO;
	GLuint MeshEBO;

	GLuint IndexCount;
	GLuint VertexCount;

	bool hasDiffuseTextures;
	bool hasSpecularTextures;

	int numDiffuseTextures;
	int numSpecularTextures;

	//ptr to the shader used by this mesh?
	Shader* Meshshader;
	std::vector <Texture*> meshDiffuseTextures;
	std::vector <Texture*> meshSpecularTextures;
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
	ID MeshID;
	ID TransformID;
};

struct DirectionalLight
{

};

struct Pointlight
{

};

struct SpotLight
{

};

struct RenderAnimation
{

};


//scene is a database of all objects that need to be drawn. Each object is placed in a table. 
// All parts of each object are contained within tables as well.
//VAOS are stored in the Scene class, basic data such as Vertices, indices, and textures/materials are stored in ResourceManager
class Scene
{
public:

	Scene();

	void Init();
	
	//returns an instance ID
	ID AddInstance(ID& MeshID,ID& TransformID);

	ID AddInstance(RenderMesh& mesh, Transform& transform);

	//ID createMesh(std::vector <Vertex> vertices, std::vector <unsigned int> indices, std::vector <Texture> textures);

	//test function for meshes
	ID createMesh(std::vector <glm::vec3>& vertices, std::vector <glm::vec3>& colors, Shader& shader);

	ID createMesh(MeshData mesh, Shader& shader);

	//test function for transforms
	ID createTransform(glm::vec3 position, glm::vec3 rotationOrigin, glm::quat rotation, glm::vec3 scale);
	
	void DebugFunction();

	void MoveCamera(Camera_Movement direction, float deltaTime);

	void MouseAimCamera(float xoffset, float yoffset);
	

private:

	lookup_table<Instance> Instances;
	lookup_table<RenderMesh> Meshes;
	lookup_table<Transform> Transforms;
	//lookup_table<Material> Materials;


	std::vector <ID> InstanceIDs;

	Camera* MainCamera;

	unsigned int InstanceCount = 0;

	friend class Renderer;

};

//things to add:
// light objects
// textures
// bone and bone transformations
// shadows?
// 2d Graphics?

