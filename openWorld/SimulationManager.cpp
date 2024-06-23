#include "SimulationManager.h"
#include "testingBoxMeshFunctions.h"

void SimulationManager::Init()
{
	this->state = startup;
	//run platform detection
	
	//init glfw/glut
	//create window	
	this->WindowManager = new windowManager;

	this->renderer = new Renderer;
	renderer->init(this->WindowManager->getCurrentWindow());
	
	this->scene = new Scene;
	scene->Init();

	this->world = new PhysicsWorld;

	this->state = running;
};

void SimulationManager::shutDown()
{
	
}

void SimulationManager::run() 
{
	ID MeshID, TransformID;

	Shader newShader("Shaders/3.3.shader.vs", "Shaders/3.3.shader.fs"); //simple no texture/mesh shader
	Shader Arissashader("Shaders/ModelShader.vs","Shaders/ModelShader.fs"); //simple mesh and texture shader
	Shader AnimationShader("Shaders/AnimationShader.vs", "Shaders/AnimationShader.fs"); //mesh, texture, and skeletal animation shader
	Shader LightShader("Shaders/PhongLightShader.vs", "Shaders/PhongLightShader.fs"); //simple mesh and light shader
	Shader LightAnimShader("Shaders/LightAndAnimationShader.vs", "Shaders/LightAndAnimationShader.fs"); //simple light, mesh, texture and animation shader
	Shader testShader("Shaders/PhysicsTestShader.vs","Shaders/PhysicsTestShader.fs");
	Shader cubeMap("Shaders/cubeMap.vs", "Shaders/cubeMap.fs");
	Shader lineShader("Shaders/lineShader.vs","Shaders/lineShader.fs");
	//Game objects go here for testing independent parts of the engine--------------------------------------

	//object physics data

	player newPlayer; //rendering glitch with textures may be due to shader uniforms need to be cleared on some version of opengl or they will remain there

	newPlayer.LoadPlayerModel("resources/Arissa/Arissa.dae", "Arissa", this->scene, this->world, LightAnimShader);
	
	newPlayer.AddAnimationtoPlayer("resources/Arissa/ArissaAnimations/idle.dae", "idle");
	newPlayer.AddAnimationtoPlayer("resources/Arissa/ArissaAnimations/Jogging.dae", "jog");
	newPlayer.AddAnimationtoPlayer("resources/Arissa/ArissaAnimations/StandardRun.dae", "run");

	newPlayer.setCurrentAnimation("idle");
	newPlayer.setMovementSpeed(5);

	GameObject newObject;
	newObject.LoadObjectFromFile("resources/Assets/badCrate.obj", "crate");
	
	GameObject newObject2;
	newObject2.LoadObjectFromFile("resources/Assets/badCrate.obj", "crate2");

	newObject.addObjectToScene(LightShader, this->scene, this->world);
	newObject2.addObjectToScene(LightShader, this->scene, this->world);

	//worldMap newMap;
	//newMap.GenerateMap("resources/Terrain/flatBox1.obj", "map", this->scene, LightShader);
	//newMap.GenerateMap("resources/Terrain/terrainobj.obj", "map", this->scene, LightShader);
	//newMap.GenerateMap("resources/Terrain/flatForest.obj", "map", this->scene, LightShader);
	//newMap.addMaptoPhysicsWorld(this->world);

	std::vector <std::string> cubeMapPaths
	{
		/*"resources/skybox/right.jpg",
		"resources/skybox/left.jpg",
		"resources/skybox/top.jpg",
		"resources/skybox/bottom.jpg",
		"resources/skybox/front.jpg",
		"resources/skybox/back.jpg"*/
		"resources/darkSkyTexture.png",
		"resources/darkSkyTexture.png",
		"resources/darkSkyTexture.png",
		"resources/darkSkyTexture.png",
		"resources/darkSkyTexture.png",
		"resources/darkSkyTexture.png"

	};

	scene->createCubeMap(cubeMapPaths, &cubeMap);
	
	
	//create lights for the scene
	scene->createDirectionalLight(glm::vec3(0.2f, -1.0f, 0.3f), glm::vec3(0.01f, 0.01f, 0.01f), glm::vec3(0.04f, 0.04f, 0.04f), glm::vec3(0.05f, 0.05f, 0.05f));

	scene->createPointLight(glm::vec3(8.0,3,0.2), glm::vec3(0.00f, 0.00f, 0.00f), glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(1.0f, 1.0f, 1.0f), 1.0f, 0.09f, 0.032f);
	scene->createPointLight(glm::vec3(13, 2, 5), glm::vec3(0.05f, 0.05f, 0.05f), glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(1.0f, 1.0f, 1.0f), 1.0f, 0.09f, 0.032f);
	scene->createPointLight(glm::vec3(14, 5, 1), glm::vec3(0.05f, 0.05f, 0.05f), glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(1.0f, 1.0f, 1.0f), 1.0f, 0.09f, 0.032f);
	scene->createPointLight(glm::vec3(10, 1, 13), glm::vec3(0.05f, 0.05f, 0.05f), glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(1.0f, 1.0f, 1.0f), 1.0f, 0.09f, 0.032f);

	scene->createSpotLight(glm::vec3(-76,20,0), glm::vec3(0.0,-1.0,0.0), glm::vec3(0.90), glm::vec3(0.90), glm::vec3(0.60),1.0f,0.09f,0.032f, glm::cos(glm::radians(12.5f)), glm::cos(glm::radians(22.0f)));

	//reactPhysics3D test area
	unsigned int worldID,objectID,objectID2;
	std::vector <glm::vec3> objectVertices = newObject.getObjectVertices();
	objectID = this->world->createRigidBody(glm::vec3(0, 3, 0), glm::quat(1.0,0,0,0.0f), 10.0f, newObject.getObjectVertices(),Dynamic);
	
	objectID2 = this->world->createRigidBody(glm::vec3(0, 3, 0),glm::quat(1.0,0,0,0.0f),10.0f,newObject2.getObjectVertices(),Dynamic);

	//std::vector <glm::vec3> worldVerts = newMap.getVertices();
	//std::vector <unsigned int> worldIndices = newMap.getIndices();

	//worldID = this->world->createRigidBody(glm::vec3(0.0f,0.0f,0.0f),glm::quat(1.0, 0, 0, 0.0f),100,worldVerts, Static);
	//worldID = this->world->createConcaveRigidbody(glm::vec3(0.0f),glm::quat(),newMap.getVertices(),newMap.getIndices());

	unsigned int playerId;
	//newPlayer.setPosition(glm::vec3(0, 1, 0));
	playerId = this->world->createCapsuleShape(newPlayer.GetCurrentPosition(), glm::quat(1.0, 0.0, 0.0, 0.0f), 50, 0.6, 1.5, Dynamic);

	float lastHeight = 1;
	this->world->changeBodyFriction(playerId, 0.5);
	this->world->lockBodyRotationAxis(playerId, glm::vec3(0, 0, 0));
	this->world->changeColliderOrigin(playerId, glm::vec3(0, 1.4, 0));

	Level level1;

	level1.setLevelScene(this->scene);
	level1.setLevelPhysicsWorld(this->world);
	
	level1.setLevelModel("resources/Terrain/flatForest.obj");
	level1.renderMap(&LightShader);

	thirdPersonCamera playerCamera;
	float pitch = 0, yaw = 0;

	//game loop and refresh/rendering loop is controlled here, actual rendering is done with the renderer
	while (this->state == running)
	{
		

		setDeltaTime(); //update deltaTime for this loop
		checkMouse();

		newObject.setPosition(this->world->getBodyPosition(objectID));
		newObject.setOrientation(this->world->getBodyRotation(objectID));

		newObject2.setPosition(this->world->getBodyPosition(objectID2));
		newObject2.setOrientation(this->world->getBodyRotation(objectID2));


		newPlayer.setPosition(this->world->getBodyPosition(playerId));
		this->playerPosition = newPlayer.GetCurrentPosition();

		if (!WindowManager->getCursorStatus()) {
			////camera ----------------------------------------------------
			float horizontalFromPlayer = radius * cos(cameraPitch);
			float verticalDistance = radius * sin(cameraPitch);
			this->cameraYaw = 180 - this->playerRotation + this->cameraFreeRotationAngle;
			float Xoffset = horizontalFromPlayer * sin(this->playerRotation + cameraFreeRotationAngle);
			float Zoffset = horizontalFromPlayer * cos(this->playerRotation + cameraFreeRotationAngle);
			this->CameraPosition.x = this->playerPosition.x - Xoffset;
			this->CameraPosition.y = this->playerPosition.y + verticalDistance;
			this->CameraPosition.z = this->playerPosition.z - Zoffset;
			////-----------------------------------------------------------

			newPlayer.setPlayerYaw(this->playerRotation);

			//set camera position
			//this needs to be fixed is incorrect and pitch/yaw have 0 effect on the actual camera object
			this->scene->setCameraPosition(this->playerPosition + glm::vec3(0, 1.5, 0), this->CameraPosition, this->cameraPitch, this->cameraYaw);
		}
		//world collision

		// set player movement
		if (!this->WindowManager->checkKey(87)) 
		{
			newPlayer.setCurrentAnimation("idle");
		}
		
		if(this->WindowManager->checkKey(87) && !this->WindowManager->checkKey(340))
		{
			newPlayer.setCurrentAnimation("jog");
			this->world->changeBodyVelocity(playerId, 4.0f * newPlayer.getPlayerFront());
		}

		if (this->WindowManager->checkKey(87) && this->WindowManager->checkKey(340))
		{
			newPlayer.setCurrentAnimation("run");
			this->world->changeBodyVelocity(playerId, 8.0f * newPlayer.getPlayerFront());
		}

		if (this->WindowManager->checkKey(83))
		{
			this->world->changeBodyVelocity(playerId, 4.0f * -newPlayer.getPlayerFront());
		}

		if (this->WindowManager->checkKey(65))
		{
			this->world->changeBodyVelocity(playerId, 4.0f * -newPlayer.getPlayerRight());
		}

		if (this->WindowManager->checkKey(68))
		{
			this->world->changeBodyVelocity(playerId, 4.0f * newPlayer.getPlayerRight());
		}

		if (this->WindowManager->checkKey(32))
		{
			this->world->addForceToBody(playerId,70.0f * newPlayer.getPlayerUp());
		}

		if(this->WindowManager->checkKey(342))
		{
			//left alt
			this->WindowManager->enableCursor();
		}

		if (this->WindowManager->checkKey(341)) 
		{
			this->WindowManager->disableCursor();
		}
	
		newPlayer.renderPlayer(this->deltaTime, this->scene, this->world);
	
		newObject.updateTransforms(this->scene, this->world);
		newObject2.updateTransforms(this->scene, this->world);
		

		//update physics
		accumulator += deltaTime;
		while(accumulator >= timestep)
		{
			this->world->stepSimulation(this->deltaTime);
			accumulator -= timestep;
		}
		
		
		//draw contents to actual game window
		this->renderer->drawWindow(this->scene,this->deltaTime);

		//shutdown key check (esc)----------------------------
		if(this->WindowManager->checkKey(256))
		{
			this->state = shutdown;
		}
		//----------------------------------------------------
		this->WindowManager->pollWindowEvents();
	}

	if (this->state != running && this->state != pause) //if the game is not running or paused shutdown
	{
		//this->renderer->shutDown();
		this->state = shutdown;
	}

}

