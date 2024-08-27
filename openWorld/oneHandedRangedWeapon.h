#pragma once

#include <iostream>

#include "item.h"


class oneHandedRangedWeapon : public item
{
public:

	oneHandedRangedWeapon(glm::vec3 pos, glm::quat orient, glm::vec3 scale, std::string name, Model* model, Shader* shader);

	void use();

private:

	std::string* name;

	glm::vec3* pos;
	glm::quat* orient;
	glm::vec3* weaponScale;

	//glm::vec3 front;

	Model* weaponModel;
	Shader* weaponShader;
};

