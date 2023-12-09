#include "Renderer.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

void errorCallback(int error, const char *msg);

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

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glEnable(GL_DEPTH_TEST);

}

Renderer::Renderer() 
{

}

void Renderer::drawWindow(Scene* scene) 
{
		
		glClearColor(0.0f, 0.4f, 0.7f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

		//create a loop that renders each instance stored in the scene
		for(unsigned int i = 0; i < scene->InstanceCount; i++)
		{
			ID* instanceID = &scene->InstanceIDs[i];

			ID* meshID = &scene->Instances.lookup(*instanceID).MeshID;
			ID* transformsID = &scene->Instances.lookup(*instanceID).TransformID;

			RenderMesh* mesh = &scene->Meshes.lookup(*meshID);
			Transform* meshTransforms = &scene->Transforms.lookup(*transformsID);

			//Render this instance--------------------------------------
			// 
			//bind the shader
			mesh->Meshshader->use();
			//bind the mesh VAO
			
			glBindVertexArray(mesh->MeshVAO);

			//set uniform variables
			glm::mat4 model(1.0f);
			glm::mat4 view(1.0f);
			glm::mat4 projection(1.0f);

			model = glm::translate(model, meshTransforms->Translation); //translate mesh
			
			//model = glm::rotate(meshTransforms->rotation, meshTransforms->RotationOrigin);//rotate mesh
			
			model = glm::scale(model, meshTransforms->Scale);//scale mesh

			view = scene->MainCamera->GetViewMatrix();
			projection = glm::perspective(glm::radians(scene->MainCamera->Zoom), ((float)800.0 / (float)600.0), 0.1f, 100.0f);
			mesh->Meshshader->setMat4("modelMatrix", model);
			mesh->Meshshader->setMat4("view", view);
			mesh->Meshshader->setMat4("projection", projection);

			if(mesh->hasTextures == true)
			{
				//mesh->Meshshader->setInt("diffuse_texture0", mesh->meshTextures[0]->id);
				mesh->meshTextures[0]->bind();
				
				
			}

			glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(mesh->IndexCount), GL_UNSIGNED_INT, 0);

			glDrawArrays(GL_TRIANGLES, 0, 100000);
			glBindVertexArray(0);

		}

		glfwSwapBuffers(this->window);
		glfwPollEvents();
		
}

GLFWwindow* Renderer::getWindow() 
{
	return this->window;
}

void Renderer::shutDown() 
{
	glfwTerminate();
}

bool Renderer::checkWindowCloseState() 
{
	if(glfwWindowShouldClose(this->window)) //if the window should close return true
	{
		return true;
	}

	if (!glfwWindowShouldClose(this->window)) //if the window should remain open return false
	{
		return false;
	}
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
