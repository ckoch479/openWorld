#pragma once

#include <glad/glad.h>
#include "GLFW/glfw3.h"

#include <iostream>
#include <vector>
#include <map>
#include <string>

#include "includes/glm/glm.hpp"
#include "Includes/glm/gtc/type_ptr.hpp"

#include "lookup_table.h"

#include "Scene.h"
#include "Camera.h"


#ifndef RENDERER_H
#define RENDERER_H

//temporary************
static bool Keys[1024];
static float currentMouse;
static float lastMouse;
static bool firstMouse;
//temporary************

class Renderer
{
public:
	Renderer();
	~Renderer();

	


	//create gl context and window
	void init();

	//draw all objects currently in scene
	void drawWindow(Scene* scene);

	void shutDown();

	bool checkWindowCloseState();


private:
	GLFWwindow* window;

	float SCR_WIDTH = 800;
	float SCR_HEIGHT = 600;

	

};



#endif