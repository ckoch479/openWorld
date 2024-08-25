#include "oneHandedRangedWeapon.h"

oneHandedRangedWeapon::oneHandedRangedWeapon(glm::vec3 pos, glm::quat orient, glm::vec3 scale, std::string name, Model* model, Shader* shader)
{
	this->entityName = name;
	this->itemShader = shader;
	this->itemModel = model;
	this->position = pos;
	this->orientation = orient;
	this->scale = scale;

	this->pos = &this->position;
	this->orient = &this->orientation;
	this->weaponScale = &this->scale;
	this->weaponModel = this->itemModel;
	this->weaponShader = this->itemShader;
	this->name = &this->entityName;

}