void SimulationManager::checkMouse() 
{
	
	double mouseX, mouseY;
	glfwGetCursorPos(this->WindowManager->getCurrentWindow(), &mouseX, &mouseY); //poll the window for the current mouse position

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

	//this->scene->MouseAimCamera(xoffset, yoffset); //using the x and y offsets aim the camera
	
	// value between 0-360 for camera
	//camera needs to be 5 away from the player at center

	this->cameraPitch += yoffset * 0.01;

	if (!glfwGetMouseButton(this->WindowManager->getCurrentWindow(), GLFW_MOUSE_BUTTON_RIGHT))
	{
		this->playerRotation += xoffset * 0.01;
	}

	//std::cout << "player rotation " << playerRotation << std::endl;

	if (glfwGetMouseButton(this->WindowManager->getCurrentWindow(), GLFW_MOUSE_BUTTON_RIGHT))
	{
		this->cameraFreeRotationAngle += xoffset * 0.01;
	}

	if (cameraPitch > 89.0f)
	{
		cameraPitch = 89.0f;
	}		
	if (cameraPitch < -89.0f)
	{
		cameraPitch = -89.0f;
	}

	/*if (cameraYaw > 360.0f)
	{
		this->cameraFreeRotationAngle = 360.0f;
	}
	if (cameraYaw < -360.0f)
	{
		this->cameraFreeRotationAngle = -360.0f;
	}*/


}

void SimulationManager::setDeltaTime() 
{
	float currentFrame = glfwGetTime();
	this->deltaTime = currentFrame - lastFrame;
	this->lastFrame = currentFrame;
	
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