#include "debugger.h"

debugger::debugger()
{

}

debugger::~debugger()
{

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