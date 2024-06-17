#pragma once

#include "vector"
#include <iostream>

#include "includes/glm/glm.hpp"
#include "Includes/glm/gtc/type_ptr.hpp"

#include "PhysicsWorld.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "Shader.h"

//level objects are objects that may or may not be dynamically simulation but does not include things like enemies or the player
struct levelObject
{
	std::string id;
	ModelData* model;
	rigidBody* body;

	ID worldModelID; //for rendering
	ID instanceID;
	ID transformID;
};

//level trigger is basically just a regular trigger, triggers can either change the level or activate a spawn, or ect;
struct LevelTrigger
{
	glm::vec3 position;
	glm::quat orientation;
	glm::vec3 halfExtents;
	bool hasBeenTrigged;
};

struct LevelSkyBox
{
	std::vector <std::string> filePaths; //file paths for skybox textures
};

#ifndef LEVEL_H
#define LEVEL_H

//this is a game level, it is in charge of it's terrain, all objects inside of this level and loading a level from a file
//this level class is responsible for loading level meshes from a file and then generating the levels colliders
class Level
{
public:
	
	Level();

	Level(std::string filePath, std::string levelName,Shader* shader);

	~Level();

	void LoadLevelFromFile(std::string filePath, Shader* shader);

	std::string addObjectToLevel(std::string filePath, glm::vec3 position); //for later gameObject loading from a file

	std::string addTriggerToMap(glm::vec3 position, glm::quat orientation, glm::vec3 halfExtents); //create a trigger return its id (trigger001)

	bool hasTriggerBeenActivated(std::string triggerName);

	void renderMap(Shader* shader);

	//for debug only------------------------
	void setLevelModel(std::string filepath); 

	void addMeshToLevel(std::string filepath, glm::vec3 position, glm::quat orientation);

	std::string addObjectToLevel(std::string filePath, glm::vec3 position, glm::quat orientation, std::string name); //this returns its id

	void addLightToLevel(glm::vec3 position, glm::vec3 direction, float brightness, glm::vec3 color);

	void setSkybox(std::vector <std::string> filePaths);

	void setLevelScene(Scene* scene);

	void setLevelPhysicsWorld(PhysicsWorld* world);

	//--------------------------------------
private:

	std::vector <levelObject> levelObjects; //vector of all objects in the level

	//mRigidBody levelBody;//this is to store all colliders used by this level

	ModelData* levelModel;
	std::vector <MeshData*> levelMeshes; //makes it easier to calculate hitboxes and such for the level

	ID worldModelID; //for rendering
	ID instanceID;
	ID transformID;
	unsigned int rigidBodyId;

	std::map <std::string, LevelTrigger> levelTriggers;

	std::string name; //name of the level its self

	Shader* levelShader;
	Scene* levelScene;
	PhysicsWorld* world;

	void parseLevelFile(std::string filePath);
	
	void createColliders();
};

#endif // !LEVEL_H