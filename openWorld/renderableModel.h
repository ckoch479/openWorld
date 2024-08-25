#pragma once

#include "Shader.h"
#include "Model.h"
#include "renderingInfoDefinitions.h" //for transform

#ifndef RENDERABLEMODEL_H
#define RENDERABLEMODEL_H

//not sure how i feel about this struct right now may remove later, really just used to collect a large amount of rendering data
struct renderableModel
{
	Model* model;
	glm::vec3* pos;
	glm::quat* orient;
	glm::vec3* scale;
	std::vector <glm::mat4>* animationMatrices;
	bool hasAnimations = false; //for ease of processing/use and peace of mind
	Shader* modelShader;

	renderableModel(Model* model, glm::vec3* pos, glm::quat* orient, glm::vec3* scale, Shader* modelShader)
	{
		this->model = model;
		this->pos = pos;
		this->orient = orient;
		this->scale = scale;
		this->modelShader = modelShader;
		this->hasAnimations = false;
	}
};


#endif