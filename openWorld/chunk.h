#pragma once

#include <iostream>
#include <unordered_map>
#include <vector>

#include "includes/glm/glm.hpp"
#include "Includes/glm/gtc/type_ptr.hpp"
#include "Includes/glm/gtc/quaternion.hpp"

#include "Scene.h"

#include "ResourceManager.h"

#ifndef CHUNK_H
#define CHUNK_H

struct staticModels
{
	Model* model;
	glm::vec3 Pos;
	glm::quat orient;
	glm::vec3 scale;
};

//game chunk is a 10 meter x 10 meter square that holds level data for that area (game items, NPCs, ai characters, terrain models, physics objects, ect)
class chunk
{
public:
	chunk();
	~chunk();

	void update();
	
	void setId(int newId);

	void setFilePath(std::string newFilePath);

	//returns a bool if loading was completed or failed
	bool loadChunk(std::string filePath);

	bool saveChunkData(); //saves chunk data to the file using the filepath passed in on load, returns bool to check if completed

	void setSceneObj(scene* newScene);

	void setTransform(glm::vec3 pos,glm::quat orient, glm::vec3 scale);

	glm::vec2 getChunkMapIndex();

private:

	void addChunktoScene(scene* scene);

	void removeChunkFromScene(scene* scene);

	void updateChunkSceneData(scene* scene);

	scene* sceneObj; //ptr to the main scene obj for rendering terrain models
	bool sceneLoaded = false;
	//chunk data:
	
	//loading and referencing:
	int chunkId; //id is assigned by the worldMap class
	std::string filePath;
	std::vector <std::string> sceneIds; //scene ids for static chunk models for adding/removing scene data for these models

	//container data:

	bool staticChange = false; //false unless a static terrain object was changed in someway to update the scene
	bool dynamicChange = false;//should be true more often due to dynamic objects tending to ya know change, mainly here for if nothing does means we save updating the sceneObj (hopefully)

	std::vector <staticModels> terrainModels; //models for the terrain itself (not dynamic terrain objects just static geometry (like the floor mainly but buildings too))
	std::vector <Model*> dynamicTerrainModels; //terrain models that can move or be moved

	glm::vec2 chunkMapIndex; //x and z coords of this chunk in the chunkmap used by the worldMap class, will be in chunk file as well as worldMap file

	//chunk transform, chunk transform is added by the worldMap class only the chunkMap is loaded in from the file
	glm::vec3 position; //center of the chunk in world coords
	glm::quat rotation; //orientation of this chunk really shouldnt get rotated but incase it is rotation is kept here
	glm::vec3 scale;    //same thing here can be scaled but shouldnt really get scaled
};

#endif