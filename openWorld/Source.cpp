#include <iostream>

#include "ResourceManager.h"


int main()
{

	std::cout << "Hello World!\n";

	ResourceManager manager;


	std::string filepath;
	filepath = "resources/Arissa@Jump.glb";

	manager.loadMesh(filepath);


	return 0;
}