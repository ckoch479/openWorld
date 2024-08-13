#include "chunk.h"

chunk::chunk()
{

}

chunk::~chunk()
{

}

void chunk::update()
{

}

void chunk::setId(int newId)
{

}

void chunk::setFilePath(std::string newFilePath)
{

}

bool chunk::loadChunk(std::string filePath)
{
	bool loadFinished = false;



	return loadFinished;
}

bool chunk::saveChunkData()
{
	bool saveFinished = false;
	//saving this chunk to a file first remove from scene so the player can no longer see the chunk
	this->removeChunkFromScene(this->sceneObj);
	//remove chunk from physics world

	//write filePaths to chunk objects into a string

	//write filepath data and object data to chunk file
	return saveFinished;
}

void chunk::setSceneObj(scene* newScene)
{
	this->sceneObj = newScene;
	this->sceneLoaded = true;
}

void chunk::addChunktoScene(scene* scene)
{
	
	//add static terrain objects:
	for(int i = 0; i < this->terrainModels.size(); i++)
	{
		transform chunkTransform; //changed this so the terrain object can have their own transforms
		chunkTransform.position = this->position + this->terrainModels[i].Pos;
		chunkTransform.orientation = this->rotation + this->terrainModels[i].orient;
		chunkTransform.scale = this->scale + this->terrainModels[i].scale;

		//std::string newId = scene->addStaticSceneObj(this->terrainModels[i].model, chunkTransform);
		//this->sceneIds.push_back(newId);
	}
}

void chunk::removeChunkFromScene(scene* scene)
{
	//static objects first
	for (int i = 0; i < this->sceneIds.size(); i++)
	{
		scene->removeStaticObject(this->sceneIds[i]); //remove each static object from scene
	}
	//dynamic objects next
}

void chunk::updateChunkSceneData(scene* scene)
{

}

void chunk::setTransform(glm::vec3 pos, glm::quat orient, glm::vec3 scale)
{
	this->position = pos;
	this->rotation = orient;
	this->scale = scale;
}

glm::vec2 chunk::getChunkMapIndex()
{
	return this->chunkMapIndex;
}