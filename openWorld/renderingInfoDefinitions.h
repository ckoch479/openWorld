#pragma once
#include "includes/glm/glm.hpp"
#include "Includes/glm/gtc/type_ptr.hpp"

#include <vector>
#include <string>
#include <map>
#include <unordered_map>

//this file is from when i thought adding all data related to rendering to one large header file, im working on moving things to their own files/classes, lights being a good example of
//something that will be a child class of entity later

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

//triangle based letter rendering was never a good idea but i may be able to resuse some of this code later, here to remind me to never spend that much time on this again
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