#pragma once

//actions the player can take may be modified for clarity since it is so large
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
	aimingStepLeft, 
	aimingStepRight,


	climbing,

	evading,
	
	falling,
	
	dying,
};