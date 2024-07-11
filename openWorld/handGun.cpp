#include "handGun.h"

handGun::handGun(std::string filePath, std::string name, float mass, float volume)
{
	this->model = ResourceManager::loadModel(filePath,name);

	this->name = name;
	this->mass = mass;
	this->volume = volume;

	transform newTransform;
	newTransform.position = glm::vec3(0.0f);
	newTransform.orientation = glm::quat(1.0, 0.0, 0.0, 0.0);
	newTransform.scale = glm::vec3(0.01f);

	this->sceneTransform = newTransform;
}

handGun::~handGun()
{

}

void handGun::addToScene(scene* scene, Shader* shader)
{
	this->sceneID = scene->addObjectToScene(this->model, this->sceneTransform, shader);

	std::cout << "handgun being added to scene\n";
}

void handGun::updateTransform(scene* scene, transform newTransform)
{
	this->sceneTransform = newTransform; //+ this->localTransform;
	sceneTransform.scale = glm::vec3(0.01f);
	scene->updateTransform(this->sceneID, this->sceneTransform);
}

