#include "SimulationManager.h"
#include "testingBoxMeshFunctions.h"

void SimulationManager::Init()
{
	this->state = startup;
	//run platform detection
	
	//init glfw/glut
	//create window	
	this->WindowManager = new windowManager;

	this->WindowManager->setScreenSize(this->SCR_WIDTH,this->SCR_WIDTH);

	this->Debug = new debugger;
	std::string dString = "Game Initializing";
	this->Debug->addEventData(dString);

	this->gameRenderer = new renderer;
	dString = "render initialized!";
	this->Debug->addEventData(dString);
	this->Debug->addRenderer(this->gameRenderer);

	this->sceneObj = new scene;
	dString = "sceneObj initialized!";
	this->Debug->addEventData(dString);

	this->world = new PhysicsWorld;
	dString = "physicsWorld initialized!";
	this->Debug->addEventData(dString);

	this->worldManager = new worldObjectManager(this->Debug);
	

	this->state = active;
	this->subState = mainMenu;
	dString = "gameState changed to active substate changed to mainMenu";
	this->Debug->addEventData(dString);

	loadAnimations();
};

void SimulationManager::shutDown()
{
	
}


void SimulationManager::run() 
{
	ID MeshID, TransformID;

	Shader* lightShader = ResourceManager::loadShader("Shaders/lightShader.vs", "Shaders/lightShader.fs", nullptr, "lightShader");
	Shader* depthShader = ResourceManager::loadShader("Shaders/shadowShader.vs", "Shaders/shadowShader.fs", nullptr, "depthShader");
	Shader* debugDepthQuad = ResourceManager::loadShader("Shaders/debugDepthQuad.vs", "Shaders/debugDepthQuad.fs", nullptr, "depthQuad");
	Shader* animationShader = ResourceManager::loadShader("Shaders/animationShader.vs", "Shaders/animationShader.fs", nullptr, "animShader");
	Shader* lightAnimShader = ResourceManager::loadShader("Shaders/LightAndAnimationShader.vs","Shaders/LightAndAnimationShader.fs",nullptr,"lightAnimshader");
	
	this->sceneObj->setDirectionalLight(glm::vec3(-1.0f, -1.0f, -0.5f), glm::vec3(0.1, 0.1, 0.1), glm::vec3(0.4, 0.4, 0.5), glm::vec3(0.3, 0.3, 0.3));

	Level level1;
	level1.setLevelScene(this->sceneObj);
	level1.setLevelModel("resources/Terrain/hangarScene.gltf");
	level1.renderMap(lightShader);
	
	//create main camera, as of right now only one camera is allowed per scene
	Camera newCamera(glm::vec3(0.0f, 2.0f, 3.0f),0,0);
	this->sceneObj->setCamera(&newCamera);

	//add depth and debug shaders to the scene/renderer for shadows, these will be refactored later for better code, was mainly attempting to test dynamic shadows
	this->sceneObj->setDepthShader(depthShader);
	this->gameRenderer->setDebugDepthQuadShader(debugDepthQuad);


	//player data
	renderContext playerContext(animationShader, this->sceneObj, &newCamera);
	Model* playerModel = ResourceManager::getModel("playerModel");
	player newPlayer(playerContext, playerModel, this->WindowManager, this->world);

	//this will be done differently later however for now all entities will be passed in like so until i decide exactly how i want to impliment loading in data that isnt hard coded 
	//(maybe custom file types?)
	Entity* playerEntity = &newPlayer;
	this->worldManager->addWorldEntity("player", playerEntity);

	//create an item for testing the inventory system

	Model* gunModel = ResourceManager::loadModel("resources/Assets/1911Edit.gltf", "handGun");
	oneHandedRangedWeapon newWeapon(glm::vec3(0.0,0.0,0.0),glm::quat(1.0,0.0,0.0,0.0),glm::vec3(0.01),"handGun", gunModel, lightShader);
	item* weaponPtr = &newWeapon;
	//add this item to the player for testing
	newPlayer.equipItem(weaponPtr);


	this->state = debug; //game state overwrite for testing

	//main loop this will start on the game menu and and such
	//game loop and refresh/rendering loop is controlled here, actual rendering is done with the renderer
	//plan is to have this section actually start as the game menu/ how the game would start up normally and the debug state is so i can jump directly to certain portions
	while (this->state == active)
	{
		setDeltaTime(); //update deltaTime for this loop
		
	
		if(this->WindowManager->checkKey(342))
		{
			//left alt
			this->WindowManager->enableCursor();
		}

		if (this->WindowManager->checkKey(341)) 
		{	//left ctrl
			this->WindowManager->disableCursor();
		}

		//update physics
		accumulator += deltaTime;
		while(accumulator >= timestep)
		{
			this->world->stepSimulation(this->deltaTime);
			accumulator -= timestep;
		}
		
		//draw contents to actual game window
		this->gameRenderer->drawScene(this->sceneObj);

		//shutdown key check (esc)----------------------------
		if(this->WindowManager->checkKey(256))
		{
			this->state = shutdown;
		}

		//----------------------------------------------------
		this->WindowManager->pollWindowEvents();
	}

	//jump directly into gameplay with player movement and such
	while(state == debug)
	{
		this->Debug->updateDebugger();

		setDeltaTime(); //update deltaTime for this loop

		if (this->WindowManager->checkKey(342)) //left alt
		{
			this->gameRenderer->setDebugLines(false);
		}
		if (this->WindowManager->checkKey(341))//left ctrl
		{
			this->gameRenderer->setDebugLines(true);
		}


		//update physics
		accumulator += deltaTime;
		while (accumulator >= timestep)
		{
			this->world->stepSimulation(this->deltaTime);
			accumulator -= timestep;
		}

		//draw contents to actual game window
		this->worldManager->update(deltaTime);
		this->world->debugOBBs(this->gameRenderer);
		this->gameRenderer->drawScene(this->sceneObj);

		//shutdown key check (esc)----------------------------
		if (this->WindowManager->checkKey(256))
		{
			this->state = shutdown;
		}

		//----------------------------------------------------
		this->WindowManager->pollWindowEvents();
		
	}

	//Game/Window shutdown check
	if (this->state != active && this->state != pause) //if the game is not running or paused shutdown
	{
		this->state = shutdown;
	}

}


