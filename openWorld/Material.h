#pragma once

#include "Texture.h"

//not the best way to do this i think but it works for now will revisit later
struct textureData //named such to differentiate between just the data and an actual texture object
{
	std::string filePath;	//path to load the texture from
	std::string uniqueName; //for resource manager, textures arent attached fully to mesh allows reused textures to only be loaded once
};

struct Material
{
	Texture* diffuse0;
	textureData diffuseData;
	Texture* specular0;
	textureData specularData;
	Texture* normalMap0;
	textureData normalData;

	float shininess;
};