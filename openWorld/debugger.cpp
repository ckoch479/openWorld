#include "debugger.h"

debugger::debugger()
{

}

debugger::~debugger()
{

}

void debugger::addRenderer(renderer* gameRenderer)
{
	this->gameRenderer = gameRenderer;
}

void debugger::updateDebugger()
{

	drawWorldLines();
}

void debugger::drawWorldLines()
{
	//draw world grid

	for(int i = 0; i < 100; i++)
	{
		
		this->gameRenderer->addLine(glm::vec3(-100,0,i), glm::vec3(100,0,i), glm::vec4(1.0,0.0,0.0,0.8));	  //x axis
		this->gameRenderer->addLine(glm::vec3(-100, 0, -1 * i), glm::vec3(100, 0, -1*i), glm::vec4(1.0, 0.0, 0.0, 0.8)); //-x axis

		this->gameRenderer->addLine(glm::vec3(i,0,-100), glm::vec3(i,0,100), glm::vec4(0.0, 1.0, 0.0, 0.8)); //z axis
		this->gameRenderer->addLine(glm::vec3(-i, 0, -100), glm::vec3(-i, 0, 100), glm::vec4(0.0, 1.0, 0.0, 0.8)); //-z axis
	
	}
	this->gameRenderer->addLine(glm::vec3(0.0f), glm::vec3(0, 100, 0), glm::vec4(0, 0, 1, 0.7));
}

void debugger::addModelData(std::string data)
{
	std::string timeStamp = "\n[" + std::to_string(this->getTimeStamp()) + "] : "; //add timestamp to data input
	this->modelData += timeStamp;
	this->modelData += data;
}

void debugger::addRenderData(std::string data)
{
	std::string timeStamp = "\n[" + std::to_string(this->getTimeStamp()) + "] : "; //add timestamp to data input
	this->renderData += timeStamp;
	this->renderData += data;
}

void debugger::addAnimationData(std::string data)
{
	std::string timeStamp = "\n[" + std::to_string(this->getTimeStamp()) + "] : "; //add timestamp to data input
	this->animationData += timeStamp;
	this->animationData += data;
}

void debugger::addPhysicsData(std::string data)
{
	std::string timeStamp = "\n[" + std::to_string(this->getTimeStamp()) + "] : "; //add timestamp to data input
	this->physicsData += timeStamp;
	this->physicsData += data;
}

void debugger::addEntityData(std::string data)
{
	std::string timeStamp = "\n[" + std::to_string(this->getTimeStamp()) + "] : "; //add timestamp to data input
	this->entityData += timeStamp;
	this->entityData += data;
}

void debugger::addEventData(std::string data)
{
	std::string timeStamp = "\n[" + std::to_string(this->getTimeStamp()) + "] : "; //add timestamp to data input
	this->eventData += timeStamp;
	this->eventData += data;

}

void debugger::dumpDatatoFile()
{
	
}

void debugger::flushDebugger()
{
	dumpDatatoConsole();
	dumpDatatoFile();
}

void debugger::dumpDatatoConsole()
{
	this->dataString += this->renderData;
	this->dataString += this->animationData;
	this->dataString += this->modelData;
	this->dataString += this->physicsData;
	this->dataString += this->entityData;
	this->dataString += this->eventData;

	std::cout << this->dataString;
}

float debugger::getTimeStamp()
{
	float currentTime = glfwGetTime();
	return currentTime;
}