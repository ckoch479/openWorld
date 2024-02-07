#include "GameObject.h"

GameObject::GameObject()
{
	this->objectScale = glm::vec3(1.0);
	this->objectName = "default";
}

GameObject::~GameObject()
{
	
}

void GameObject::LoadObjectFromFile(std::string filepath, std::string objectName)
{
	this->modelingData = ResourceManager::loadModel(filepath, objectName);
	this->objectName = objectName;
}

void GameObject::addObjectToScene(Shader& shader, Scene* scene, PhysicsWorld* world)
{
	this->sceneModelID = scene->createModel(*modelingData, shader);
	this->sceneTransformID = scene->createTransform(world->getBodyPosition(this->rigidBodyID), world->getBodyRotationOrigin(this->rigidBodyID),world->getBodyOrientation(this->rigidBodyID), objectScale);

	this->sceneObjectID = scene->AddInstance(this->sceneModelID, this->sceneTransformID);
}

void GameObject::removeObjectFromScene(Scene* scene)
{
	scene->removeModelFromScene(this->sceneModelID);
}

void GameObject::CreateRigidBody(glm::vec3 position, float orientation, glm::vec3 rotationOrigin, float mass, PhysicsWorld* world)
{
	this->rigidBodyID = world->createRigidBody(position,orientation,rotationOrigin, mass);
}

void GameObject::AddtoPhysicsWorld(PhysicsWorld* world)
{
	this->physicsWorldObjectID = world->createPhysicsObject(this->rigidBodyID); //create physics object in the world
}

void GameObject::removeFromPhysicsWorld(PhysicsWorld* world)
{
	world->deletePhysicsObject(this->physicsWorldObjectID);
}

void GameObject::applyForce(glm::vec3 direction,PhysicsWorld* world)
{
	world->applyForce(this->rigidBodyID, direction);
}

void GameObject::setPosition(glm::vec3 position, PhysicsWorld* world)
{
	world->setPosition(this->rigidBodyID, position);
}

void GameObject::setRotation(glm::vec3 rotationOrigin, float rotation, PhysicsWorld* world)
{
	world->setRotation(this->rigidBodyID,rotation);
	world->setRotationOrigin(this->rigidBodyID,rotationOrigin);
}

void GameObject::setScaling(glm::vec3 scaling)
{
	this->objectScale = scaling;
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

void GameObject::updateTransforms(Scene* scene, PhysicsWorld* world)
{
	scene->updateTransform(this->sceneTransformID, world->getBodyPosition(this->rigidBodyID), world->getBodyRotationOrigin(this->rigidBodyID), world->getBodyOrientation(this->rigidBodyID), objectScale);
}