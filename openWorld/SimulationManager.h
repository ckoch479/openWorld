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

	//testing

	glm::vec3 playerPosition = glm::vec3(1,1,1);
	float playerRotation = 1.0;
	float radius = 5.0;

	glm::vec3 CameraPosition;
	float cameraPitch = 0.0f;
	float cameraYaw = 0.0f;
	float cameraFreeRotationAngle = 0.0f;


};

#endif // !SIMULATIONMANAGER_H