#pragma once

#include <iostream>

#include "glad/glad.h"
#include "GLFW/glfw3.h"


#ifndef PROGRAMTIMER_H
#define PROGRAMTIMER_H

class programTimer
{
public:

	programTimer() { currentTime = 0; currentTick = 0; ticksPerSecond = 1000; }; //default constructor

	~programTimer() {}; //default destructor

	static void updateTimer() //updates the current time based on the glfw get time method then sets the current tick count
	{
		lastTime = currentTime;
		currentTime = glfwGetTime();//get time in seconds

		double timeDiff = currentTime - lastTime;
		timeDiff = timeDiff * ticksPerSecond; //amount of ticks between last update and this update
		currentTick += (int)timeDiff; //add the difference in ticks to the current tick timer
	}

	static unsigned int getCurrentTick() //returns an unsigned int with the current tick count from the start of the application
	{
		return currentTick;
	}

	static void changeTicksPerSecond(int& newValue)
	{
		ticksPerSecond = newValue;
	}

private:
	
	static double currentTime;
	static double lastTime;

	static unsigned int currentTick;

	static int ticksPerSecond;

};

#endif