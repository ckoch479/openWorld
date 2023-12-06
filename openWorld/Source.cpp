#include <iostream>

#include "SimulationManager.h"


int main()
{
	
	SimulationManager newSimulation;
	newSimulation.Init();

	newSimulation.run();

	newSimulation.shutDown();

	return 0;
}