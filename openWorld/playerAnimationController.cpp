#include "playerAnimationController.h"

playerAnimationController::playerAnimationController(objAnimator* playerAnimator, playerActions* currentAction)
{
	this->playerAnimator = playerAnimator;
	this->currentAction = currentAction;
	this->currentAnimation = "idle";
}

playerAnimationController::~playerAnimationController()
{

}

void playerAnimationController::updatePlayerAction(playerActions* newAction)
{
	this->currentAction = newAction;

}

void playerAnimationController::updateAnimationState()
{
	//use the current player action to determine the animation that should be played, blending and ect
	switch(*this->currentAction)
	{
	case(idle):
		this->playerAnimator->playAnimation("idle");
		break;
	}
}