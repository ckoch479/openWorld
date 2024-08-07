#include "handGun.h"

handGun::handGun(std::string filePath, std::string name, float mass, float volume)
{
	this->model = ResourceManager::loadModel(filePath,name);

	this->name = name;
	this->mass = mass;
	this->volume = volume;

	this->objectTransform = glm::mat4(1.0f);
	this->objectTransform = glm::translate(this->objectTransform, glm::vec3(0, 0, 0));
	this->objectTransform = glm::rotate(this->objectTransform, 0.0f, glm::vec3(0,0,0));
	this->objectTransform = glm::scale(this->objectTransform, glm::vec3(0.01, 0.01, 0.01));

	//transform newTransform;
	//newTransform.position = glm::vec3(0.0f);
	//newTransform.orientation = glm::quat(1.0, 0.0, 0.0, 0.0);
	//newTransform.scale = glm::vec3(0.01f);

	//glm::vec3 skew;
	//glm::vec4 perspective;

	//glm::decompose(this->objectTransform, newTransform.scale, newTransform.orientation, newTransform.position, skew, perspective);

	//this->sceneTransform = newTransform;
}

handGun::~handGun()
{

}

void handGun::addToScene(scene* scene, Shader* shader)
{
	transform newTransform;
	glm::vec3 skew;
	glm::vec4 perspective;

	glm::decompose(this->objectTransform, newTransform.scale, newTransform.orientation, newTransform.position, skew, perspective);


	this->sceneID = scene->addObjectToScene(this->model, newTransform, shader);

	std::cout << "handgun being added to scene\n";
}

void handGun::updateTransform(scene* scene, glm::mat4 newTransform)
{
	glm::mat4 totalTransform = newTransform;// *this->objectTransform;

	transform decompTransform;
	glm::vec3 skew;
	glm::vec4 perspective;

	glm::decompose(totalTransform, decompTransform.scale, decompTransform.orientation, decompTransform.position, skew, perspective);


	decompTransform.scale = glm::vec3(0.01);
	scene->updateTransform(this->sceneID, decompTransform);
}

