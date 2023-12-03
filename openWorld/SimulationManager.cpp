#include "SimulationManager.h"

void SimulationManager::Init()
{
	this->state = startup;
	//run platform detection
	//init glfw/glut
	//create window
	
	this->renderer = new Renderer;
	renderer->init();
	

	Camera newCamera(glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0), -90, 0);

	this->scene = new Scene;
	scene->Init(newCamera);

	this->state = running;
};

void SimulationManager::run() 
{
	//game loop and refresh/rendering loop is controlled here, actual rendering is done with the renderer
	while (this->state == running)
	{
		if (renderer->checkWindowCloseState())  //check if user closes out of the window
		{
			this->state = shutdown;
			break;
		}

		setDeltaTime(); //update deltaTime for this loop
		checkKeys(); //check for active keys during this loop


		this->renderer->drawWindow(this->scene);
	}

	if (this->state != running && this->state != pause) //if the game is not running or paused shutdown
	{
		this->renderer->shutDown();
	}


}

void SimulationManager::checkKeys() 
{

}

void SimulationManager::setDeltaTime() 
{

}

void SimulationManager::shutDown() 
{

}