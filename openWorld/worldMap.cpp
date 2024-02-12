#include "worldMap.h"

worldMap::worldMap()
{

}

worldMap::~worldMap()
{

}


void worldMap::GenerateMap(std::string filename, std::string mapName, Scene* scene, Shader& shader)
{
	this->worldModel = ResourceManager::loadModel(filename, mapName); //load map model from file
	this->worldModelID = scene->createModel(*this->worldModel,shader);
	ID transformID = scene->createTransform(glm::vec3(0.0f),glm::vec3(0,1,0),0,glm::vec3(100.0,5.0,100.0));
	ID sceneObjectID = scene->AddInstance(this->worldModelID, transformID);
	this->instanceID = sceneObjectID;
	generateTerrainHeight();
}

float worldMap::getTerrainHeight(float x, float z)
{
	return this->XZtable[x][z];
}



void worldMap::addStaticObject()
{

}

void worldMap::generateTerrainHeight()
{
	for (unsigned int i = 0; i < this->worldModel->meshes.size(); i++) //iterate through each map mesh first then through each vertex
	{

		for (int j = 0; j < this->worldModel->meshes[i].vertices.size(); j++) 
		{
			glm::vec3* tempVec = &this->worldModel->meshes[i].vertices[i].vertexPosition;
			this->XZtable[tempVec->x][tempVec->z] = tempVec->y; //insert the x value first then the z value leaving the y value as a key of a key
		}
	}

}

