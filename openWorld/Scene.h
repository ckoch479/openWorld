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

	std::vector <Texture*> meshDiffuseTextures;
	std::vector <Texture*> meshSpecularTextures;
};

struct RenderModel
{
	std::vector <ID> renderMeshIDs;

	Shader* Modelshader;

	bool hasActiveAnimation;
	ID animationID;

	std::map<std::string, BoneData> boneMap;
};

struct Transform 
{
	glm::vec3 Scale;
	glm::vec3 Translation;
	glm::quat rotationQuat;
};

struct Instance 
{
	ID ModelID;
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

struct RenderTriangleVertex
{
	glm::vec3 vertexPosition;
	glm::vec3 color;
	int vertexId;
};

struct triangleTransforms
{
	glm::vec3 a;
	glm::vec3 b;
	glm::vec3 c;
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
	ID AddInstance(ID& ModelID,ID& TransformID);

	ID AddInstance(RenderModel& Model, Transform& transform);

	ID createModel(ModelData model, Shader& shader);

	ID createModel(ModelData model, Shader& shader, AnimationData* animation);

	void removeModelFromScene(ID modelID);

	void UpdateAnimation(ID modelID, ID animationID);

	void UpdateShader(ID modelID, Shader& shader);

	//test function for transforms
	ID createTransform(glm::vec3 position, glm::quat rotation, glm::vec3 scale);

	void updateTransform(ID transformID, glm::vec3 position, glm::quat rotation, glm::vec3 scale);
	//animations

	ID createAnimation(AnimationData* animation);

	ID createAnimation(AnimationData* animation, std::string name);
	
	void DebugFunction();

	void MoveCamera(Camera_Movement direction, float deltaTime);

	void MouseAimCamera(float xoffset, float yoffset);

	void setCameraPosition(glm::vec3 target, glm::vec3 position, float pitch, float yaw);

	ID createLight(DirectionalLight directionalLight);
	
	ID createLight(Pointlight pointLight);

	ID createLight(SpotLight spotLights);

	ID createPointLight(glm::vec3 position,glm::vec3 ambient, glm::vec3 diffuse,glm::vec3 specular, float constant, float linear, float quadratic);

	ID createDirectionalLight(glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular);

	ID createSpotLight(glm::vec3 position,glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float constant, float linear, float quadratic, float innerCutoff, float outerCutoff);

	void MovePointLight(ID pointLightID, glm::vec3 translation);
	
	void createCubeMap(std::vector <std::string> cubeMapTexturePaths, Shader* cubeMapshader);

	void setDebugTriangleRenderStatus(bool set);

	void debugTriangleInfo(std::vector< triangleTransforms> triangles,Shader* triangleShader);

private:

	void createCubeMapVAO();

	void createTriangleVAO();

	unsigned int loadCubeMapTextures(std::vector <std::string> texturePaths);

	lookup_table<Instance> Instances;
	lookup_table<RenderMesh> Meshes;
	lookup_table<Transform> Transforms;
	lookup_table<RenderModel> Models;

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

	float cubeMapLoaded = false; //used in the renderer to check status of a cubemap
	Shader* cubeMapShader; //created when a cube map is created
	unsigned int cubeMapVAO;
	unsigned int cubeMapVBO;

	unsigned int cubeMaptextureID;

	std::vector <RenderTriangleVertex> triangleVertices; //vertices used to render a simple triangle and change it's position
	std::vector <triangleTransforms> triangleVertexPositions;
	Shader* triangleShader;

	unsigned int triangleVAO;
	unsigned int triangleVBO;

	bool renderDebugTriangles = false;

	unsigned int InstanceCount = 0;
	unsigned int numPointLights = 0;

	ID createMesh(MeshData mesh);

	friend class Renderer;

};

//things to add:
// light objects
// textures
// bone and bone transformations
// shadows?
// 2d Graphics?

