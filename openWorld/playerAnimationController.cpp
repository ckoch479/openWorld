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
		this->playerAnimator->playAnimation("walkForward");
		break;
	case(walkLeft):
		this->playerAnimator->playAnimation("walkForward");
		break;
	case(walkRight):
		this->playerAnimator->playAnimation("walkForward");
		break;
	case(walkBack):
		this->playerAnimator->playAnimation("walkForward");
		break;

	case(jogForward):
		this->playerAnimator->playAnimation("jogForward");
		break;
	case(jogLeft):
		this->playerAnimator->playAnimation("jogForward");
		break;
	case(jogRight):
		this->playerAnimator->playAnimation("jogForward");
		break;
	case(jogBack):
		this->playerAnimator->playAnimation("jogForward");
		break;

	case(jump):
		this->playerAnimator->playAnimation("jump");
		break;
	case(crouch):
		//this->playerAnimator->playAnimation("crouch");
		break;
	case(evading):
		//this->playerAnimator->playAnimation("evade");
		break;

	case(aiming):
		this->playerAnimator->playAnimation("aimPistol");
		break;

	case(walkAiming):
		this->playerAnimator->playAnimation("aimWalkForward");
		break;

	case(aimingStepBack):
		this->playerAnimator->playAnimation("aimWalkBack");
		break;

	case(aimingStepLeft):
		this->playerAnimator->playAnimation("aimWalkLeft");
		break;

	case(aimingStepRight):
		this->playerAnimator->playAnimation("aimWalkRight");
		break;

	case(jogForwardLeft):
		this->playerAnimator->playAnimation("jogForward");
		break;

	case(jogForwardRight):
		this->playerAnimator->playAnimation("jogForward");
		break;

	case(jogBackLeft):
		this->playerAnimator->playAnimation("jogForward");
		break;

	case(jogBackRight):
		this->playerAnimator->playAnimation("jogForward");
		break;

	}
}