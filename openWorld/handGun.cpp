#include "handGun.h"

handGun::handGun(std::string filePath, std::string name, float mass, float volume)
{
	this->model = ResourceManager::loadModel(filePath,name);

	this->name = name;
	this->mass = mass;
	this->volume = volume;

	glm::mat4 newTran(1.0f);
	newTran = glm::translate(newTran, glm::vec3(-1.0f, 0.0f, 0.0f));
	newTran = glm::rotate(newTran, glm::radians(94.0f), glm::vec3(1, 0, 0));
	newTran = glm::rotate(newTran, glm::radians(185.0f), glm::vec3(0, 1, 0));

	this->objectTransform = newTran;
}

handGun::~handGun()
{

}

void handGun::addToScene(scene* scene, Shader* shader)
{
	transform newTransform;
	newTransform.position = glm::vec3(0.0f);
	newTransform.orientation = glm::quat(1.0, 0.0, 0.0, 0.0);
	newTransform.scale = glm::vec3(0.01);

	this->sceneID = scene->addObjectToScene(this->model, newTransform, shader);

	std::cout << "handgun being added to scene\n";
}

void handGun::updateTransform(scene* scene, transform newTransform)
{	
	scene->updateTransform(this->sceneID, newTransform);
}

