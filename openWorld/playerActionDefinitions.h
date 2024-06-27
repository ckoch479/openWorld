#pragma once
enum playerActions
{
	idle,
	idlePistol,
	idleRifle,

	walking,
	sideWalkLeft,
	sideWalkRight,
	walkingBack,
	walkingPistolLowered,
	walkingPistolRaised,
	walkingRifleLowered,
	walkingRifleRaised,

	leftTurn,
	rightTurn,

	jogging,
	sideJogLeft,
	sideJogRight,
	joggingPistolLowered,
	joggingRifleLowered,

	leftJoggingTurn,
	rightJoggingTurn,
	
	running,

	leftRunninggTurn,
	rightRunningTurn,

	crouching,
	crouchingPistol,
	crouchingRile,

	crouchWalking,
	crouchWalkingPistolLowered,
	crouchWalkingPistolRaised,
	crouchWalkingRifleLowered,
	crouchWalkingRifleRaise,
	
	jumping,

	diveRight,
	diveLeft,
	jumpBack,
	diveForward,

	climbingSmall,
	climingTall,

	falling,

	dying,

};

//this enum below is to define the players "parts" (legs,feet,hands,arms,torso)
enum playerParts
{
	head,
	
	torso,
	
	leftArm,
	rightArm,
	
	leftHand,
	rightHand,

	pelvis,

	leftLeg,
	rightLeg,

	leftFoot,
	rightFoot,
};

//posible injury types
enum injuryStatus
{
	healthy,
	sprained,
	broken,
	scrape,
	abrasion,
	laceration,
	bleeding,
	missing,
	bitten,
	bandaged,
	sutured,
	torniquet,
};