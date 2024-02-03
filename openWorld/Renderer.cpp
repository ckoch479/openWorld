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
	this->window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "openWorld", NULL, NULL);
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

	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetErrorCallback(errorCallback);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glEnable(GL_DEPTH_TEST);

	this->animator = new Animator;

}

Renderer::Renderer() 
{

}

void Renderer::drawWindow(Scene* scene, float dt)
{
		
		glClearColor(0.30f, 0.30f, 0.60f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

		//create a loop that renders each instance stored in the scene
		for(unsigned int i = 0; i < scene->InstanceCount; i++)
		{
			//iterate through each instance and render its parts
			ID* instanceID = &scene->InstanceIDs[i];
			Instance* currentInstance = &scene->Instances.lookup(*instanceID);
			RenderModel* model = &scene->Models.lookup(currentInstance->ModelID);

			model->Modelshader->use();

			//set up current transforms for this instance 
			setTransforms(currentInstance->TransformID, *scene, *model->Modelshader);

			//set up animation matrix uniforms
			//animation handling--------------------------------------------------------------------
			if (model->hasActiveAnimation != true)
			{
				for (int j = 0; j < 100; j++)
				{
					model->Modelshader->setMat4("finalBonesMatrices[" + std::to_string(j) + "]", glm::mat4(1.0f));
				}
			}
			else if (model->hasActiveAnimation == true)
			{
				animator->setCurrentAnimation(&scene->animations.lookup(model->animationID), model);

				animator->updateCurrentAnimation(dt, scene->animations.lookup(model->animationID).currentPoint);
				//do math for the animation
				std::vector <glm::mat4> finalAnimationMatrix = animator->returnFinalMatrices();

				for (int matrixCounter = 0; matrixCounter < 100; matrixCounter++)
				{
					model->Modelshader->setMat4("finalBonesMatrices[" + std::to_string(matrixCounter) + "]", finalAnimationMatrix[matrixCounter]);
				}
			}

			//set up scene lighting
			model->Modelshader->setVec3("viewPos", scene->MainCamera->CameraPosition);
			model->Modelshader->setFloat("material.shininess", 132.0f);
			//point Lights
			for (unsigned int i = 0; i < scene->numPointLights; i++)
			{
				setPointLightUniform(scene->pointLights.lookup(scene->pointLightIDs[i]), *model->Modelshader, i);
			}

			if (scene->numPointLights < 4 && scene->numPointLights >= 1) //shader needs all lighting uniforms to be filled so fill the empty uniforms with the same light
			{
				for (unsigned int pointLightCounter = scene->numPointLights; pointLightCounter < 4; pointLightCounter++)
				{
					setPointLightUniform(scene->pointLights.lookup(scene->pointLightIDs[0]), *model->Modelshader, pointLightCounter);
				}
			}
			//Spot lights
			setSpotLightUniforms(scene->spotLights.lookup(scene->spotLightID), *model->Modelshader);

			//directional Lights
			setDirectionalLightUniform(scene->directionalLights.lookup(scene->directionLightID), *model->Modelshader);


			//set up current Model and mesh data for this instance
			for(int meshes = 0; meshes < model->renderMeshIDs.size(); meshes++)
			{
				RenderMesh* mesh = &scene->Meshes.lookup(model->renderMeshIDs[meshes]);

				glBindVertexArray(mesh->MeshVAO);

				//textures
				if (mesh->hasDiffuseTextures == true)
				{
					glActiveTexture(GL_TEXTURE0);
					mesh->meshDiffuseTextures[0]->bind();
				}

				if (mesh->hasSpecularTextures == true)
				{
					glActiveTexture(GL_TEXTURE1);
					mesh->meshSpecularTextures[0]->bind();
				}

				glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(mesh->IndexCount), GL_UNSIGNED_INT, 0);

				//glDrawArrays(GL_TRIANGLES, 0, 100000);
				glBindVertexArray(0);
			}

			
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

void Renderer::setTransforms(ID transformID, Scene& currentScene,Shader& shader)
{
	glm::mat4 model(1.0f);
	glm::mat4 view(1.0f);
	glm::mat4 projection(1.0f);

	model = glm::translate(model, currentScene.Transforms.lookup(transformID).Translation); //translate mesh

	model * glm::toMat4(currentScene.Transforms.lookup(transformID).rotation);//rotate mesh

	model *= glm::toMat4(currentScene.Transforms.lookup(transformID).rotation);

	model = glm::scale(model, currentScene.Transforms.lookup(transformID).Scale);//scale mesh

	view = currentScene.MainCamera->GetViewMatrix();
	projection = glm::perspective(glm::radians(currentScene.MainCamera->Zoom), ((float)SCR_WIDTH / (float)SCR_HEIGHT), 0.1f, 100.0f);
	shader.setMat4("modelMatrix", model);
	shader.setMat4("view", view);
	shader.setMat4("projection", projection);
}

void Renderer::setPointLightUniform(Pointlight light, Shader& shader, int iter)
{
	shader.setVec3("pointLights[" + std::to_string(iter) + "].position" , light.position);
	shader.setVec3("pointLights[" + std::to_string(iter) + "].ambient", light.ambient);
	shader.setVec3("pointLights[" + std::to_string(iter) + "].diffuse", light.diffuse);
	shader.setVec3("pointLights[" + std::to_string(iter) + "].specular", light.specular);
	shader.setFloat("pointLights[" + std::to_string(iter) + "].constant", light.constant);
	shader.setFloat("pointLights[" + std::to_string(iter) + "].linear", light.linear);
	shader.setFloat("pointLights[" + std::to_string(iter) + "].quadratic", light.quadratic);
}

void Renderer::setDirectionalLightUniform(DirectionalLight light, Shader& shader)
{
	shader.setVec3("dirLight.direction", light.direction);
	shader.setVec3("dirLight.ambient", light.ambient);
	shader.setVec3("dirLight.diffuse", light.diffuse);
	shader.setVec3("dirLight.specular", light.specular);
}

void Renderer::setSpotLightUniforms(SpotLight light, Shader& shader)
{
	shader.setVec3("spotLight.position", light.position);
	shader.setVec3("spotLight.direction", light.direction);
	shader.setVec3("spotLight.ambient", light.ambient);
	shader.setVec3("spotLight.diffuse", light.diffuse);
	shader.setVec3("spotLight.specular", light.specular);
	shader.setFloat("spotLight.constant", light.constant);
	shader.setFloat("spotLight.linear", light.linear);
	shader.setFloat("spotLight.quadratic", light.quadratic);
	shader.setFloat("spotLight.cutOff", light.cutoff);
	shader.setFloat("spotLight.outerCutOff", light.outerCutoff);
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

