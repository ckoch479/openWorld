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

	this->gameRenderer = new renderer;
	
	this->sceneObj = new scene;
	

	this->world = new PhysicsWorld;

	this->state = active;
	this->subState = mainMenu;
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
	unsigned int gunId = newManager.createHandGun("resources/Assets/1911Modified.gltf","handGun",10,10);

	//player manager:
	playerManager newPlayer(this->sceneObj,this->world,this->WindowManager,animationShader, lightShader,"resources/player/player.gltf",&newCamera);
	newPlayer.testItemSlots(newManager.getItemPTR(gunId));
	//newPlayer.testItemSlots(newManager.getItemPTR(gunId));

	ShapeGenerator newShaper;

	//shape2D newshape = newShaper.generateCharacter('a', 1, 1, glm::vec4(1.0, 0.0, 1.0, 0.7));
	//shape2D newshape = newShaper.generateBox(0.5, 1, glm::vec4(1.0, 1.0, 1.0, 0.3));
	//shape2D newshape = newShaper.generateCircle(0.01, glm::vec4(1.0,1.0,1.0,0.3), 30);
	//shape2D newshape = newShaper.generateTriangle(1, 1, glm::vec4(1.0, 1.0, 1.0, 0.3));
	shape2D newshape = newShaper.generateCharacter('k', 0.5, 1, glm::vec4(1.0, 1.0, 1.0, 0.7));
	this->sceneObj->add2DScreenShape(newshape, glm::vec2(0, 0));

	//------------------------------------------
	//unsigned int boxId;
	//std::string boxSceneID;
	//transform boxTransform;
	//boxTransform.position = glm::vec3(4, 10, 4);
	//boxTransform.orientation = glm::quat(1.0, 0.0, 0.0, 0.0);
	//boxTransform.scale = glm::vec3(1.0f);

	//transform newObjTransform;
	//newObjTransform.position = glm::vec3(0, 0, 0);
	//newObjTransform.orientation = glm::quat(1.0, 0.0, 0.0, 0.0);
	//newObjTransform.scale = glm::vec3(0.01f);

	//Model* boxModel = ResourceManager::loadModel("resources/Assets/badCrate.obj","badBox");

	//std::vector <glm::vec3> boxVertices;
	//for(unsigned int i = 0 ; i < boxModel->meshes[0].vertices.size(); i++)
	//{
	//	Vertex vertex = boxModel->meshes[0].vertices[i];
	//	boxVertices.push_back(vertex.vertexPosition);
	//}
	//boxSceneID = sceneObj->addObjectToScene(boxModel, boxTransform,lightShader);

	//boxId = this->world->createRigidBody(boxTransform.position, boxTransform.orientation,20 ,boxVertices,Dynamic);
	//this->world->changeColliderOrigin(boxId, glm::vec3(0, -1.0, 0));

	this->state = debug; //game state overwrite for testing

	//main loop this will start on the game menu and and such
	//game loop and refresh/rendering loop is controlled here, actual rendering is done with the renderer
	while (this->state == active)
	{
		setDeltaTime(); //update deltaTime for this loop
		

		/*boxTransform.position = world->getBodyPosition(boxId);
		boxTransform.orientation = world->getBodyRotation(boxId);
		sceneObj->updateTransform(boxSceneID, boxTransform);*/
		
		while(subState == mainMenu)
		{
			//draw background scene
			//draw menu buttons (new,load,settings,credits,exit)
			//track mouseMovement
			//changeGamestate/subState as indicated

		}

		//if(this->WindowManager->checkKey(342))
		//{
		//	//left alt
		//	this->WindowManager->enableCursor();
		//}

		//if (this->WindowManager->checkKey(341)) 
		//{
		//	this->WindowManager->disableCursor();
		//}

		newPlayer.updateManager(deltaTime, &level1);

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


		/*boxTransform.position = world->getBodyPosition(boxId);
		boxTransform.orientation = world->getBodyRotation(boxId);
		sceneObj->updateTransform(boxSceneID, boxTransform);*/


		//if(this->WindowManager->checkKey(342))
		//{
		//	//left alt
		//	this->WindowManager->enableCursor();
		//}

		//if (this->WindowManager->checkKey(341)) 
		//{
		//	this->WindowManager->disableCursor();
		//}

		newPlayer.updateManager(deltaTime, &level1);

		//update physics
		accumulator += deltaTime;
		while (accumulator >= timestep)
		{
			this->world->stepSimulation(this->deltaTime);
			accumulator -= timestep;
		}

		//draw contents to actual game window
		animator::updateAnimations(deltaTime);

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