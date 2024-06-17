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
	this->levelShader = shader;
	this->transformID = this->levelScene->createTransform(glm::vec3(0.0f),glm::quat(),glm::vec3(1.0f));
	this->worldModelID = this->levelScene->createModel(*this->levelModel,*this->levelShader);
	this->instanceID = this->levelScene->AddInstance(this->worldModelID,this->transformID);
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
	this->rigidBodyId = this->world->CreateRigidBody();
	createColliders();
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

void Level::setLevelScene(Scene* scene)
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
		MeshData* mesh = levelMeshes[i];
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