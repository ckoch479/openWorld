#pragma once

#include <iostream>
#include <vector>

#include "renderingInfoDefinitions.h"
#include "animationDataDefinitions.h"
#include "playerActionDefinitions.h"

#include "includes/glm/glm.hpp"
#include "Includes/glm/gtc/type_ptr.hpp"

#include "Renderer.h"

//change to singleton later:
class debugger
{
public:

	debugger();
	~debugger();

	void addModelData(std::string data);

	void addRenderData(std::string data);

	void addAnimationData(std::string data);

	void addPhysicsData(std::string data);

	void addEntityData(std::string data);

	void addEventData(std::string data);

	void flushDebugger();

	void addRenderer(renderer* gameRenderer);

	void updateDebugger();

private:

	void dumpDatatoFile();

	void dumpDatatoConsole();

	float getTimeStamp();

	void drawWorldLines();

	int debugLevel = 0; //how much data will be presented to the programmer 0 = none, 10 = absolutely everything

	std::string dumpFilePath; //filepath to the dat dump file
	std::string dataString; //overall string that is placed in a file or through the console

	std::string modelData;
	std::string animationData;
	std::string renderData;
	std::string physicsData;
	std::string entityData;
	std::string eventData;

	renderer* gameRenderer;
};

