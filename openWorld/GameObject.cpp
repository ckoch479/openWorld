#include "GameObject.h"

GameObject::GameObject()
{
	this->objectScale = glm::vec3(1.0);
	this->objectName = "default";
	this->Position = glm::vec3(1.0,1.0,1.0);
	
}

GameObject::~GameObject()
{
	
}
//object loading-------------------------------------------------------------------
void GameObject::LoadObjectFromFile(std::string filepath, std::string objectName)
{
	this->modelingData = ResourceManager::loadModel(filepath, objectName);
	
	for(unsigned int i = 0; i < modelingData->meshes.size();i++)
	{
		MeshData tempMesh = modelingData->meshes[i];

			for(unsigned int j = 0; j < tempMesh.vertices.size(); j++)
			{
				glm::vec3 tempVec = tempMesh.vertices[j].vertexPosition;
				this->objectMeshData.push_back(tempVec);
			}
	}

	this->objectName = objectName;
}

//rendering---------------------------------------------------------------------------------
void GameObject::addObjectToScene(Shader& shader, Scene* scene, PhysicsWorld* world)
{
	this->sceneModelID = scene->createModel(*modelingData, shader);
	this->sceneTransformID = scene->createTransform(this->Position, rotation, objectScale);

	this->sceneObjectID = scene->AddInstance(this->sceneModelID, this->sceneTransformID);
}

void GameObject::removeObjectFromScene(Scene* scene)
{
	scene->removeModelFromScene(this->sceneModelID);
}

//physics handling----------------------------------------------------------------------

void GameObject::addObjectToPhysicsWorld(PhysicsWorld* world)
{
this->physicsWorldObjectID = world->createPhysicsObject(this->objectMeshData, this->Position, this->rotation);
std::cout << "object added to physics world!\n";
}

void GameObject::addForce(glm::vec3 force, PhysicsWorld* world)
{
	world->applyForce(this->physicsWorldObjectID, force);
}

void GameObject::updateTransforms(Scene* scene, PhysicsWorld* world)
{
	this->Position = world->getBodyPosition(this->physicsWorldObjectID);
	this->rotation = world->getBodyOrientation(this->physicsWorldObjectID);

	std::cout << Position.x << " " << Position.y << " " << Position.z << std::endl;
	
	scene->updateTransform(this->sceneTransformID, this->Position, this->rotation, this->objectScale);
}

void GameObject::setPosition(glm::vec3 newPosition)
{
	this->Position = newPosition;
}