#include "SimulationManager.h"
#include "testingBoxMeshFunctions.h"

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

	this->world = new PhysicsWorld;

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
	Shader testShader("Shaders/PhysicsTestShader.vs","Shaders/PhysicsTestShader.fs");
	//Game objects go here for testing independent parts of the engine--------------------------------------

	//object physics data

	//temporary meshes for world and physics bodies
	//normals are used for color
	ModelData testModel = createTestModel(glm::vec3(2,0.5,0),glm::vec3(1,1,1), glm::vec3(0.5, 0.1, 0.1));
	ID testModelTransform = scene->createTransform(glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0), glm::quat(0.0, 0, 0.0, 0), glm::vec3(1.0, 1.0, 1.0));
	ID testerID = scene->createModel(testModel,testShader);
	scene->AddInstance(testerID,testModelTransform);


	ModelData worldModel = createTestModel(glm::vec3(0, -0.2, 0), glm::vec3(25, 0.2, 25), glm::vec3(0.1, 0.1, 0.6));
	ID worldModelTransform = scene->createTransform(glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0), glm::quat(0.0, 0, 0.0, 0), glm::vec3(1.0, 1.0, 1.0));
	ID worldID = scene->createModel(worldModel, testShader);
	scene->AddInstance(worldID, worldModelTransform);

	//object rendering data
	AnimationData* newAnimation = ResourceManager::loadAnimation("resources/vampire/dancing_vampire.dae","dance");

	//game object class tester
	GameObject newObject;

	newObject.LoadObjectFromFile("resources/vampire/dancing_vampire.dae", "vampire");
	ID newAnimationID = scene->createAnimation(newAnimation);
	
	newObject.CreateRigidBody(glm::vec3(0,0,-2),glm::quat(), glm::vec3(0,1,0), 10.0f,this->world);
	newObject.AddtoPhysicsWorld(this->world);


	newObject.addObjectToScene(LightAnimShader,scene, this->world);
	newObject.setAnimation(newAnimation, scene);


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

		//update physics
		this->world->stepSimulation(this->deltaTime);
		//newObject.applyForce(glm::vec3(0.0,0.0,0.2),this->world);
		newObject.updateTransforms(this->scene, this->world);

		//testing only remove later
		if (up == true) { newObject.applyForce(glm::vec3(10.0, 0.0, 0.0), this->world); };
		if (down == true) { newObject.applyForce(glm::vec3(-10.0, 0.0, 0.0), this->world); };
		if (left == true) { newObject.applyForce(glm::vec3(0.0, 0.0, 10.0), this->world); };
		if (right == true) { newObject.applyForce(glm::vec3(0.0, 0.0, -10.0), this->world); };
		if (space == true) { newObject.applyForce(glm::vec3(0.0, 10.0, 0.0), this->world); };
	
		//draw contents to actual game window
		this->renderer->drawWindow(this->scene,this->deltaTime);
		
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

	//testing only remove later
	state = glfwGetKey(this->renderer->getWindow(), GLFW_KEY_DOWN);
	if(state == GLFW_PRESS)
	{
		this->down = true;
	}
	if (state == GLFW_RELEASE)
	{
		this->down = false;
	}

	state = glfwGetKey(this->renderer->getWindow(), GLFW_KEY_LEFT);
	if (state == GLFW_PRESS)
	{
		this->left = true;
	}
	if (state == GLFW_RELEASE)
	{
		this->left = false;
	}

	state = glfwGetKey(this->renderer->getWindow(), GLFW_KEY_RIGHT);
	if (state == GLFW_PRESS)
	{
		this->right = true;
	}
	if (state == GLFW_RELEASE)
	{
		this->right = false;
	}

	state = glfwGetKey(this->renderer->getWindow(), GLFW_KEY_SPACE);
	if (state == GLFW_PRESS)
	{
		this->space = true;
	}
	if (state == GLFW_RELEASE)
	{
		this->space = false;
	}

	state = glfwGetKey(this->renderer->getWindow(), GLFW_KEY_UP);
	if (state == GLFW_PRESS)
	{
		this->up = true;
	}
	if (state == GLFW_RELEASE)
	{
		this->up = false;
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

//script testing function idea
//
// setup section (what to load and preform for this level)-------------------------------------------------------------------------
// 
// load model shader
// load light shader
// load map mesh
// load player model
// load player animations
// load dynamic environment objects (boxes,NPCs)
// load lights
// 
// load and create EntityArray
// 
// Add box to scene entity Array (x,y) x10
// Add Agressive NPC (x,y) x 4
// set Enemy AI?
// 
// set Environmental triggers array (x,y,z) 
// 
// end setup section ()---------------------------------------------------------------------------------------
// 
// Active check section
// 
//	check environment triggers array (trigger name, true/false)
// 
//	if(trigger name == true) do trigger action
// 
//  if(player == moving(slow)) set animation walk
//  if(player == moving(medium)) set animation jog
//  if(player == moving(fast)) set animation run
// 
//  keypress checks---------------------------------------------
//  
// if(keypress = space) Apply force +y
// if(keypress = crtl) set Animation Crouch
// if(mouseClick = LMB) set Animation Attack
// if(mouseClick = RMB) set Animation Block
// 
// 
// //collision checks
// 
// if(player == attacking && Collision(nearest enemy) = true) Enemy = die
// if(Enemy == attacking && Collision(player) = true) Player = die
// 
// TerrainHeight = mapCheckHeight(player.x, player.y)
// if(player.y < TerrainHeight) player.y = TerrainHeight
//