#pragma once
enum playerActions
{
	idle,
	walking,
	turning,
	jogging,
	sprinting,
	jumping,
	climbing,
	evading,
	falling,
	dying,
};

enum actionModifiers
{
walkToggle,
sprintToggle,
crouch,
crawl,
aim,
shoot,
leftWards,
rightWards,
forward,
backward,
oneHandEquiped,
twoHandEquiped,
none,
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

	legs,

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