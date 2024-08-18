#pragma once

#include "includes/glm/glm.hpp"
#include "Includes/glm/gtc/type_ptr.hpp"

#include <vector>
#include <string>

#include "Mesh.h"
#include "skeleton.h"

struct Model
{
	std::vector <Mesh> meshes;
	skeleton* skeleton;
	std::string name;
	std::vector <glm::mat4> animationMatrices; //temporary im thinking
};