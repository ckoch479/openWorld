#pragma once

#include <vector>
#include <string>

#include "Material.h"
#include "Vertex.h"

struct Mesh
{
	std::vector <Vertex> vertices;
	std::vector <unsigned int> indices;
	Material material; 
	unsigned int VAO;//for rendering
	unsigned int VBO;
	unsigned int EBO;
};