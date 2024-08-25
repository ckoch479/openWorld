#pragma once

#include <iostream>

#include "includes/glm/glm.hpp"
#include "Includes/glm/gtc/type_ptr.hpp"
#include "Includes/glm/gtc/quaternion.hpp"
#include <glm/gtx/string_cast.hpp>

#include "Entity.h"

#include "Model.h"

#ifndef ITEM_H
#define ITEM_H

class item : public Entity
{
public:

	item();

	item(Model* model, Shader* itemShader);

	~item();

	virtual void update() {};

	virtual void equip() {};

	virtual void unEquip() {};

	virtual void use() {};

	virtual Model* getModel() { return this->itemModel; }

	virtual glm::vec3* getPos() { return this->positionPtr; };

	virtual glm::quat* getOrient() { return this->orientPtr;};

	virtual glm::vec3* getScale() { return this->scalePtr; };

	virtual Shader* getShader() { return this->itemShader; }

protected:
	
	glm::vec3* positionPtr;
	glm::quat* orientPtr;
	glm::vec3* scalePtr;

	Model* itemModel;
	Shader* itemShader; //needed for rendering unless i keep all shaders in scene/renderer

private:

	
};

#endif // !ITEM_H