#include "GameObject.h"

GameObject::GameObject()
{

}

GameObject::~GameObject()
{

}

void GameObject::LoadObjectFromFile(std::string filepath, std::string objectName)
{
	this->modelingData = ResourceManager::loadModel(filepath, objectName);
}

void GameObject::addObjectToScene(Shader& shader, Scene* scene)
{
	scene->createModel(*modelingData, shader);
	this->sceneID = scene->AddInstance(*modelingData, this->currentTransform);
}

void GameObject::removeObjectFromScene()
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

void GameObject::setAnimation(RenderAnimation* animation)
{

}

void GameObject::setAnimation(ID animationID)
{

}

void GameObject::calculateOBBDataFromBones()
{

}

void GameObject::calculateTransform()
{

}