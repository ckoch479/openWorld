#pragma once

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <iostream>
#include <vector>
#include <map>

#include "windowManager.h"
#include "Renderer.h"
#include "Scene.h"
#include "Camera.h"
#include "Shader.h"

#include "gameObjectManager.h"
#include "thirdPersonCamera.h"

#include "characterController.h"

#include "includes/glm/glm.hpp"
#include "Includes/glm/gtc/type_ptr.hpp"

#include "Level.h"

#include "playerEntity.h"

#ifndef SIMULATIONMANAGER_H
#define SIMULATIONMANAGER_H

enum gameState 
{
active, end, pause, loading, startup, shutdown
};

class SimulationManager
{
public:

	SimulationManager() {};

	~SimulationManager() {};

	void Init();

	void run();

	void shutDown();

	void checkMouse();

	void setDeltaTime();

	void playerInputTestFunction(playerEntity* player, windowManager* window);
private:

	scene* sceneObj;
	renderer* gameRenderer;
	PhysicsWorld* world;
	windowManager* WindowManager;
	//InputManager* inputs;
	//resource manager
	//platform detection
	//physics/dynamics
	//animation manager
	//scripting manager

	const unsigned int SCR_WIDTH = 1600;
	const unsigned int SCR_HEIGHT = 800;

	gameState state;

	float deltaTime = 0.0f;
	float lastFrame = 1.0f;

	float lastMouseX = 400.0f;
	float lastMouseY = 300.0f;

	float mouseSensitivity = 0.3f;

	bool firstMouse = true;

	//testing

	glm::vec3 playerPosition = glm::vec3(0,0,0);
	float playerRotation = 0.0;
	float radius = 5.0;

	glm::vec3 CameraPosition;
	float cameraPitch = 0.0f;
	float cameraYaw = 0.0f;
	float cameraFreeRotationAngle = 0.0f;

	float timestep = 1.0f / 60;
	float accumulator = 0.0f;


};

#endif // !SIMULATIONMANAGER_H