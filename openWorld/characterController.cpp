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

	if (keyStates[87] && !keyStates[340]) //w and LShift
	{
		currentAction = walkForward;
	}
	else if (keyStates[87]) //w
	{
		currentAction = jogForward;
	}

	else if (keyStates[65] && keyStates[340]) //a
	{
		currentAction = jogLeft;
	}
	else if (keyStates[65] ) //a and LShift
	{
		currentAction = walkLeft;
	}

	else if (keyStates[83] && keyStates[340]) //s
	{
		currentAction = jogBack ;
	}
	else if (keyStates[83] ) //s and LShift
	{
		currentAction = walkBack;
	}

	else if (keyStates[68] && keyStates[340]) //d
	{
		currentAction = jogRight ;
	}
	else if (keyStates[68] ) //d and LShift
	{
		currentAction = walkRight;
	}

	else if(keyStates[32]) //space
	{
		currentAction = jump;
	}
	else if(keyStates[341])//Lcrtl
	{
		currentAction = crouch;
	}
	else if(keyStates[342]) //Lalt
	{
		currentAction = evading;
	}

	return currentAction;
}

void characterController::checkCombinationKeys()
{

}