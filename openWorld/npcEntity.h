#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>

#include "renderingInfoDefinitions.h"
#include "animationDataDefinitions.h"

//npc action definitions

#include "ResourceManager.h"
#include "objAnimator.h"
#include "Scene.h"
#include "Shader.h"

//this class controls animations for an npc based off of npc actions
#ifndef NPCENTITY_H
#define NPCENTITY_H


class npcEntity
{
public:
	npcEntity(std::string npcFilePath);
	~npcEntity();

	void setNPCaction();

	void setNPCtransform(transform newTransform);

	transform* getTransform();

	relTransform* getRelativeTransform();

	Model* getNPCmodel();

	void calculateRelTransform();

	void addToScene(scene* scene, Shader* shader);

	void updateScene(scene* scene);

	objAnimator* getAnimator();

	void updateEntity();

private:

	void loadPlayerAnimations(std::string filePath); //directory for player animations will be under the players file path in a file named animations

	void updateActions();

	objAnimator* animator;

	//transforms and movement
	//this is position, orientation, and scaling for renderer
	relTransform relativeTransf; //this is front, up, and right

	//player file path from .player file format
	std::string filePath;

	std::string name; //this one should be pretty self explanatory

	bool meshChange = false;
	bool animationChange = false;
	bool actionChange = false;

	std::string activeAnim;//current active animation

	//rendering data
	Model* Model;

	std::string sceneID;

	transform currentTransform;

};

#endif // !NPCENTITY_H