void SimulationManager::setDeltaTime() //frame time
{
	float currentFrame = glfwGetTime();
	this->deltaTime = currentFrame - lastFrame;
	this->lastFrame = currentFrame;
	
}

//this function preloads animations that are available for use for all humanoid models, thank you mixamo for the animations for testing, you are appreciated greatly
void SimulationManager::loadAnimations()
{
	ResourceManager::loadModel("resources/player/playerEdit.gltf", "playerModel");

	ResourceManager::loadAnimation("resources/player/animations/idle.gltf", "idle", "playerModel");

	ResourceManager::loadAnimation("resources/player/animations/walking.gltf", "walkForward", "playerModel");

	ResourceManager::loadAnimation("resources/player/animations/jogging.gltf", "jogForward", "playerModel");

	ResourceManager::loadAnimation("resources/player/animations/jump.gltf", "jump", "playerModel");

	//ResourceManager::loadAnimation("resources/player/animations/idle.gltf", "crouch", "playerModel");
	ResourceManager::loadAnimation("resources/player/animations/pistolAim.gltf", "aimPistol", "playerModel");

	ResourceManager::loadAnimation("resources/player/animations/pistolWalkForward.gltf", "aimWalkForward", "playerModel");
	ResourceManager::loadAnimation("resources/player/animations/pistolWalkBackwards.gltf", "aimWalkBack", "playerModel");
	ResourceManager::loadAnimation("resources/player/animations/aimingStrafeLeft.gltf", "aimWalkLeft", "playerModel");
	ResourceManager::loadAnimation("resources/player/animations/aimingStrafeRight.gltf", "aimWalkRight", "playerModel");


}

//this below is a rough idea of what i initally thought i wanted to impliment keeping it here to see how far ive come
// 
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