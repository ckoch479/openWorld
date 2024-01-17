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

#include "Scene.h"

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
class GameObject
{
public:

	GameObject();

	~GameObject();

	void LoadObjectFromFile(std::string filepath,std::string objectName); //load gameObject using resource manager

	void addObjectToScene(Shader& shader, Scene* scene);

	void removeObjectFromScene(Scene* scene);

	void AddtoPhysicsWorld();

	void removeFromPhysicsWorld();

	void applyForce(glm::vec3 direction, float force);

	void setPosition(glm::vec3 position); //used to overRide transform data created from physics engine

	void setRotation(glm::vec3 rotationOrigin, glm::quat rotation); //used to overRide transform data created from physics engine

	void setScaling(glm::vec3 scaling);  //used to overRide transform data created from physics engine

	void setAnimation(AnimationData* animation, Scene* scene);

	void setAnimation(ID animationID, Scene* scene);

private:

	void calculateOBBDataFromBones();

	void calculateTransform();

	//rendering info
	ModelData* modelingData; //data from resource manager about rendering, skeleton info, ect

	ID sceneObjectID;
	ID sceneModelID;
	ID renderAnimationID;

	//physics and collision info
	std::vector <orientedBoundingBox*> orientedBoundingBoxes; //oriented bounding boxes based off the vertices and bones of the model, 1 OBB per bone
	RigidBody* body; // rigid body of the game object, this contains data needed to determine physics of the object

	ID sceneTransformID;
	glm::vec3 objectScale;

	std::string objectName;

};
#endif

