#pragma once
#include <iostream>
#include <vector> //might remove alter
#include <unordered_map> //same here dont know yet

#include "includes/glm/glm.hpp"
#include "Includes/glm/gtc/type_ptr.hpp"
#include "Includes/glm/gtc/quaternion.hpp"

#include "ResourceManager.h"

//world map class is the overall manager of the game world all filepaths to map chunks will be store here. this class is responsible for managing and loading chunks surrounding the player
//as well as saving data about chunks that no longer need to be loaded (NPCs/AI characters), this class is not responsible for managing triggers, rendering, or scripts of any kind
//just raw level data for loading and unloading purposes

#ifndef WORLDMAP_H
#define WORLDMAP_H

class worldMap
{
public:
	//constructor needs the filepath to the main map file this file contains all of the filepaths of each chunk
	worldMap(std::string mainFilePath);

	~worldMap();

	void updateWorld();

private:

	//data and settings:

	int chunkDistance = 9; //makes a nice square with the player's chunk in the middle so thats nice
	int chunkCount = 0;

	glm::vec3 playerWorldPosition; //position of the player in the game world (NOT CHUNK COORDS) <- thats why it's a vec3 incase of confusion even though only x and z coords are needed
	
	//std::vector <chunk*> loadedChunks; //to be added later but should contain the loaded chunks
	//chunk* playerChunk; //chunk the player is currently in this chunk gets update first when updating chunks

	int generateNewId(); //creates unique id for each chunk

	std::unordered_map <glm::vec2, int> chunkMap; //each chunk is given a x and y coordinate of it's placement which stores it's id
	std::unordered_map <int, std::string> chunkPaths; //each chunk is a 10 meter x 10 meter square, each chunk has it's own id (10x10 is arbitrary so bite me)
	std::unordered_map <int, bool> chunkLoaded; //map of each currently loaded chunk
};

#endif

//chunk layout
//
//  
// +
// | [][][][][][][][][][][][][][][][][][][]
// | [][][][][][][][][][][][][][][][][][][]
// | [][][][][][][][][][][][][][][][][][][]
// | [][][][][][][][o][o][o][][][][][][][][][]
// | [][][][][][][][o][x][o][][][][][][][][][]
// | [][][][][][][][o][o][o][][][][][][][][][]
// | [][][][][][][][][][][][][][][][][][][]
// | [][][][][][][][][][][][][][][][][][][]
// | [][][][][][][][][][][][][][][][][][][]
// | [][][][][][][][][][][][][][][][][][][]
// | [][][][][][][][][][][][][][][][][][][]
// z [][][][][][][][][][][][][][][][][][][]
//  x------------------------------------ +
// x = player chunk
// o = loaded chunks