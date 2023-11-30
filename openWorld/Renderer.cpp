#include "Renderer.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

void errorCallback(int error, const char *msg);

void processInput(GLFWwindow* window);

void Renderer::init() 
{
	//init opengl and set opengl version
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//create window object

	this->window = glfwCreateWindow(800, 600, "openWorld", NULL, NULL);
	if(window == NULL)
	{
		std::cout << "Failed to create GLFW window!" << std::endl;
		glfwTerminate();
	}
	glfwMakeContextCurrent(window);
	

	//init glad
	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD!" << std::endl;
	}

	glViewport(0, 0, 800, 600);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetErrorCallback(errorCallback);
}

Renderer::Renderer() 
{

}

void Renderer::drawWindow(Scene* scene) 
{

	while(!glfwWindowShouldClose(this->window))
	{
		processInput(window);

		glClearColor(0.0f, 0.4f, 0.7f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//create a loop that renders each instance stored in the scene
		for(unsigned int i = 0; i < scene->InstanceCount; i++)
		{
			ID* instanceID = &scene->InstanceIDs[i];

			ID* meshID = &scene->Instances.lookup(*instanceID).MeshID;
			ID* transformsID = &scene->Instances.lookup(*instanceID).TransformID;

			Mesh* mesh = &scene->Meshes.lookup(*meshID);
			Transform* meshTransforms = &scene->Transforms.lookup(*transformsID);

			//Render this instance--------------------------------------
			// 
			//bind the shader
			mesh->Meshshader->use();
			//bind the mesh VAO
			glBindVertexArray(mesh->MeshVAO);
			glDrawArrays(GL_TRIANGLES, 0, 9);

			glBindVertexArray(0);

			//std::cout << "renderer loop" << std::endl;

		}


		glfwSwapBuffers(this->window);
		glfwPollEvents();
		
	}

	glfwTerminate();
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void errorCallback(int error, const char* msg) 
{
	std::string s;
	s = " [" + std::to_string(error) + "] " + msg + '\n';
	std::cerr << s << std::endl;
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}