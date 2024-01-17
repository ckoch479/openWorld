#include "GameObject.h"

GameObject::GameObject()
{
	this->objectScale = glm::vec3(1.0f);
	this->body = new RigidBody;

	this->body->mass = 1.0f;
	this->body->acceleration = glm::vec3 (0.0f);
	this->body->position = glm::vec3(0.0,0.0,-2.0);
	this->body->orientation = glm::quat(0.0,0.0,0.0,0.0);
	this->body->rotationOrigin = glm::vec3(0, 1, 0);
	this->body->velocity = glm::vec3(0.0f);

	this->objectName = "default";
}

GameObject::~GameObject()
{
	delete this->body;
}

void GameObject::LoadObjectFromFile(std::string filepath, std::string objectName)
{
	this->modelingData = ResourceManager::loadModel(filepath, objectName);
	this->objectName = objectName;
}

void GameObject::addObjectToScene(Shader& shader, Scene* scene)
{
	this->sceneModelID = scene->createModel(*modelingData, shader);
	this->sceneTransformID = scene->createTransform(body->position,body->rotationOrigin, body->orientation, objectScale);

	this->sceneObjectID = scene->AddInstance(this->sceneModelID, this->sceneTransformID);
}

void GameObject::removeObjectFromScene(Scene* scene)
{
	scene->removeModelFromScene(this->sceneModelID);
}

void GameObject::AddtoPhysicsWorld()
{

}

void GameObject::removeFromPhysicsWorld()
{

}

void GameObject::applyForce(glm::vec3 direction, float force)
{

}

void GameObject::setPosition(glm::vec3 position)
{

}

void GameObject::setRotation(glm::vec3 rotationOrigin, glm::quat rotation)
{

}

void GameObject::setScaling(glm::vec3 scaling)
{

}

//for animations be sure to create a scene object first or the an error will be thrown
void GameObject::setAnimation(AnimationData* animation, Scene* scene)
{
	this->renderAnimationID = scene->createAnimation(animation, this->objectName + "animation");
	scene->UpdateAnimation(this->sceneModelID, renderAnimationID);
}

void GameObject::setAnimation(ID animationID, Scene* scene)
{
	this->renderAnimationID = animationID;
	scene->UpdateAnimation(this->sceneModelID, renderAnimationID);
}

void GameObject::calculateOBBDataFromBones()
{
	//count the number of boxes needed (1 per bone)
	
	this->modelingData->skeleton;


	// take each bone and find all vertices it affects then find the furthest points of these vertices
	//create a box using the vertices generated above then apply the bones transform to them


}

void GameObject::calculateTransform()
{

}