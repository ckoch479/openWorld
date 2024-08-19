#pragma once

#include "objAnimator.h"

#include "playerActions.h"
#include "Model.h"
#include "skeleton.h"


#ifndef PLAYERANIMATIONCONTROLLER_H
#define PLAYERANIMATIONCONTROLLER_H

class playerAnimationController
{
public:

	playerAnimationController(objAnimator* playerAnimator, playerActions* currentAction);

	~playerAnimationController();

	void updatePlayerAction(playerActions* newAction);

	void updateAnimationState();


private:

	std::string currentAnimation;


	objAnimator* playerAnimator;
	playerActions* currentAction;

};

#endif