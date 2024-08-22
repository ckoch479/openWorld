#include "characterController.h"

characterController::characterController(windowManager* manager)
{
	this->inputManager = manager;
	//setDefaultMappings();
}

characterController::~characterController()
{

}

void characterController::setDefaultMappings()
{
	/*this->keyMap['w'] = 87;
	this->keyMap['a'] = 65;
	this->keyMap['s'] = 83;
	this->keyMap['d'] = 68;

	this->keyMap['q'];
	this->keyMap['e'];
	this->keyMap[' '] = 32;

	this->keyMap['Lctr'] = 341;
	this->keyMap['caps'] = 280;
	this->keyMap['tab'] = 258;

	this->keyMap['lshf'] = 340;
	
	this->keyMap['z'];
	this->keyMap['x'];*/

}

void characterController::updateInputs()
{
	this->keyStates = this->inputManager->getKeyStates();
}


playerActions characterController::updateController()
{
	updateInputs();

	playerActions currentAction = idle;

	//single key presses:
	if (keyStates[87]) //w
	{
		currentAction = walkForward;
	}
	if (keyStates[65] ) //a and LShift
	{
		currentAction = walkLeft;
	}
	if (keyStates[83] ) //s and LShift
	{
		currentAction = walkBack;
	}
	if (keyStates[68] ) //d and LShift
	{
		currentAction = walkRight;
	}

	if(keyStates[32]) //space
	{
		currentAction = jump;
	}
	if(keyStates[341])//Lcrtl
	{
		currentAction = crouch;
	}
	if(keyStates[342]) //Lalt
	{
		currentAction = evading;
	}
	if(this->inputManager->rightClick())
	{
		currentAction = aiming;
	}

	//2 key presses:
	if (keyStates[87] && keyStates[340]) //w and LShift
	{
		currentAction = jogForward;
	}
	if (keyStates[68] && keyStates[340]) //d
	{
		currentAction = jogRight;
	}
	if (keyStates[65] && keyStates[340]) //a
	{
		currentAction = jogLeft;
	}
	if (keyStates[83] && keyStates[340]) //s
	{
		currentAction = jogBack;
	}

	if (keyStates[87] && keyStates[65]) //w and a
	{
		currentAction = walkForwardLeft;
	}
	if (keyStates[87] && keyStates[68]) //w and d
	{
		currentAction = walkForwardRight;
	}
	if (keyStates[83] && keyStates[65]) //s and a
	{
		currentAction = walkBackLeft;
	}
	if (keyStates[83] && keyStates[68]) //s and d
	{
		currentAction = walkBackRight;
	}

	if (this->inputManager->rightClick() && keyStates[87]) //w and right click
	{
		currentAction = walkAiming;
	}
	if (this->inputManager->rightClick() && keyStates[65])//a and right click
	{
		currentAction = aimingStepLeft;
	}
	if (this->inputManager->rightClick() && keyStates[83])//s and right click
	{
		currentAction = aimingStepBack;
	}
	if (this->inputManager->rightClick() && keyStates[68])//d and right click
	{
		currentAction = aimingStepRight;
	}

	//3 key presses
	if (keyStates[87] && keyStates[65] && keyStates[340]) //w and a
	{
		currentAction = jogForwardLeft;
	}
	if (keyStates[87] && keyStates[68] && keyStates[340]) //w and d
	{
		currentAction = jogForwardRight;
	}
	if (keyStates[83] && keyStates[65] && keyStates[340]) //s and a
	{
		currentAction = jogBackLeft;
	}
	if (keyStates[83] && keyStates[68] && keyStates[340]) //s and d
	{
		currentAction = jogBackRight;
	}

	

	

	return currentAction;
}

void characterController::checkCombinationKeys()
{

}