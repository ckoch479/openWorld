#pragma once
#include <iostream>

#include "Includes/glm/glm.hpp"
#include "Includes/glm/gtc/type_ptr.hpp"

#include "renderingInfoDefinitions.h"
#include "item.h"

#include "ResourceManager.h"
#include "Scene.h"
#include "Shader.h"

#ifndef HANDGUN_H
#define HANDGUN_H


class handGun : public item
{
public:
	handGun(std::string filePath, std::string name, float mass, float volume);

	~handGun() override;

	std::string getName() const override { return this->name; }

	bool isEquipable() const override { return true; }
	bool isStackable() const override { return false; }
	bool isConsumable() const override { return false; }

	float getMass() const override { return this->mass; }
	float getVolume() const override { return this->volume; }

	void addToScene(scene* scene, Shader* shader); 
	void updateTransform(scene* scene, transform newTransform);
	transform getTransform() { return this->sceneTransform; }

	void shoot(); //create projectile in the world

private:
	//local points on the object that is used for player/entity animations
	Model* model;
	std::string sceneID;
	transform sceneTransform;

	//temporary use these to create the final orientation
	glm::vec3 front = glm::vec3(0,0,-1);
	glm::vec3 up = glm::vec3(0,1,0);
	glm::vec3 right = glm::vec3(1,0,0);

	float mass; //mass/volume used for inventory management 
	float volume;
	std::string name;

	bool hasMagazine = false;
	bool chambered = false;
	//Magazine* currentMagazine
};

#endif // !HANDGUN_H