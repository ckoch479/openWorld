#include "handGun.h"

handGun::handGun(std::string filePath, float baseDamage, glm::vec3 handPoint, std::string name, glm::vec3 barrelPos, glm::vec3 front)
{
	this->model = ResourceManager::loadModel(filePath,name);
	this->baseDamage = baseDamage;
	this->handPoint1 = glm::vec3(this->model->boneMap["handle"].offsetMatrix * glm::vec4(1,1,1,1));// handPoint; //not working currently
	this->twoHanded = false;
	this->barrel = barrelPos;
	this->front = front;
	this->chambered = false;
	this->hasMagazine = false;

	this->name = name;
	this->consumable = false;
	this->equipable = true;
	this->stackable = false;
	this->mass = 10;
	this->volume = this->mass;

	//std::cout << "hand gun handle: " << glm::to_string(this->model->boneMap["handle"].offsetMatrix) << std::endl;

}

handGun::~handGun()
{

}

glm::vec3 handGun::getBarrelPos()
{
	return this->barrel;
}

glm::vec3 handGun::getDirection()
{
	return this->front;
}

glm::mat4 handGun::getTransform()
{
	return this->worldTransform;
}

void handGun::setTransform(glm::mat4 transf)
{
	this->worldTransform = transf;
}