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
	if(this->currentAction != newAction)
	{
		this->currentAction = newAction;
	}
}

void playerAnimationController::updateAnimationState()
{
	//use the current player action to determine the animation that should be played, blending and ect
	switch(*this->currentAction)
	{
	case(idle):
		this->playerAnimator->playAnimation("idle");
		break;

	case(walkForward):
		//this->playerAnimator->playAnimation("walkForward");
		break;
	case(walkLeft):
		//this->playerAnimator->playAnimation("walkLeft");
		break;
	case(walkRight):
		//this->playerAnimator->playAnimation("walkRight");
		break;
	case(walkBack):
		//this->playerAnimator->playAnimation("walkBack");
		break;

	case(jogForward):
		//this->playerAnimator->playAnimation("jogForward");
		break;
	case(jogLeft):
		//this->playerAnimator->playAnimation("jogLeft");
		break;
	case(jogRight):
		//this->playerAnimator->playAnimation("jogRight");
		break;
	case(jogBack):
		//this->playerAnimator->playAnimation("jogBack");
		break;

	case(jump):
		//this->playerAnimator->playAnimation("jump");
		break;
	case(crouch):
		//this->playerAnimator->playAnimation("crouch");
		break;
	case(evading):
		//this->playerAnimator->playAnimation("evade");
		break;
	}
}