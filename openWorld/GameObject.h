#pragma once

#include <iostream>
#include <vector>
#include <map>

#include "includes/glm/glm.hpp"
#include "Includes/glm/gtc/type_ptr.hpp"

#include "ResourceManager.h"
#include "Collider.h"
#include "RigidBody.h"

#include "Scene.h"

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
class GameObject
{
public:

	GameObject();

	~GameObject();

	void LoadObjectFromFile(std::string filepath,std::string objectName); //load gameObject using resource manager

	void addObjectToScene(Shader& shader);

	void removeObjectFromScene();

	void applyForce(glm::vec3 direction, float force);

	void setPosition(glm::vec3 position); //used to overRide transform data created from physics engine

	void setRotation(glm::vec3 rotationOrigin, glm::quat rotation); //used to overRide transform data created from physics engine

	void setScaling(glm::vec3 scaling);  //used to overRide transform data created from physics engine

	void setAnimation(RenderAnimation* animation);

	void setAnimation(ID animationID);

private:

	void calculateOBBDataFromBones();

	void calculateTransform();

	Transform currentTransform;

	//rendering info
	ModelData* modelingData; //data from resource manager about rendering, skeleton info, ect
	ID sceneID;

	RenderAnimation* animation;//current animation for this object, allows for the OBBs to be updated accordingly
	//physics and collision info
	std::vector <OBB*> orientedBoundingBoxes; //oriented bounding boxes based off the vertices and bones of the model, 1 OBB per bone
	RigidBody* body; // rigid body of the game object, this contains data needed to determine physics of the object

};
#endif

