#pragma once

#include <iostream>

#include "includes/glm/glm.hpp"
#include "Includes/glm/gtc/type_ptr.hpp"

#include "renderingInfoDefinitions.h"


#ifndef SHAPEGENERATOR_H
#define SHAPEGENERATOR_H

class ShapeGenerator
{
public:

	ShapeGenerator();
	~ShapeGenerator();

	shape2D generateCharacter(char letter, float width, float height, glm::vec4 RGBA);

	shape2D generateBox(float width, float height, glm::vec4 RGBA);

	shape2D generateCircle(float radius,glm::vec4 RGBA, float numSegments);

	shape2D generateTriangle(float width, float height, glm::vec4 RGBA);

private:


	//each letter generated is down here dont look at it, its gross i know
	shape2D generateLetterA(float width, float height, glm::vec4 RGBA);

	shape2D generateLetterB(float width, float height, glm::vec4 RGBA);

	shape2D generateLetterC(float width, float height, glm::vec4 RGBA);

	shape2D generateLetterD(float width, float height, glm::vec4 RGBA);

	shape2D generateLetterE(float width, float height, glm::vec4 RGBA);
	
	shape2D generateLetterF(float width, float height, glm::vec4 RGBA);
	
	shape2D generateLetterG(float width, float height, glm::vec4 RGBA);
	
	shape2D generateLetterH(float width, float height, glm::vec4 RGBA);
	
	shape2D generateLetterI(float width, float height, glm::vec4 RGBA);
	
	shape2D generateLetterJ(float width, float height, glm::vec4 RGBA);
	
	shape2D generateLetterK(float width, float height, glm::vec4 RGBA);
	
	shape2D generateLetterL(float width, float height, glm::vec4 RGBA);
	
	shape2D generateLetterM(float width, float height, glm::vec4 RGBA);
	
	shape2D generateLetterN(float width, float height, glm::vec4 RGBA);
	
	shape2D generateLetterO(float width, float height, glm::vec4 RGBA);
	
	shape2D generateLetterP(float width, float height, glm::vec4 RGBA);
	
	shape2D generateLetterQ(float width, float height, glm::vec4 RGBA);
	
	shape2D generateLetterR(float width, float height, glm::vec4 RGBA);
	
	shape2D generateLetterS(float width, float height, glm::vec4 RGBA);
	
	shape2D generateLetterT(float width, float height, glm::vec4 RGBA);
	
	shape2D generateLetterU(float width, float height, glm::vec4 RGBA);
	
	shape2D generateLetterV(float width, float height, glm::vec4 RGBA);
	
	shape2D generateLetterW(float width, float height, glm::vec4 RGBA);
	
	shape2D generateLetterX(float width, float height, glm::vec4 RGBA);
	
	shape2D generateLetterY(float width, float height, glm::vec4 RGBA);
	
	shape2D generateLetterZ(float width, float height, glm::vec4 RGBA);
};

#endif // !SHAPEGENERATOR_H