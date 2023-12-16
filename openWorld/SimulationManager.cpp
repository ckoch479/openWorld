#include "SimulationManager.h"

void SimulationManager::Init()
{
	this->state = startup;
	//run platform detection
	//init glfw/glut
	//create window
	
	this->renderer = new Renderer;
	renderer->init();
	
	this->scene = new Scene;
	scene->Init();

	this->state = running;
};

void SimulationManager::run() 
{
	ID MeshID, TransformID;

	Shader newShader("Shaders/3.3.shader.vs", "Shaders/3.3.shader.fs"); //simple no texture/mesh shader
	Shader Arissashader("Shaders/ModelShader.vs","Shaders/ModelShader.fs"); //simple mesh and texture shader
	Shader AnimationShader("Shaders/AnimationShader.vs", "Shaders/AnimationShader.fs"); //mesh, texture, and skeletal animation shader
	Shader LightShader("Shaders/PhongLightShader.vs", "Shaders/PhongLightShader.fs"); //simple mesh and light shader
	Shader LightAnimShader("Shaders/LightAndAnimationShader.vs", "Shaders/LightAndAnimationShader.fs"); //simple light, mesh, texture and animation shader

	//Animation data testing
	AnimationData* newAnimation = ResourceManager::loadAnimation("resources/vampire/dancing_vampire.dae","dance");

	ModelData* newModel = ResourceManager::loadModel("resources/vampire/dancing_vampire.dae", "vampire");
	ID newModelTransform = scene->createTransform(glm::vec3(0.0, 0.0, -1.0), glm::vec3(0.0, 1.0, 0.0), glm::quat(), glm::vec3(1.0, 1.0, 1.0));
	ID RenderID = scene->createModel(*newModel, LightAnimShader, newAnimation);
	scene->AddInstance(RenderID, newModelTransform);

	/*ModelData* newModel1 = ResourceManager::loadModel("resources/crystal.dae", "crystal");
	ID newModelTransform1 = scene->createTransform(glm::vec3(3.0, 0.0, -1.0), glm::vec3(0.0, 1.0, 0.0), glm::quat(), glm::vec3(0.01, 0.01, 0.01));
	ID RenderID1 = scene->createModel(*newModel1, LightShader);
	scene->AddInstance(RenderID1, newModelTransform1);*/

	/*ModelData* newModel2 = ResourceManager::loadModel("resources/vampire/dancing_vampire.dae", "vampire");
	ID newModelTransform2 = scene->createTransform(glm::vec3(0.0, 3.0, -1.0), glm::vec3(0.0, 1.0, 0.0), glm::quat(), glm::vec3(1.0, 1.0, 1.0));
	ID RenderID2 = scene->createModel(*newModel2, LightAnimShader, newAnimation);
	scene->AddInstance(RenderID2, newModelTransform2);*/

	/*ModelData* newModel3 = ResourceManager::loadModel("resources/vampire/dancing_vampire.dae", "vampire");
	ID newModelTransform3 = scene->createTransform(glm::vec3(3.0, 3.0, -1.0), glm::vec3(0.0, 1.0, 0.0), glm::quat(), glm::vec3(1.0, 1.0, 1.0));
	ID RenderID3 = scene->createModel(*newModel3, LightAnimShader, newAnimation);
	scene->AddInstance(RenderID3, newModelTransform3);*/


	//create lights for the scene
	scene->createDirectionalLight(glm::vec3(-0.2f, -1.0f, -0.3f), glm::vec3(0.05f, 0.05f, 0.05f), glm::vec3(0.4f, 0.4f, 0.4f), glm::vec3(0.5f, 0.5f, 0.5f));

	scene->createPointLight(glm::vec3(8.0,3,0.2), glm::vec3(0.05f, 0.05f, 0.05f), glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(1.0f, 1.0f, 1.0f), 1.0f, 0.09f, 0.032f);

	scene->createPointLight(glm::vec3(13, 2, 5), glm::vec3(0.05f, 0.05f, 0.05f), glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(1.0f, 1.0f, 1.0f), 1.0f, 0.09f, 0.032f);
	scene->createPointLight(glm::vec3(14, 5, 1), glm::vec3(0.05f, 0.05f, 0.05f), glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(1.0f, 1.0f, 1.0f), 1.0f, 0.09f, 0.032f);
	scene->createPointLight(glm::vec3(10, 1, 13), glm::vec3(0.05f, 0.05f, 0.05f), glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(1.0f, 1.0f, 1.0f), 1.0f, 0.09f, 0.032f);

	scene->createSpotLight(glm::vec3(-1.0), glm::vec3(-1.0,-1.0,-1.0), glm::vec3(0.020), glm::vec3(0.020), glm::vec3(0.050),1.0f,0.09f,0.032f, glm::cos(glm::radians(12.5f)), glm::cos(glm::radians(15.0f)));

	//game loop and refresh/rendering loop is controlled here, actual rendering is done with the renderer
	while (this->state == running)
	{
		if (renderer->checkWindowCloseState())  //check if user closes out of the window
		{
			this->state = shutdown;
			break;
		}

		setDeltaTime(); //update deltaTime for this loop
		checkKeys(); //check for active keys during this loop
		checkMouse();

	
	
	
		//draw contents to actual game window
		this->renderer->drawWindow(this->scene);
		
	}

	if (this->state != running && this->state != pause) //if the game is not running or paused shutdown
	{
		this->renderer->shutDown();
	}

}

