#pragma once

#include <iostream>

#include "Scene.h"

#include "includes/glm/glm.hpp"
#include "includes/glm/gtc/type_ptr.hpp"
#include "includes/glm/gtc/quaternion.hpp"

#ifndef LIGHTEMITTER_H
#define LIGHTEMITTER_H

enum lightType
{
	directional,
	spot,
	point,
};

class lightEmitter
{
public:

	lightEmitter(std::string uniqueId, lightType type);
	~lightEmitter();

	void setLighting(glm::vec3 position, glm::vec3 direction, glm::vec3 ambientColor, glm::vec3 specularColor, glm::vec3 diffuseColor);

	void addLightingToScene(scene* sceneObj);

	void removeLightingFromScene(scene* scenObj);

	void updateSceneLighting();

private:

	lightType type;

	glm::vec3 position;
	glm::vec3 direction; 

	glm::vec3 ambientColor;
	glm::vec3 diffuseColor;
	glm::vec3 specularColor;

	std::string uniqueId;
	std::string sceneId;

	scene* sceneObj;

};

#endif