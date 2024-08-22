#pragma once

enum playerActions
{
	idle,

	walkForward,
	walkLeft,
	walkRight,
	walkBack,

	walkForwardLeft,
	walkForwardRight,
	walkBackLeft,
	walkBackRight,

	turnLeft,
	turnRight,

	jogForward,
	jogLeft,
	jogRight,
	jogBack,

	jogForwardLeft,
	jogForwardRight,
	jogBackLeft,
	jogBackRight,

	sprintForward,
	sprintLeft,
	sprintRight,

	jumpForward,
	jumpLeft,
	jumpRight,
	jumpBack,
	jump,

	crouch,

	aimPistol,

	aimPistolUp,
	aimPistolDown,
	aimPistolRight,
	aimPistolLeft,

	aiming,

	walkAiming,
	aimingStepBack, 
	aimingStepLeft, //found
	aimingStepRight,//found


	climbing,

	evading,
	
	falling,
	
	dying,
};