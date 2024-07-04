#pragma once
#include <iostream>

#include "Includes/glm/glm.hpp"
#include "Includes/glm/gtc/type_ptr.hpp"

#include "renderingInfoDefinitions.h"
#include "item.h"

#include "ResourceManager.h"

#ifndef HANDGUN_H
#define HANDGUN_H


class handGun : public item
{
public:
	handGun(std::string filePath, float baseDamage, glm::vec3 handPoint, std::string name, glm::vec3 barrelPos, glm::vec3 front);

	handGun() {};

	~handGun() override;

	std::string getName() const override { return this->name; }

	bool isEquipable() const override { return true; }
	bool isStackable() const override { return false; }
	bool isConsumable() const override { return false; }

	float getMass() const override { return this->mass; }
	float getVolume() const override { return this->volume; }

	Model* getModel() { return this->model; }

	glm::vec3 getBarrelPos();
	glm::vec3 getDirection();

	glm::mat4 getTransform();
	void setTransform(glm::mat4 transf);



private:
	//local points on the object that is used for player/entity animations
	glm::vec3 handPoint1; //hand Point relative to the gun (should be the grip on a handgun)
	glm::vec3 handPoint2; //second point if used relative to the gun
	bool twoHanded; //is this object one handed or two handed

	float baseDamage;

	bool hasMagazine;
	//Magazine* currentMagazine
	bool chambered;

	//ammoType

	glm::vec3 front;  //world space front
	glm::vec3 barrel; //relative position of the barrel

	glm::mat4 worldTransform;
	Model* model;

	std::string name;
	bool equipable;
	bool stackable;
	bool consumable;
	float mass; //mass/volume used for inventory management 
	float volume;
};

#endif // !HANDGUN_H