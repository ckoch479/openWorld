#pragma once
#include "includes/glm/glm.hpp"
#include "Includes/glm/gtc/type_ptr.hpp"

#include "Texture.h"

#include <vector>
#include <string>
#include <map>
#include <unordered_map>

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

struct textureData //named such to differentiate between just the data and an actual texture object
{
	std::string filePath;	//path to load the texture from
	std::string uniqueName; //for resource manager, textures arent attached fully to mesh allows reused textures to only be loaded once
};

struct Material
{
	Texture* diffuse0;
	textureData diffuseData;
	Texture* specular0;
	textureData specularData;
	Texture* normalMap0;
	textureData normalData;

	float shininess;
};

struct Mesh
{
	std::vector <Vertex> vertices;
	std::vector <unsigned int> indices;
	Material material; //will replace textureData vector
	unsigned int VAO;//for rendering
	unsigned int VBO;
	unsigned int EBO;
};

struct Bone
{
	int id;
	glm::mat4 offsetMatrix;
	std::string name;
};

struct Model
{
	std::vector <Mesh> meshes;
	std::vector <Bone> Skeleton;
	std::map<std::string, Bone> boneMap;
	//glm::mat4 boneMatrices[100];
};

struct pointLight
{
	glm::vec3 position;

	float constant;
	float linear;
	float quadratic;

	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
};

struct directionalLight
{
	glm::vec3 direction;

	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
};

struct spotLight
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

//scene transform
struct transform
{
	glm::vec3 position;
	glm::quat orientation;
	glm::vec3 scale;
};

struct relTransform
{
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;
};

//2d rendering
struct Vertex2D
{
	glm::vec2 position; //local position will be transformed by a positonal transform when rendered
	glm::vec4 color;    //color of this vertex

	Vertex2D(float x, float y, float r, float g, float b, float a)
	{
		this->position.x = x;
		this->position.y = y;
		this->color.x = r;
		this->color.y = g;
		this->color.z = b;
		this->color.w = a;
	}

	Vertex2D(float x, float y, glm::vec4 RGBA)
	{
		this->position.x = x;
		this->position.y = y;
		this->color = RGBA;
	}
};
struct shape2D
{
	std::vector <Vertex2D> vertices;

	//has these instead of a transform
	glm::vec3 position;
	glm::vec3 scale;

	unsigned int VAO;
	unsigned int VBO;
};