#pragma once

#include <iostream>
#include <vector>
#include <map>

#include "includes/glm/glm.hpp"
#include "Includes/glm/gtc/type_ptr.hpp"
#include "Includes/glm/gtc/quaternion.hpp"

#include "ResourceManager.h"
#include "Collider.h"
#include "RigidBody.h"
#include "physicsWorld.h"

#include "Scene.h"

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
class GameObject
{
public:

	GameObject();

	~GameObject();

	void LoadObjectFromFile(std::string filepath,std::string objectName); //load gameObject using resource manager

	void addObjectToScene(Shader& shader, Scene* scene, PhysicsWorld* world);

	void removeObjectFromScene(Scene* scene);

	void addObjectToPhysicsWorld(PhysicsWorld* world);

	void addForce(glm::vec3 force, PhysicsWorld* world);

	void updateTransforms(Scene* scene, PhysicsWorld* world);

	void setPosition(glm::vec3 newPosition);

private:

	//rendering info
	ModelData* modelingData; //data from resource manager about rendering, skeleton info, ect

	ID sceneObjectID;
	ID sceneModelID;
	ID renderAnimationID;
	ID sceneTransformID;

	ID physicsWorldObjectID;

	glm::vec3 Position;

	glm::quat rotation;

	glm::vec3 objectScale;

	std::string objectName;

	std::vector <glm::vec3> objectMeshData;

};
#endif

