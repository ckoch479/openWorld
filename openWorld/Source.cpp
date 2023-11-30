#include <iostream>

#include "Renderer.h"
#include "Scene.h"

Renderer* render = new Renderer;
Scene scene;


std::string vertex = { "#version 330 core\n"
"layout(location = 0) in vec3 aPos;\n"
"layout(location = 1) in vec3 aColor;\n"

"out vec3 FragPos;\n"

"void main()\n"
"{\n"
"FragPos = aColor;\n"


"gl_Position = vec4(FragPos, 1.0);\n"
"};\n" };

std::string fragment{ "#version 330 core\n"
"out vec4 FragColor;\n"

"in vec3 fragPos;\n"

"void main()\n"
"{\n"
"FragColor = vec4(fragPos, 1.0);\n"
"};\n" };

int main()
{
	
	ID MeshID,TransformID;

	std::vector <glm::vec3> positions {glm::vec3(-0.5,-0.5,0.0),glm::vec3(0.5,-0.5,0.0),glm::vec3(0.0,0.5,0.0)};
	std::vector <glm::vec3> colors { glm::vec3(1,0,0),glm::vec3(0,1,0),glm::vec3(0,0,1) };

	render->init();

	Shader newShader("Shaders/3.3.shader.vs","Shaders/3.3.shader.fs");
	//Shader newShader(vertex, fragment);

	scene.DebugFunction();
	

	MeshID = scene.createMesh(positions,colors, newShader);
	TransformID = scene.createTransform(glm::vec3(1.0,1.0,1.0),glm::vec3(0.0, 1.0, 0.0),glm::quat(),glm::vec3(1.0, 1.0, 1.0));
	scene.AddInstance(MeshID,TransformID);

	
	scene.DebugFunction();
	
	render->drawWindow(&scene);
	scene.DebugFunction();

	return 0;
}