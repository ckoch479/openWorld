#include "worldMap.h"

worldMap::worldMap()
{

}

worldMap::~worldMap()
{

}

void worldMap::addMaptoPhysicsWorld(PhysicsWorld* world)
{
	world->addTerrainMeshVertices(this->terrainMesh);
}

std::vector <glm::vec3> worldMap::getVertices()
{
	std::vector <glm::vec3> vertices;

	//for(unsigned int i = 0; i < this->worldModel->meshes.size(); i++)
	//{
	//	for(unsigned int j = 0; j < this->worldModel->meshes[i].vertices.size(); j++)
	//	{
	//		vertices.push_back(this->worldModel->meshes[i].vertices[j].vertexPosition);
	//	}
	//}

	return this->terrainMesh;// vertices;
}

std::vector <int> worldMap::getIndices()
{
	std::vector <int> indices;
	for(unsigned int i = 0; i < this->worldModel->meshes.size(); i++)
	{
		for(unsigned int j = 0; j < this->worldModel->meshes[i].indices.size(); j++)
		{
			indices.push_back(this->worldModel->meshes[i].indices[j]);
		}
	}

	return indices;
}

void worldMap::GenerateMap(std::string filename, std::string mapName, Scene* scene, Shader& shader)
{
	this->worldModel = ResourceManager::loadModel(filename, mapName); //load map model from file
	this->worldModelID = scene->createModel(*this->worldModel,shader);
	ID transformID = scene->createTransform(glm::vec3(0.0,0.0,0.0),glm::quat(), glm::vec3(1.0, 1.0, 1.0));
	ID sceneObjectID = scene->AddInstance(this->worldModelID, transformID);
	this->instanceID = sceneObjectID;
	generateTerrainHeight();
}

float worldMap::getTerrainHeight(float x, float z) //throws error when x coordinate goes negative
{
	int x0 = 1;// x;//std::floor(x);
	int z0 = 1;// z;// std::floor(z);
	//int x1 = x0 + 1;
	//int z1 = z0 + 1;


	x0 = x;
	z0 = z;
	//int index00 = x0 * 1 + z0;
	//int index10 = x1 * 1 + z0;
	//int index01 = x0 * 1 + z1;
	//int index11 = x1 * 1 + z1;



	//if (index00 > terrainMesh.size() || index10 > terrainMesh.size() || index01 > terrainMesh.size() || index11 > terrainMesh.size(),
	//	index00 < 0 || index01 < 0 || index10 < 0 || index11 < 0) 
	//{
	//	index00 = 1;
	//	index10 = 1;
	//	index01 = 1;
	//	index11 = 1; 
	//}

	//glm::vec3 v00 = terrainMesh[index00];
	//glm::vec3 v10 = terrainMesh[index10];
	//glm::vec3 v01 = terrainMesh[index01];
	//glm::vec3 v11 = terrainMesh[index11];

	//float wx = x - x0;
	//float wz = z - z0;

	//float height_x0 = v00.y + (v10.y - v00.y) * wx;
	//float height_x1 = v01.y + (v11.y - v01.y) * wx;

	//std::cout << "height 1 and 2: " << height_x0 << " " << height_x1 << std::endl;

	//float interpolatedHeight = height_x0 + (height_x1 - height_x0) * wz;

	//std::cout << "terrain height: " << XZtable[(int)x][(int)z] << std::endl;
	//std::cout << "player x,z: " << x << " " << z << std::endl;
	//std::cout << "terrain height interpolated: " << interpolatedHeight << std::endl;

	return this->XZtable[(int)x][(int)z];

//	return interpolatedHeight;

}



void worldMap::addStaticObject()
{

}

void worldMap::generateTerrainHeight()
{
	std::vector <int> uniqueTerrainXvalues;

	for (unsigned int i = 0; i < this->worldModel->meshes.size(); i++) //iterate through each map mesh first then through each vertex
	{

		for (int j = 0; j < this->worldModel->meshes[i].vertices.size(); j++) 
		{
			this->numXcoords++;
			glm::vec3* tempVec = &this->worldModel->meshes[i].vertices[j].vertexPosition;

			this->XZtable[(int)tempVec->x][(int)tempVec->z] = tempVec->y; //insert the x value first then the z value leaving the y value as a key of a key

			this->terrainMesh.push_back(*tempVec);

			bool hasXvalue = false;
			for(int xCounter = 0; xCounter < uniqueTerrainXvalues.size(); xCounter++)
			{
				if(uniqueTerrainXvalues[xCounter] == (int)tempVec->x)
				{
					hasXvalue = true;
				}
			}

			if(hasXvalue == false)
			{
				uniqueTerrainXvalues.push_back((int)tempVec->x);
			}
		}
	}

	this->terrainWidth = uniqueTerrainXvalues.size() * 2;

	
	
}



