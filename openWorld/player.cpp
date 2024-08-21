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

	this->cameraController->updateController(dt, this->position);

	this->renderer->setTransform(this->positionPtr, this->orientationPtr, this->scalePtr);
	this->renderer->setAnimTransforms(this->playerAnimator->getAnimationTransforms());
	this->renderer->updatePlayerRender();

	//collider
	this->collider->updateColliders(dt);
	this->motionController->updatePlayerMotion(dt, &this->currentAction);
	//this->motionController->handleRotation(dt, this->cameraController->getCamera());

}