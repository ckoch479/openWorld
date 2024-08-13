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

	this->sceneObj = new scene;
	dString = "sceneObj initialized!";
	this->Debug->addEventData(dString);

	this->world = new PhysicsWorld;
	dString = "physicsWorld initialized!";
	this->Debug->addEventData(dString);
	

	this->state = active;
	this->subState = mainMenu;
	dString = "gameState changed to active substate changed to mainMenu";
	this->Debug->addEventData(dString);
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
	//Shader* physicsDebugShader = ResourceManager::loadShader("Shaders/PhysicsTestShader.vs","Shaders/PhysicsTestShader.fs",nullptr,"physicsDebug");
	//Game objects go here for testing independent parts of the engine--------------------------------------

	this->sceneObj->setDirectionalLight(glm::vec3(-1.0f, -1.0f, -0.5f), glm::vec3(0.1, 0.1, 0.1), glm::vec3(0.4, 0.4, 0.5), glm::vec3(0.3, 0.3, 0.3));

	Level level1;
	level1.setLevelScene(this->sceneObj);
	level1.setLevelPhysicsWorld(this->world);
	level1.setLevelModel("resources/Terrain/citySceneOneModel.gltf");

	

	level1.renderMap(lightShader);

	Camera newCamera(glm::vec3(0.0f, 0.0f, 3.0f));

	this->sceneObj->setCamera(&newCamera);

	this->sceneObj->setDepthShader(depthShader);
	this->gameRenderer->setDebugDepthQuadShader(debugDepthQuad);

	//item testing:
	gameObjectManager newManager;
	unsigned int gunId = newManager.createHandGun("resources/Assets/1911Edit.gltf","handGun",10,10);

	//player manager:
	playerManager newPlayer(this->sceneObj,this->world,this->WindowManager,animationShader, lightShader,"resources/player/playerEdit.gltf",&newCamera);
	newPlayer.testItemSlots(newManager.getItemPTR(gunId));
	
	//npc testing no AI yet:
	npcManager newNPC(this->sceneObj, this->world, animationShader, "resources/NPC/Zombie/zombieHolder.gltf", "swatZombie");

	//Model* gunModel = ResourceManager::loadModel("resources/Assets/1911Edit.gltf", "test gun");

	//transform newTransform;
	//newTransform.position = glm::vec3(0.0f);
	//newTransform.orientation = glm::quat(1.0, 0.0, 0.0, 0.0);
	//newTransform.scale = glm::vec3(0.01f);

	//std::string sceneGunID = this->sceneObj->addObjectToScene(gunModel, newTransform, lightShader);
	/*ShapeGenerator newShaper;
	shape2D newshape = newShaper.generateCharacter('k', 0.5, 1, glm::vec4(1.0, 1.0, 1.0, 0.7));
	newshape.position = glm::vec3(0.1,0.1,0.0f);
	newshape.scale = glm::vec3(0.1f,0.1f,1.0f);
	this->sceneObj->add2DScreenShape(newshape);*/

	//textBox newBox("continue", glm::vec2(0.0, 0.0), glm::vec2(0.3, 0.05),1.5,1.0, glm::vec4(1.0,1.0,1.0,0.3)); //16:1 ratio

	//newBox.letters;

	//for(unsigned int i = 0; i < newBox.letters.size(); i++)
	//{
	//	sceneObj->add2DScreenShape(newBox.letters[i]);
	//}

	this->state = debug; //game state overwrite for testing

	//main loop this will start on the game menu and and such
	//game loop and refresh/rendering loop is controlled here, actual rendering is done with the renderer
	while (this->state == active)
	{
		setDeltaTime(); //update deltaTime for this loop
		
	
		if(this->WindowManager->checkKey(342))
		{
			//left alt
			this->WindowManager->enableCursor();
		}

		if (this->WindowManager->checkKey(341)) 
		{
			this->WindowManager->disableCursor();
		}

		newPlayer.updateManager(deltaTime, &level1);
		newNPC.updateManager(deltaTime, &level1);

		//update physics
		accumulator += deltaTime;
		while(accumulator >= timestep)
		{
			this->world->stepSimulation(this->deltaTime);
			accumulator -= timestep;
		}
		
		//draw contents to actual game window
		animator::updateAnimations(deltaTime);

		this->gameRenderer->drawScene(this->sceneObj);

		//shutdown key check (esc)----------------------------
		if(this->WindowManager->checkKey(256))
		{
			this->state = shutdown;
		}

		//----------------------------------------------------
		this->WindowManager->pollWindowEvents();
	}

	//level editor is active:
	while(state == editor)
	{
		setDeltaTime();


		this->gameRenderer->drawScene(this->sceneObj);

		if (this->WindowManager->checkKey(256))
		{
			this->state = shutdown;
		}

		this->WindowManager->pollWindowEvents();
	}

	//jump directly into gameplay with player movement and such
	while(state == debug)
	{
		
		setDeltaTime(); //update deltaTime for this loop

		if (this->WindowManager->checkKey(342)) //left alt
		{
			this->gameRenderer->setDebugLines(false);
		}
		if (this->WindowManager->checkKey(341))//left ctrl
		{
			this->gameRenderer->setDebugLines(true);
		}

		double x = 0, y = 0;
		this->WindowManager->getMousePosition(&x, &y);

		newPlayer.updateManager(deltaTime, &level1);
		newNPC.updateManager(deltaTime, &level1);

		//newTransform.position = newPlayer.player->getPlayerRelativeTransform()->front + newPlayer.player->getPlayersTransform()->position + glm::vec3(0, 1.5, 0);
		//this->sceneObj->updateTransform(sceneGunID, newTransform);

		//update physics
		accumulator += deltaTime;
		while (accumulator >= timestep)
		{
			this->world->stepSimulation(this->deltaTime);
			accumulator -= timestep;
		}

		//draw contents to actual game window
		animator::updateAnimations(deltaTime);

		glm::vec3 playerPos = newPlayer.player->getPlayersTransform()->position;
		this->sceneObj->setFocusPos(playerPos);

		this->gameRenderer->addCube(playerPos + glm::vec3(0,1,0), newPlayer.player->getPlayersTransform()->orientation, glm::vec3(0.7, 1.6, 0.7), glm::vec4(1.0, 0.0, 0.0, 0.4));
		this->gameRenderer->addCube(glm::vec3(4.0f, 2.0f, 2.0f), glm::quat(1.0f, 0.0, 0.0, 0.0), glm::vec3(1.0f), glm::vec4(1.0, 0.0, 1.0, 0.7));
		this->gameRenderer->addCube(glm::vec3(6.0f, 2.0f, 2.0f), glm::quat(1.0f, 0.0, 0.0, 0.0), glm::vec3(1.0f), glm::vec4(0.0, 0.0, 1.0, 0.7));
		this->gameRenderer->addCube(glm::vec3(8.0f, 2.0f, 2.0f), glm::quat(1.0f, 0.0, 0.0, 0.0), glm::vec3(1.0f), glm::vec4(0.0, 1.0, 1.0, 0.7));
		this->gameRenderer->addCube(glm::vec3(10.0f,2.0f, 2.0f), glm::quat(1.0f, 0.0, 0.0, 0.0), glm::vec3(1.0f), glm::vec4(1.0, 0.0, 1.0, 0.7));


		this->gameRenderer->addLine(glm::vec3(0, 1, 0), glm::vec3(15, 1, 0), glm::vec4(1.0, 0.0, 0.0, 1.0));
		this->gameRenderer->addLine(glm::vec3(0, 1, 0), glm::vec3(0, 15, 0), glm::vec4(0.0, 1.0, 0.0, 1.0));
		this->gameRenderer->addLine(glm::vec3(0, 1, 0), glm::vec3(0, 1, 15), glm::vec4(0.0, 0.0, 1.0, 1.0));

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