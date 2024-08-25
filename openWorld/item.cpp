#include "item.h"

item::item()
{
	this->positionPtr = &this->position;
	this->orientPtr = &this->orientation;
	this->scalePtr = &this->scale;
	this->itemModel = nullptr;
}

item::item(Model* model, Shader* itemShader)
{
	this->positionPtr = &this->position;
	this->orientPtr = &this->orientation;
	this->scalePtr = &this->scale;
	this->itemModel = model;
	this->itemShader = itemShader;
}

item::~item()
{

}