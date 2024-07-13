#include "Level.h"

Level::Level()
{
	this->name = "level1";
}

Level::Level(std::string filePath, std::string levelName, Shader* shader)
{
	this->name = levelName;
	this->levelShader = shader;
}

Level::~Level()
{

}

void Level::LoadLevelFromFile(std::string filePath, Shader* shader)
{
	this->name = "level1";
	this->levelShader = shader;
}

std::string Level::addObjectToLevel(std::string filePath, glm::vec3 position) 
{
	return "null";
}

std::string Level::addTriggerToMap(glm::vec3 position, glm::quat orientation, glm::vec3 halfExtents) 
{
	return "null";
}

bool Level::hasTriggerBeenActivated(std::string triggerName)
{
	return false;
}

void Level::renderMap(Shader* shader)
{
	transform newTransform;
	newTransform.position = glm::vec3(0.0f);
	newTransform.orientation = glm::quat(1.0, 0.0, 0.0, 0.0);
	newTransform.scale = glm::vec3(0.4f,0.03,0.4f);

	this->levelShader = shader;
	this->levelScene->addObjectToScene(this->levelModel, newTransform, shader);
}

//debug only--------------------------------------------
void Level::setLevelModel(std::string filepath)
{
	this->name = "level1";
	this->levelModel = ResourceManager::loadModel(filepath,this->name);
	levelModel->meshes;
	for(unsigned int i = 0; i <levelModel->meshes.size(); i++)
	{
		this->levelMeshes.push_back(&levelModel->meshes[i]);
	}
	//this->rigidBodyId = this->world->CreateRigidBody();
	//createColliders();
	generateHeightMapForPlayer();
	this->rigidBodyId = world->createConcaveRigidbody(glm::vec3(0.0f), glm::quat(1.0, 0.0, 0.0, 0.0), this->vertices, this->indices);
	
}

void Level::addMeshToLevel(std::string filepath, glm::vec3 position, glm::quat orientation)
{
	
}

std::string Level::addObjectToLevel(std::string filePath, glm::vec3 position, glm::quat orientation, std::string name)
{
	std::string newObjectID = "null";


	return newObjectID;
}

void Level::addLightToLevel(glm::vec3 position, glm::vec3 direction, float brightness, glm::vec3 color)
{

}

void Level::setSkybox(std::vector <std::string> filePaths)
{

}

void Level::setLevelScene(scene* scene)
{
	this->levelScene = scene;
}

void Level::setLevelPhysicsWorld(PhysicsWorld* world)
{
	this->world = world;
}
//------------------------------------------------------
void Level::createColliders()
{
	for(unsigned int i = 0; i < this->levelMeshes.size(); i++)
	{
		Mesh* mesh = levelMeshes[i];
		std::vector <glm::vec3> vertices;
		for(unsigned int j = 0; j < mesh->vertices.size(); j++)
		{
			Vertex* vert = &mesh->vertices[j];
			vertices.push_back(vert->vertexPosition);
		}
		mesh->indices;
		
			this->world->attachConcaveColliderToBody(convexMesh, glm::vec3(0, 0, 0), glm::quat(1, 0, 0, 0), vertices, mesh->indices,this->rigidBodyId);
		
	}

}

void Level::parseLevelFile(std::string filePath)
{
	//to do:
}

float Level::getHeightAtPosition(glm::vec3 position)
{
	float height = 0;
	for(unsigned int i = 0; i < tiles.size(); i++)
	{
		terrainTile* tempTile = &tiles[i];
		//check position against tiles
		std::vector <glm::vec3> tempVec;
		tempVec.push_back(tempTile->Triangle1.point1);
		tempVec.push_back(tempTile->Triangle1.point2);
		tempVec.push_back(tempTile->Triangle1.point3);
		tempVec.push_back(tempTile->Triangle2.point1);
		tempVec.push_back(tempTile->Triangle2.point2);
		tempVec.push_back(tempTile->Triangle2.point3);

		glm::vec2 min = glm::vec2(tempTile->Triangle1.point1.x, tempTile->Triangle1.point1.z);
		glm::vec2 max = glm::vec2(tempTile->Triangle1.point1.x, tempTile->Triangle1.point1.z);

		for(unsigned int j = 0; j < tempVec.size();j++)
		{
			if (tempVec[j].x < min.x) { min.x = tempVec[j].x; }
			if (tempVec[j].z < min.y) { min.y = tempVec[j].z; }
			if (tempVec[j].x > max.x) { max.x = tempVec[j].x; }
			if (tempVec[j].z > max.y) { max.y = tempVec[j].z; }
		}

		if(position.x > min.x && position.x < max.x && position.z > min.y && position.z < max.y)
		{
			height = tiles[i].averageHeight;

		}

	}

	return height;
}

void Level::generateHeightMapForPlayer()
{
	//push back vertices and indices from all world model meshes
	for(unsigned int i = 0; i < this->levelModel->meshes.size(); i++)
	{
		for(unsigned int j = 0; j < this->levelModel->meshes[i].vertices.size(); j++)
		{
			vertices.push_back(this->levelModel->meshes[i].vertices[j].vertexPosition);
		}

		for(unsigned int j = 0; j < this->levelModel->meshes[i].indices.size(); j++)
		{
			indices.push_back(this->levelModel->meshes[i].indices[j]);
		}
	}

	//generate terrain faces;
	for(unsigned int i = 0; i < this->indices.size(); i += 6)
	{
		if(i < indices.size())
		{
			glm::vec3 p1 = vertices[indices[i]];
			glm::vec3 p2 = vertices[indices[i + 1]];
			glm::vec3 p3 = vertices[indices[i + 2]];

			glm::vec3 p4 = vertices[indices[i + 3]];
			glm::vec3 p5 = vertices[indices[i + 4]];
			glm::vec3 p6 = vertices[indices[i + 5]];

			float averageHeight = p1.y + p2.y + p3.y + p4.y + p5.y + p6.y;
			averageHeight /= 6;

			terrainTile newTile;
			triangle triangle1(p1,p2,p3);
			triangle triangle2(p4,p5,p6);

			newTile.Triangle1 = triangle1;
			newTile.Triangle2 = triangle2;
			newTile.averageHeight = averageHeight;

			this->tiles.push_back(newTile);
		}
	}


}