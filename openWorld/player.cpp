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
	this->collider = new playerCollider(); //need to add more data to this later
	this->motionController = new playerMotionController(); //add more data to this later
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
	//motionController
	
}