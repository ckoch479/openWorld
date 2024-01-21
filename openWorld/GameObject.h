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

	void CreateRigidBody(glm::vec3 position, glm::quat orientation, glm::vec3 rotationOrigin, float mass, PhysicsWorld* world);

	void AddtoPhysicsWorld(PhysicsWorld* world);

	void removeFromPhysicsWorld(PhysicsWorld* world);

	void applyForce(glm::vec3 direction, PhysicsWorld* world);

	void setPosition(glm::vec3 position, PhysicsWorld* world); //used to overRide transform data created from physics engine

	void setRotation(glm::vec3 rotationOrigin, glm::quat rotation, PhysicsWorld* world); //used to overRide transform data created from physics engine

	void setScaling(glm::vec3 scaling);  //used to overRide transform data created from physics engine

	void setAnimation(AnimationData* animation, Scene* scene);

	void setAnimation(ID animationID, Scene* scene);

	void updateTransforms(Scene* scene, PhysicsWorld* world);

private:

	//rendering info
	ModelData* modelingData; //data from resource manager about rendering, skeleton info, ect

	ID sceneObjectID;
	ID sceneModelID;
	ID renderAnimationID;
	ID sceneTransformID;

	ID physicsWorldObjectID;
	ID rigidBodyID;

	//physics and collision info
	std::vector <orientedBoundingBox> orientedBoundingBoxes; //oriented bounding boxes based off the vertices and bones of the model, 1 OBB per bone
	
	glm::vec3 objectScale;

	std::string objectName;

};
#endif

