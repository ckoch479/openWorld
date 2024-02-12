#pragma once
#include <iostream>
#include <vector>
#include <map>

#include "includes/glm/glm.hpp"
#include "Includes/glm/gtc/type_ptr.hpp"
#include "Includes/glm/gtc/quaternion.hpp"

#include "ResourceManager.h"
#include "Scene.h"

#ifndef WORLDMAP_H
#define WORLDMAP_H

class worldMap
{
public:
	worldMap();
	~worldMap();

	//load a mesh for terrain modeled in an outside program and extract height coordinates as well as add world details i.e skybox, trees, grass etc
	void GenerateMap(std::string filename, std::string mapName, Scene* scene, Shader& shader); //loadModelData and collision data for a worldMap

	float getTerrainHeight(float x, float z); //input x,z coordinates for the world and the height will be returned



	void addStaticObject();
	
private:

	void generateTerrainHeight();

	ModelData* worldModel;
	ID worldModelID; //for rendering
	ID instanceID;
	std::map <float, std::map<float, float>> XZtable; 

	
};

#endif