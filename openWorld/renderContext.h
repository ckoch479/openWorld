#pragma once

#include "Shader.h"
#include "Scene.h"
#include "Camera.h"

struct renderContext
{
	Shader* shader;
	scene* sceneObj;
	Camera* camera;

	renderContext(Shader* newShader, scene* newScene, Camera* newCamera)
	{
		this->shader = newShader;
		this->sceneObj = newScene;
		this->camera = newCamera;
	}

	renderContext() {};
};