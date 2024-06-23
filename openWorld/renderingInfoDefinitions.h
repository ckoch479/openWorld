#pragma once
#include "includes/glm/glm.hpp"
#include "Includes/glm/gtc/type_ptr.hpp"



//struct Vertex
//{
//	glm::vec3 vertexPositions;
//	glm::vec3 normals;
//	glm::vec2 texCoords;
//
//	int boneIds[4];
//	float boneWeights[4];
//
//	glm::vec3 tangent;
//	glm::vec3 bitTangent;
//};

struct Material
{
	Texture* diffuseTexture;
	Texture* specularTexture;
	Texture* normalTexture;
	float shininess;
};

struct mesh
{
	//std::vector <Vertex> vertices;
	std::vector <unsigned int> indicies;
	Material material;
};

//struct Bone
//{
//	int id;
//	glm::mat4 offsetMatrix;
//	std::string name;
//};

struct Model
{
	std::vector <mesh*> meshes;
	//std::vector <Bone> skeleton;
};

struct animation
{
	float duration;
	int ticksPerSecond;
	std::string name;
	std::string rootBoneName;
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