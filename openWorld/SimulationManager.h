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

#include "GameObject.h"


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

	void checkMouse();

	void setDeltaTime();
private:

	Scene* scene;
	Renderer* renderer;
	PhysicsWorld* world;
	//InputManager* inputs;
	//resource manager
	//platform detection
	//physics/dynamics
	//animation manager
	//scripting manager

	gameState state;

	float deltaTime = 0.0f;
	float lastFrame = 1.0f;

	float lastMouseX = 400.0f;
	float lastMouseY = 300.0f;

	float mouseSensitivity = 0.5f;

	bool firstMouse = true;

	//for testing to be removed later
	bool up = false;
	bool down = false;
	bool left = false;
	bool right = false;
	bool space = false;
};

#endif // !SIMULATIONMANAGER_H