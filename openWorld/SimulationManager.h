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
#include "renderContext.h"

#include "includes/glm/glm.hpp"
#include "Includes/glm/gtc/type_ptr.hpp"

#include "Level.h"

#include "player.h"
#include "npcManager.h"
#include "renderContext.h"

#include "ShapeGenerator.h"
#include "guiManager.h"

#include "debugger.h"
#include "worldObjectManager.h"

//#include "programTimer.h"

#ifndef SIMULATIONMANAGER_H
#define SIMULATIONMANAGER_H

enum gameState 
{
active, 
end, 
pause, 
loading, 
startup, 
shutdown, 
editor, 
debug,
};

enum subGameState
{
	mainMenu,
	settingsMenu,
	creditsMenu,
	newGame,
	campaignOne,
	campaignTwo,
	sandBox,
};

class SimulationManager
{
public:

	SimulationManager() {};

	~SimulationManager() {};

	void Init();

	void run();

	void shutDown();

	void setDeltaTime();

	//void playerInputTestFunction(playerEntity* player, windowManager* window);

	

private:

	void loadAnimations();

	scene* sceneObj;
	renderer* gameRenderer;
	PhysicsWorld* world;
	windowManager* WindowManager;
	debugger* Debug;
	worldObjectManager* worldManager;


	//InputManager* inputs;
	//resource manager
	//platform detection
	//physics/dynamics
	//animation manager
	//scripting manager

	int SCR_WIDTH = 1600;
	int SCR_HEIGHT = 800;

	gameState state;
	subGameState subState;

	float deltaTime = 0.0f;
	float lastFrame = 1.0f;

	float timestep = 1.0f / 30;
	float accumulator = 0.0f;

};

#endif // !SIMULATIONMANAGER_H