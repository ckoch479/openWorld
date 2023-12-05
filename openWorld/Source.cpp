#include <iostream>

#include "SimulationManager.h"


std::string vertex = { "#version 330 core\n"
"layout(location = 0) in vec3 aPos;\n"
"layout(location = 1) in vec3 aColor;\n"
"out vec3 FragPos;\n"
"void main()\n"
"{\n"
"FragPos = aColor;\n"
"gl_Position = vec4(aPos, 1.0);\n"
"};\n" };

std::string fragment{ "#version 330 core\n"
"out vec4 FragColor;\n"

"in vec3 FragPos;\n"

"void main()\n"
"{\n"
"FragColor = vec4(FragPos, 1.0);\n"
"};\n" };

int main()
{
	
	SimulationManager newSimulation;
	newSimulation.Init();

	newSimulation.run();

	newSimulation.shutDown();

	return 0;
}