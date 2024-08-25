#include "player.h"
player::player(renderContext context, Model* newModel, windowManager* inputManager, PhysicsWorld* world)
{
	this->positionPtr = &position;
	this->orientationPtr = &orientation;
	this->scalePtr = &scale;

	this->name = &entityName;

	currentAction = idle;
	secondaryAction = idle;

	this->currentAnimation = "idle";

	this->playerModel = newModel; //will need to be changed later if the player can dynamically swap each of its models but for now good enough
	this->playerSkeleton = this->playerModel->skeleton;
	this->renderData = context;

	this->playerController = new characterController(inputManager);
	this->playerAnimator = new objAnimator(this->playerModel);
	this->cameraController = new playerCameraController(&this->renderData,inputManager);

	this->renderer = new playerRenderer(&this->renderData,this->playerModel);
	this->renderer->setTransform(this->positionPtr, this->orientationPtr, this->scalePtr);
	this->renderer->addPlayerToScene();
	
	this->collider = new playerCollider(world,this->playerSkeleton,this->playerAnimator,this->positionPtr,this->orientationPtr); //create player main and bone colliders

	this->motionController = new playerMotionController(this->collider->getMainBox(),&this->currentAction); //set the main collider in movement controller for world collisions
	this->motionController->setPlayerTransforms(this->positionPtr,this->orientationPtr,this->scalePtr,&this->front,&this->right,&this->up);

	this->animationController = new playerAnimationController(this->playerAnimator, &this->currentAction);

	this->modelManager = new playerModelManager(this->playerModel, this->playerAnimator, this->renderer);
	this->modelManager->setPlayerTransform(this->positionPtr, this->orientationPtr, this->scalePtr);
	invManager = new PlayerInventoryManager(this->modelManager);

}

player::~player() 
{

}

void player::update(float dt)
{
	this->currentAction = this->playerController->updateController();

	this->animationController->updatePlayerAction(&this->currentAction);
	this->animationController->updateAnimationState();

	this->playerAnimator->update(dt);

	this->cameraController->updateController(dt, this->position,&this->front);

	this->renderer->setTransform(this->positionPtr, this->orientationPtr, this->scalePtr);
	this->renderer->setAnimTransforms(this->playerAnimator->getAnimationTransforms());
	//this->renderer->updatePlayerRender();

	//collider
	
	this->motionController->updatePlayerMotion(dt, &this->currentAction);
	this->motionController->handleRotation(dt, this->cameraController->getCamera());

	this->modelManager->updateManager();
	this->collider->updateColliders(dt);

	//transforms are really messed up, had to inverse the orientation in collider and render to get things to match up correctly, cant really find where i messed up my math so this will
	//have to do for now until i can either fix it or impliment a class that manages corrections applied to imported models and such

}

void player::debugDirections(debugger* debug)
{

	glm::vec3 frontA = *this->positionPtr + glm::vec3(0, 1, 0);
	glm::vec3 frontB = frontA + this->front * 1.0f;
	debug->addDebugLine(frontA, frontB);

	//draw target position, just a box where the camera target is
	glm::vec3 targetPos = *this->cameraController->getTargetPosition();
	debug->addDebugBox(targetPos, glm::quat(1.0, 0.0, 0.0, 0.0), glm::vec4(1.0, 1.0, 1.0, 0.9), glm::vec3(0.1, 0.1, 0.1));
}

glm::vec3* player::getPosition()
{
	return this->positionPtr;
}

void player::equipItem(item* newItem)
{
	this->invManager->equipItem(PlayerInventoryManager::Slot::RightHand, newItem);
}