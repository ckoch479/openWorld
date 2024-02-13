#pragma once

#include <iostream>
#include <vector>
#include <map>

#include "includes/glm/glm.hpp"
#include "Includes/glm/gtc/type_ptr.hpp"
#include "Includes/glm/gtc/quaternion.hpp"

#include "ResourceManager.h"

#ifndef WORLDGENERATOR_H
#define WORLDGENERATOR_H

struct biomes 
{

};

struct Corner
{
	int index;

	glm::vec3 position;
	bool ocean;
	bool water;
	bool coast;
	bool border;
	int moisture;

	std::vector <Center*> touches;
	std::vector <Edge*> protrudes;
	std::vector <Corner*> adjacent;

	int river;
	Corner* downslope;
	Corner* waterShed;
	int waterShedSize;
};

struct Center
{
	int index;

	glm::vec3 point; //position
	bool water;
	bool ocean;
	bool coast;
	bool border;
	biomes biome;
	int moisture; //how humid or wet the biome is

	std::vector <Center*> neighbors;
	std::vector <Edge*> borders;
	std::vector <Corner*> corners;
};

struct Edge 
{
	int index;
	Center* d0, d1; //Delaunay edge
	Corner* v0, v1; //Voronoi edge
	glm::vec3 midPoint;
	int river;
};

struct Tile 
{
	//four corners and four edges

};


class worldGenerator
{
public:

	worldGenerator();
	~worldGenerator();

private:


};

#endif