void SimulationManager::checkKeys() 
{
	int state = glfwGetKey(this->renderer->getWindow(), GLFW_KEY_W);
	if(state == GLFW_PRESS)
	{
		this->scene->MoveCamera(FORWARD, this->deltaTime);
		state = GLFW_RELEASE;
	}

	state = glfwGetKey(this->renderer->getWindow(), GLFW_KEY_A);
	if (state == GLFW_PRESS)
	{
		this->scene->MoveCamera(LEFT, this->deltaTime);
		state = GLFW_RELEASE;
	}

	state = glfwGetKey(this->renderer->getWindow(), GLFW_KEY_S);
	if (state == GLFW_PRESS)
	{
		this->scene->MoveCamera(BACKWARD, this->deltaTime);
		state = GLFW_RELEASE;
	}

	state = glfwGetKey(this->renderer->getWindow(), GLFW_KEY_D);
	if (state == GLFW_PRESS)
	{
		this->scene->MoveCamera(RIGHT, this->deltaTime);
		state = GLFW_RELEASE;
	}

	state = glfwGetKey(this->renderer->getWindow(), GLFW_KEY_ESCAPE);
	if(state == GLFW_PRESS)
	{
		this->state = shutdown;
	}

}

void SimulationManager::checkMouse() 
{
	
	double mouseX, mouseY;
	glfwGetCursorPos(this->renderer->getWindow(), &mouseX, &mouseY); //poll the window for the current mouse position

	if (firstMouse == true)
	{
		lastMouseX = mouseX;
		lastMouseY = mouseY;
		firstMouse = false;
	}

	float xoffset = mouseX - this->lastMouseX; //create an offset value from where the mouse last was for relative camera movement
	float yoffset = this->lastMouseY - mouseY;

	this->lastMouseX = mouseX;
	this->lastMouseY = mouseY;

	xoffset *= this->mouseSensitivity;
	yoffset *= this->mouseSensitivity;

	this->scene->MouseAimCamera(xoffset, yoffset); //using the x and y offsets aim the camera
	
}

void SimulationManager::setDeltaTime() 
{
	float currentFrame = glfwGetTime();
	this->deltaTime = currentFrame - lastFrame;
	this->lastFrame = currentFrame;
}

void SimulationManager::shutDown() 
{

}