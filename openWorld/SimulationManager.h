#pragma once

#include <glad/glad.h>
#include "GLFW/glfw3.h"

#include <iostream>
#include <vector>
#include <map>

#include "Renderer.h"
#include "Scene.h"
#include "Camera.h"
#include "Shader.h"


#include "includes/glm/glm.hpp"
#include "Includes/glm/gtc/type_ptr.hpp"

#ifndef SIMULATIONMANAGER_H
#define SIMULATIONMANAGER_H

enum gameState 
{
running, end, pause, loading, startup, shutdown
};

class SimulationManager
{
public:

	SimulationManager() {};

	~SimulationManager() {};

	void Init();

	void run();

	void shutDown();

	void checkKeys();

	void setDeltaTime();
private:

	Scene* scene;
	Renderer* renderer;
	//InputManager* inputs;
	//resource manager
	//platform detection
	//physics/dynamics
	//animation manager
	//scripting manager

	gameState state;

	float deltaTime = 0.0f;
	float lastFrame = 0.0f;
};

#endif // !SIMULATIONMANAGER_H