#pragma once

#include "includes/glm/glm.hpp"
#include "Includes/glm/gtc/type_ptr.hpp"

#include "animationDataDefinitions.h"
#include "renderingInfoDefinitions.h"
#include "Shader.h"

#include <iostream>
#include <vector>

enum rangedWeaponTypes
{
	pistol,
	longGun,
	bowCrossBow,
	sling,
	thrown, //thrown weapons like rocks, bricks, ect
};

enum meleeWeaponTypes
{
	blunt,
	stab,
	slash,
};

enum ammoType //used to describe ammo type so you cant use an arrow in a gun and bullets with a bow and arrow
{
	ball556,
	ball223,
	ball9mm,
	ball45ACP,
	nato308,
	improvisedArrow,
	huntingArrow,
};

enum magazineTypes
{
	doubleStack556, //10 round, 20 round and 30 round variants (more variants are possible but not going that in depth just yet)
	doubleStack223,
	singleStack45,
	singleStack9mm,
	doubleStack45,
	doubleStack9mm,
};

struct magazine
{
	magazineTypes type;
	ammoType ammoUsed; //type of ammo currently in this magazine
	int maxCapacity;   //max ammo allowed in this magazine
	int currentCount;  //current amount in the magazine
};

struct rangedWeapon
{
	rangedWeaponTypes type; //what type of weapon is it
	glm::vec3 handPoint1; //where is the main handle point in object space on this weapon (grip of a pistol, shaft of a spear, ect)
	glm::vec3 handPoint2; //where does the second/off hand go if used in object space (supporting the other hand on a pistol, further down the shaft of a spear, ect)
	bool twoHanded; //true if this weapon is only two handed

	float baseDamage;

	bool hasMagazine; //does this weapon have a magazine currently equiped
	unsigned int currentMagazine; //ID of current magazine, if ID = 0 there is not magazine
	bool chambered; //is there a round chambered

	ammoType AmmoUsed; //ammo type used by the weapon, some guns can use multiple however is not implimented currently
	std::vector <magazineTypes> allowedMagazines; //what magazine types are allowed to be used in this weapon (some guns can use multiple types, ar-15s can use ar-15,m-16, and mini-14 style magazines)

	glm::vec3 front;  //front of the weapon or the projectile direction
	glm::vec3 barrel; //from where the projectile comes from (barrel of a gun, arrow in a bow and arrow), used for projectile tragectories with the weapon front
};

struct meleeWeapon
{
	meleeWeaponTypes type;
	glm::vec3 handPoint1;
	glm::vec3 handPoint2;
	bool twoHanded;

	float baseDamage;

	//damage hitbox (oriented boundng box in local space)
	glm::vec3 localPosition;
	glm::quat localOrient;
	glm::vec3 halfSizes;
};

struct healthItems
{
	int uses;
	int timesUsed;

	float amtRestored;
};

struct renderable
{
	Model* objectModel;
	Shader* renderingShader;
	transform renderTransform;
};

enum clothingPart //what body part can the item be worn on
{
	chest,
	arms,
	hands,
	head,
	feet,
	waist,
	legs,
};

struct wearable
{
	clothingPart whereWorn; //what body part this object is worn on
	float heatResist;
	float coldResist;
	float damageResist;
};

struct isAnimated
{
	std::vector <animation*> animations;
};

struct isStorage
{
	float maxWeight;
	float maxVolume;
	float currentVolume;
	float currentWeight;

	float weightModifier; //modifier used to determine how much player is affected by weight of items in this object
	std::vector <unsigned int> objectIds; //ids of all objects stored in this object
};

struct renderable2D
{
	//this is where data for it's sprite will be when implimented so it can be seen in an inventory on the players hud
};