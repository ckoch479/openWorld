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
};

void SimulationManager::shutDown()
{
	
}

//for debugging purposes
void SimulationManager::playerInputTestFunction(playerEntity* player, windowManager* window)
{
	if (this->WindowManager->checkKey(87)) //w
	{
		player->setPlayerAction(walking);
	};

	if (!this->WindowManager->checkKey(87))
	{
		player->setPlayerAction(idle);
	}

	if (this->WindowManager->checkKey(65)) //a
	{
		player->setPlayerAction(sideWalkLeft);
	};

	if (this->WindowManager->checkKey(83)) //s
	{
		player->setPlayerAction(walkingBack);
	};

	if (this->WindowManager->checkKey(68)) //d
	{
		player->setPlayerAction(sideWalkRight);
	};

	if (this->WindowManager->checkKey(32)) //space
	{
		player->setPlayerAction(jumping);
	}

	if (this->WindowManager->checkKey(258)) //tab
	{
		player->debugAnimations();
	}
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

	Model* gltfModel = ResourceManager::loadModel("resources/Arissa/ArissaGLTF/Arissa.gltf", "gltfTest");
	transform gltfTransform;
	gltfTransform.position = glm::vec3(2, 0, -4);
	gltfTransform.scale = glm::vec3(1.0f);
	gltfTransform.orientation = glm::quat(1.0, 0.0, 0.0, 0.0);
	std::string name = this->sceneObj->addObjectToScene(gltfModel, gltfTransform, lightShader);


	this->sceneObj->setDirectionalLight(glm::vec3(-1.0f, -1.0f, -0.5f), glm::vec3(0.1, 0.1, 0.1), glm::vec3(0.4, 0.4, 0.5), glm::vec3(0.3, 0.3, 0.3));

	
	Level level1;
	level1.setLevelScene(this->sceneObj);
	level1.setLevelPhysicsWorld(this->world);
	level1.setLevelModel("resources/Terrain/flatForest.obj");
	level1.renderMap(lightShader);

	Camera newCamera(glm::vec3(0.0f, 0.0f, 3.0f));

	this->sceneObj->setCamera(&newCamera);

	this->sceneObj->setDepthShader(depthShader);
	this->gameRenderer->setDebugDepthQuadShader(debugDepthQuad);

	playerEntity newPlayer("resources/player/player.gltf");
	characterController playerController(&newPlayer,this->sceneObj,this->world, animationShader);

	unsigned int boxId;
	std::string boxSceneID;
	transform boxTransform;
	boxTransform.position = glm::vec3(4, 10, 4);
	boxTransform.orientation = glm::quat(1.0, 0.0, 0.0, 0.0);
	boxTransform.scale = glm::vec3(1.0f);

	transform newObjTransform;
	newObjTransform.position = glm::vec3(0, 0, 0);
	newObjTransform.orientation = glm::quat(1.0, 0.0, 0.0, 0.0);
	newObjTransform.scale = glm::vec3(0.01f);

	gameObjectManager newManager;
unsigned int objID = newManager.createHandGun("resources/Assets/1911Modified.gltf",100,glm::vec3(0,0,0),"handGun",glm::vec3(1.0f),glm::vec3(0,0,1));

std::string sceneobjID;

if(auto weapon = std::dynamic_pointer_cast<handGun>(newManager.getItemPTR(objID)))
{
	std::cout << "this is a gun pew pew pew\n";
	Model* newModels = weapon->getModel();

	sceneobjID = this->sceneObj->addObjectToScene(newModels,newObjTransform,lightShader);
}

newPlayer.equipRightHand(newManager.getItemPTR(objID));



	Model* boxModel = ResourceManager::loadModel("resources/Assets/badCrate.obj","badBox");

	std::vector <glm::vec3> boxVertices;
	for(unsigned int i = 0 ; i < boxModel->meshes[0].vertices.size(); i++)
	{
		Vertex vertex = boxModel->meshes[0].vertices[i];
		boxVertices.push_back(vertex.vertexPosition);
	}
	boxSceneID = sceneObj->addObjectToScene(boxModel, boxTransform,lightShader);

	boxId = this->world->createRigidBody(boxTransform.position, boxTransform.orientation,20 ,boxVertices,Dynamic);
	//this->world->changeColliderOrigin(boxId, glm::vec3(0, -1.0, 0));

	thirdPersonCamera playerCamera;
	float pitch = 0, yaw = 0;
	double cursorX = 0, cursorY = 0;

	//game loop and refresh/rendering loop is controlled here, actual rendering is done with the renderer
	while (this->state == active)
	{
		setDeltaTime(); //update deltaTime for this loop
		checkMouse();


		boxTransform.position = world->getBodyPosition(boxId);
		boxTransform.orientation = world->getBodyRotation(boxId);
		sceneObj->updateTransform(boxSceneID, boxTransform);

		//std::cout << "box position: " << glm::to_string(boxTransform.position) << std::endl;



		if(this->WindowManager->checkKey(342))
		{
			//left alt
			this->WindowManager->enableCursor();
		}

		if (this->WindowManager->checkKey(341)) 
		{
			this->WindowManager->disableCursor();
		}

		if (this->WindowManager->checkKey(87)) //w
		{
			newCamera.ProcessKeyboard(FORWARD,deltaTime);
		};

		if (this->WindowManager->checkKey(65)) //a
		{
			newCamera.ProcessKeyboard(LEFT, deltaTime);
		};

		if (this->WindowManager->checkKey(83)) //s
		{
			newCamera.ProcessKeyboard(BACKWARD, deltaTime);
		};

		if (this->WindowManager->checkKey(68)) //d
		{
			newCamera.ProcessKeyboard(RIGHT, deltaTime);
		};

		//mouse position;
		float lastx = cursorX;
		float lasty = cursorY;

		this->WindowManager->getMousePosition(&cursorX, &cursorY);

		float xOffset = cursorX - lastx;
		float yOffset = lasty - cursorY;
		newCamera.ProcessMouseMovement(xOffset,yOffset,true,newPlayer.getPlayersTransform()->position + glm::vec3(0,1.5,0), 0);
		
		if(newCamera.isThirdPerson())
		{
			transform* newTransform = newPlayer.getPlayersTransform();
			newTransform->orientation = glm::rotate(glm::toMat4(newTransform->orientation), xOffset * 0.01f, glm::vec3(0, 1, 0));
			//newPlayer.setPlayerTransform(*newTransform);
		}
		
		if(this->WindowManager->checkKey(49))//1 key
		{
			newCamera.setCameraFreeCam();
		}
		if(this->WindowManager->checkKey(50))//2 key
		{
			newCamera.setCameraThirdPerson(2.6);
		}

		playerController.updateInputs(this->WindowManager);
		playerController.updateController(deltaTime, level1);

		transform tempTran;
		tempTran.position = newPlayer.getRightHandMat() * glm::vec4(1.0f);
		tempTran.orientation = glm::quat(1.0, 0, 0, 0);
		tempTran.scale = glm::vec3(0.01f);

		//std::cout << "hand position: " << glm::to_string(newPlayer.getRightHandMat()) << std::endl;

		this->sceneObj->updateTransform(sceneobjID, tempTran);
	
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

	//Game/Window shutdown check
	if (this->state != active && this->state != pause) //if the game is not running or paused shutdown
	{
		this->state = shutdown;
	}

}

//old mouse positon checker will be removed
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