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

	bool hasActiveAnimation;
	ID animationID;

	std::map<std::string, BoneData> boneMap;
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
	glm::vec3 direction;

	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
};

struct Pointlight
{
	glm::vec3 position;

	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;

	float constant;
	float linear;
	float quadratic;
};

struct SpotLight
{
	glm::vec3 position;
	glm::vec3 direction;

	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;

	float constant;
	float linear;
	float quadratic;
	float cutoff;
	float outerCutoff;
};


struct RenderAnimation
{
	AnimationData animationData;
	std::string name;
	float currentPoint;
	
};

#define MAX_NR_SPOT_LIGHTS 6;


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

	ID createMesh(MeshData mesh, Shader& shader, AnimationData* animation);

	//test function for transforms
	ID createTransform(glm::vec3 position, glm::vec3 rotationOrigin, glm::quat rotation, glm::vec3 scale);

	//animations

	ID createAnimation(AnimationData* animation);

	ID createAnimation(AnimationData* animation, std::string name);
	
	void DebugFunction();

	void MoveCamera(Camera_Movement direction, float deltaTime);

	void MouseAimCamera(float xoffset, float yoffset);

	ID createLight(DirectionalLight directionalLight);
	
	ID createLight(Pointlight pointLight);

	ID createLight(SpotLight spotLights);

	ID createPointLight(glm::vec3 position,glm::vec3 ambient, glm::vec3 diffuse,glm::vec3 specular, float constant, float linear, float quadratic);

	ID createDirectionalLight(glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular);

	ID createSpotLight(glm::vec3 position,glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float constant, float linear, float quadratic, float innerCutoff, float outerCutoff);

	void MovePointLight(ID pointLightID, glm::vec3 translation);

private:

	lookup_table<Instance> Instances;
	lookup_table<RenderMesh> Meshes;
	lookup_table<Transform> Transforms;

	lookup_table<RenderAnimation> animations;

	//lights in the scene
	lookup_table <Pointlight> pointLights;
	lookup_table <DirectionalLight> directionalLights;
	lookup_table <SpotLight> spotLights;


	std::vector <ID> InstanceIDs;
	std::vector <ID> pointLightIDs;

	ID spotLightID;
	ID directionLightID;

	Camera* MainCamera;

	unsigned int InstanceCount = 0;
	unsigned int numPointLights = 0;

	friend class Renderer;

};

//things to add:
// light objects
// textures
// bone and bone transformations
// shadows?
// 2d Graphics?

