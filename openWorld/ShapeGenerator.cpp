#include "ShapeGenerator.h"

ShapeGenerator::ShapeGenerator()
{

}

ShapeGenerator::~ShapeGenerator()
{

}

shape2D ShapeGenerator::generateCharacter(char letter, float width, float height, glm::vec4 RGBA)
{
	shape2D newShape;
	
	newShape = generateCircle(width / 4, RGBA, 30); //if the letter given is invalid draw a circle first
	switch(letter)
	{
	case('a'):
	newShape = generateLetterA(width, height, RGBA);
		break;
	case('b'):
		newShape = generateLetterB(width, height, RGBA);
		break;
	case('c'):
		newShape = generateLetterC(width, height, RGBA);
		break;
	case('d'):
		newShape = generateLetterD(width, height, RGBA);
		break;
	case('e'):
		newShape = generateLetterE(width, height, RGBA);
		break;
	case('f'):
		newShape = generateLetterF(width, height, RGBA);
		break;
	case('g'):
		newShape = generateLetterG(width, height, RGBA);
		break;
	case('h'):
		newShape = generateLetterH(width, height, RGBA);
		break;
	case('i'):
		newShape = generateLetterI(width, height, RGBA);
		break;
	case('j'):
		newShape = generateLetterJ(width, height, RGBA);
		break;
	case('k'):
		newShape = generateLetterK(width, height, RGBA);
		break;
	case('l'):
		newShape = generateLetterL(width, height, RGBA);
		break;
	case('m'):
		newShape = generateLetterM(width, height, RGBA);
		break;
	case('n'):
		newShape = generateLetterN(width, height, RGBA);
		break;
	case('o'):
		newShape = generateLetterO(width, height, RGBA);
		break;
	case('p'):
		newShape = generateLetterP(width, height, RGBA);
		break;
	case('q'):
		newShape = generateLetterQ(width, height, RGBA);
		break;
	case('r'):
		newShape = generateLetterR(width, height, RGBA);
		break;
	case('s'):
		newShape = generateLetterS(width, height, RGBA);
		break;
	case('t'):
		newShape = generateLetterT(width, height, RGBA);
		break;
	case('u'):
		newShape = generateLetterU(width, height, RGBA);
		break;
	case('v'):
		newShape = generateLetterV(width, height, RGBA);
		break;
	case('w'):
		newShape = generateLetterW(width, height, RGBA);
		break;
	case('x'):
		newShape = generateLetterX(width, height, RGBA);
		break;
	case('y'):
		newShape = generateLetterY(width, height, RGBA);
		break;
	case('z'):
		newShape = generateLetterZ(width, height, RGBA);
		break;

	}

	return newShape;
}

shape2D ShapeGenerator::generateBox(float width, float height, glm::vec4 RGBA)
{
	shape2D newShape;

	std::vector <Vertex2D> screenData //a regular box
	{
	Vertex2D(-0.2 * width,-0.2 * height,RGBA),
	Vertex2D( 0.2 * width,-0.2 * height,RGBA),
	Vertex2D(-0.2 * width, 0.2 * height,RGBA),

	Vertex2D( 0.2 * width,-0.2 * height,RGBA),
	Vertex2D( 0.2 * width, 0.2 * height,RGBA),
	Vertex2D(-0.2 * width, 0.2 * height,RGBA)
	};

	newShape.vertices = screenData;
	return newShape;

}

shape2D ShapeGenerator::generateCircle(float radius, glm::vec4 RGBA, float numSegments)
{
	shape2D newShape;

	std::vector <Vertex2D> screenData; 

	for(int i = 0; i < numSegments; i++)
	{
		screenData.push_back(Vertex2D(0.0f, 0.0f, RGBA));

		float angle = 2.0f * 3.1415 * float(i) / float(numSegments); //current angle
		float x = radius * cosf(angle);
		float y = radius * sinf(angle);
		screenData.push_back(Vertex2D(x/2, y, RGBA));

		float angle2 = 2.0f * 3.1415 * float(i + 1) / float(numSegments);
		float x2 = radius * cosf(angle2);
		float y2 = radius * sinf(angle2);
		screenData.push_back(Vertex2D(x2/2, y2, RGBA));
	}
	
	newShape.vertices = screenData;
	return newShape;
}

shape2D ShapeGenerator::generateTriangle(float width, float height, glm::vec4 RGBA)
{
	shape2D newShape;

	std::vector <Vertex2D> screenData //a regular box
	{
	Vertex2D(-0.1 * width,-0.1 * height,RGBA),
	Vertex2D( 0.1 * width,-0.1 * height,RGBA),
	Vertex2D( 0.0 * width, 0.1 * height,RGBA),
	};

	newShape.vertices = screenData;
	return newShape;
}




//gross letters made down here
shape2D ShapeGenerator::generateLetterA(float width, float height, glm::vec4 RGBA)
{
	std::vector <Vertex2D> screenData //letter A
	{
	Vertex2D(-0.1 * width, 0.0 * height,RGBA),
	Vertex2D(-0.2 * width, 0.2 * height,RGBA),
	Vertex2D(-0.3 * width, 0.1 * height,RGBA),

	Vertex2D(-0.3* width, 0.0 * height,RGBA),
	Vertex2D(-0.1* width, 0.0 * height,RGBA),
	Vertex2D(-0.3* width, 0.1 * height,RGBA),

	Vertex2D(-0.3 * width,-0.6 * height,RGBA),
	Vertex2D(-0.1 * width, 0.0 * height,RGBA),
	Vertex2D(-0.3 * width, 0.0 * height,RGBA),

	Vertex2D(-0.3 * width,-0.6 * height,RGBA),
	Vertex2D(-0.1 * width,-0.6 * height,RGBA),
	Vertex2D(-0.1 * width, 0.0 * height,RGBA),

	Vertex2D(-0.1 * width,-0.2 * height,RGBA),
	Vertex2D( 0.1 * width,-0.4 * height,RGBA),
	Vertex2D( 0.1 * width,-0.2 * height,RGBA),

	Vertex2D(-0.1 * width,-0.4 * height,RGBA),
	Vertex2D( 0.1 * width,-0.4 * height,RGBA),
	Vertex2D(-0.1 * width,-0.2 * height,RGBA),

	Vertex2D(0.1 * width,-0.6 * height,RGBA),
	Vertex2D(0.3 * width,-0.6 * height,RGBA),
	Vertex2D(0.1 * width, 0.0 * height,RGBA),

	Vertex2D(0.1 * width, 0.0 * height,RGBA),
	Vertex2D(0.3 * width,-0.6 * height,RGBA),
	Vertex2D(0.3 * width, 0.0 * height,RGBA),

	Vertex2D(-0.1 * width, 0.0 * height,RGBA),
	Vertex2D( 0.3 * width, 0.0 * height,RGBA),
	Vertex2D( 0.3 * width, 0.1 * height,RGBA),

	Vertex2D(-0.1 * width, 0.0 * height,RGBA),
	Vertex2D( 0.3 * width, 0.1 * height,RGBA),
	Vertex2D( 0.2 * width, 0.2 * height,RGBA),

	Vertex2D(-0.1 * width, 0.0 * height,RGBA),
	Vertex2D( 0.2 * width, 0.2 * height,RGBA),
	Vertex2D(-0.2 * width, 0.2 * height,RGBA),

	};

	shape2D newShape;
	newShape.vertices = screenData;
	return newShape;
}

shape2D ShapeGenerator::generateLetterB(float width, float height, glm::vec4 RGBA) 
{
	shape2D newShape;

	std::vector <Vertex2D> screenData
	{
	Vertex2D(-0.3 * width,-0.4 * height,RGBA),
	Vertex2D(-0.1 * width,-0.4 * height,RGBA),
	Vertex2D(-0.3 * width, 0.4 * height,RGBA),

	Vertex2D(-0.1 * width,-0.4 * height,RGBA),
	Vertex2D(-0.1 * width, 0.4 * height,RGBA),
	Vertex2D(-0.3 * width, 0.4 * height,RGBA),

	Vertex2D(-0.1 * width, 0.3 * height,RGBA),
	Vertex2D(-0.1 * width, 0.4 * height,RGBA),
	Vertex2D( 0.3 * width, 0.3 * height,RGBA),

	Vertex2D(-0.1 * width, 0.4 * height,RGBA),
	Vertex2D( 0.3 * width, 0.3 * height,RGBA),
	Vertex2D( 0.2 * width, 0.4 * height,RGBA),

	Vertex2D( 0.1 * width, 0.1 * height,RGBA),
	Vertex2D( 0.3 * width, 0.1 * height,RGBA),
	Vertex2D( 0.1 * width, 0.3 * height,RGBA),

	Vertex2D( 0.1 * width, 0.3 * height,RGBA),
	Vertex2D( 0.3 * width, 0.1 * height,RGBA),
	Vertex2D( 0.3 * width, 0.3 * height,RGBA),

	Vertex2D(-0.1 * width, 0.1 * height,RGBA),
	Vertex2D( 0.2 * width, 0.0 * height,RGBA),
	Vertex2D( 0.3 * width, 0.1 * height,RGBA),

	Vertex2D(-0.1 * width, 0.1 * height,RGBA),
	Vertex2D(-0.1 * width,-0.1 * height,RGBA),
	Vertex2D( 0.2 * width, 0.0 * height,RGBA),

	Vertex2D(-0.1 * width,-0.1 * height,RGBA),
	Vertex2D( 0.3 * width,-0.1 * height,RGBA),
	Vertex2D( 0.2 * width, 0.0 * height,RGBA),

	Vertex2D( 0.1 * width,-0.1 * height,RGBA),
	Vertex2D( 0.1 * width,-0.3 * height,RGBA),
	Vertex2D( 0.3 * width,-0.3 * height,RGBA),

	Vertex2D( 0.1 * width,-0.1 * height,RGBA),
	Vertex2D( 0.3 * width,-0.3 * height,RGBA),
	Vertex2D( 0.3 * width,-0.1 * height,RGBA),

	Vertex2D(-0.1 * width,-0.3 * height,RGBA),
	Vertex2D(-0.1 * width,-0.4 * height,RGBA),
	Vertex2D( 0.3 * width,-0.3 * height,RGBA),

	Vertex2D(-0.1 * width,-0.4 * height,RGBA),
	Vertex2D( 0.2 * width,-0.4 * height,RGBA),
	Vertex2D( 0.3 * width,-0.3 * height,RGBA),
	};

	newShape.vertices = screenData;
	return newShape;
}

shape2D ShapeGenerator::generateLetterC(float width, float height, glm::vec4 RGBA) 
{
	shape2D newShape;

	std::vector <Vertex2D> screenData
	{
	Vertex2D(-0.1 * width, 0.4 * height,RGBA),
	Vertex2D( 0.3 * width, 0.3 * height,RGBA),
	Vertex2D( 0.3 * width, 0.4 * height,RGBA),

	Vertex2D(-0.1 * width, 0.4 * height,RGBA),
	Vertex2D(-0.1 * width, 0.3 * height,RGBA),
	Vertex2D( 0.3 * width, 0.3 * height,RGBA),

	Vertex2D(-0.2 * width, 0.4 * height,RGBA),
	Vertex2D(-0.1 * width, 0.3 * height,RGBA),
	Vertex2D(-0.1 * width, 0.4 * height,RGBA),

	Vertex2D(-0.3 * width, 0.3 * height,RGBA),
	Vertex2D(-0.1 * width, 0.3 * height,RGBA),
	Vertex2D(-0.2 * width, 0.4 * height,RGBA),
	
	Vertex2D(-0.3 * width, 0.3 * height,RGBA),
	Vertex2D(-0.2 * width, 0.2 * height,RGBA),
	Vertex2D(-0.1 * width, 0.3 * height,RGBA),

	Vertex2D(-0.3 * width,-0.3 * height,RGBA),
	Vertex2D(-0.2 * width,-0.2 * height,RGBA),
	Vertex2D(-0.2 * width, 0.2 * height,RGBA),
	
	Vertex2D(-0.3 * width,-0.3 * height,RGBA),
	Vertex2D(-0.1 * width,-0.3 * height,RGBA),
	Vertex2D(-0.2 * width,-0.2 * height,RGBA),

	Vertex2D(-0.3 * width,-0.3 * height,RGBA),
	Vertex2D(-0.2 * width,-0.4 * height,RGBA),
	Vertex2D(-0.1 * width,-0.3 * height,RGBA),

	Vertex2D(-0.2 * width,-0.4 * height,RGBA),
	Vertex2D( 0.3 * width,-0.3 * height,RGBA),
	Vertex2D(-0.1 * width,-0.3 * height,RGBA),

	Vertex2D(-0.2 * width,-0.4 * height,RGBA),
	Vertex2D( 0.3 * width,-0.4 * height,RGBA),
	Vertex2D( 0.3 * width,-0.3 * height,RGBA),

	Vertex2D(-0.3 * width, 0.3 * height,RGBA),
	Vertex2D(-0.3 * width,-0.3 * height,RGBA),
	Vertex2D(-0.2 * width, 0.2 * height,RGBA),
	};

	newShape.vertices = screenData;
	return newShape;
}

shape2D ShapeGenerator::generateLetterD(float width, float height, glm::vec4 RGBA) 
{
	shape2D newShape;

	std::vector <Vertex2D> screenData
	{
	Vertex2D(-0.3 * width, 0.4 * height,RGBA),
	Vertex2D(-0.3 * width,-0.4 * height,RGBA),
	Vertex2D(-0.1 * width,-0.4 * height,RGBA),

	Vertex2D(-0.3 * width, 0.4 * height,RGBA),
	Vertex2D(-0.1 * width,-0.4 * height,RGBA),
	Vertex2D(-0.1 * width, 0.4 * height,RGBA),

	Vertex2D(-0.1 * width, 0.4 * height,RGBA),
	Vertex2D(-0.1 * width, 0.2 * height,RGBA),
	Vertex2D( 0.0 * width, 0.2 * height,RGBA),

	Vertex2D(-0.1 * width, 0.4 * height,RGBA),
	Vertex2D( 0.0 * width, 0.2 * height,RGBA),
	Vertex2D( 0.0 * width, 0.4 * height,RGBA),

	Vertex2D( 0.0 * width, 0.4 * height,RGBA),
	Vertex2D( 0.0 * width, 0.2 * height,RGBA),
	Vertex2D( 0.2 * width, 0.3 * height,RGBA),

	Vertex2D( 0.0 * width, 0.2 * height,RGBA),
	Vertex2D( 0.1 * width, 0.1 * height,RGBA),
	Vertex2D( 0.2 * width, 0.3 * height,RGBA),

	Vertex2D( 0.2 * width, 0.3 * height,RGBA),
	Vertex2D( 0.1 * width, 0.1 * height,RGBA),
	Vertex2D( 0.3 * width, 0.1 * height,RGBA),

	Vertex2D( 0.1 * width, 0.1 * height,RGBA),
	Vertex2D( 0.1 * width,-0.1 * height,RGBA),
	Vertex2D( 0.3 * width, 0.1 * height,RGBA),

	Vertex2D( 0.1 * width,-0.1 * height,RGBA),
	Vertex2D( 0.3 * width,-0.1 * height,RGBA),
	Vertex2D( 0.3 * width, 0.1 * height,RGBA),

	Vertex2D( 0.0 * width,-0.2 * height,RGBA),
	Vertex2D( 0.3 * width,-0.1 * height,RGBA),
	Vertex2D( 0.1 * width,-0.1 * height,RGBA),

	Vertex2D( 0.0 * width,-0.2 * height,RGBA),
	Vertex2D( 0.2 * width,-0.3 * height,RGBA),
	Vertex2D( 0.3 * width,-0.1 * height,RGBA),

	Vertex2D( 0.0 * width,-0.2 * height,RGBA),
	Vertex2D( 0.0 * width,-0.4 * height,RGBA),
	Vertex2D( 0.2 * width,-0.3 * height,RGBA),

	Vertex2D(-0.1 * width,-0.2 * height,RGBA),
	Vertex2D( 0.0 * width,-0.4 * height,RGBA),
	Vertex2D( 0.0 * width,-0.2 * height,RGBA),

	Vertex2D(-0.1 * width,-0.2 * height,RGBA),
	Vertex2D(-0.1 * width,-0.4 * height,RGBA),
	Vertex2D( 0.0 * width,-0.4 * height,RGBA),


	};

	newShape.vertices = screenData;
	return newShape;
}

shape2D ShapeGenerator::generateLetterE(float width, float height, glm::vec4 RGBA) 
{
	shape2D newShape;

	std::vector <Vertex2D> screenData
	{
	Vertex2D(-0.1 * width, 0.1 * height,RGBA),
	Vertex2D(-0.1 * width,-0.1 * height,RGBA),
	Vertex2D( 0.1 * width,-0.1 * height,RGBA),

	Vertex2D(-0.1 * width, 0.1 * height,RGBA),
	Vertex2D( 0.1 * width,-0.1 * height,RGBA),
	Vertex2D( 0.1 * width, 0.1 * height,RGBA),

	Vertex2D(-0.3 * width,-0.4 * height,RGBA),
	Vertex2D( 0.3 * width,-0.4 * height,RGBA),
	Vertex2D( 0.3 * width,-0.2 * height,RGBA),

	Vertex2D(-0.3 * width,-0.2 * height,RGBA),
	Vertex2D(-0.3 * width,-0.4 * height,RGBA),
	Vertex2D( 0.3 * width,-0.2 * height,RGBA),

	Vertex2D(-0.3 * width, 0.2 * height,RGBA),
	Vertex2D(-0.3 * width,-0.2 * height,RGBA),
	Vertex2D(-0.1 * width,-0.2 * height,RGBA),

	Vertex2D(-0.3 * width, 0.2 * height,RGBA),
	Vertex2D(-0.1 * width,-0.2 * height,RGBA),
	Vertex2D(-0.1 * width, 0.2 * height,RGBA),

	Vertex2D(-0.3 * width, 0.4 * height,RGBA),
	Vertex2D(-0.3 * width, 0.2 * height,RGBA),
	Vertex2D( 0.3 * width, 0.2 * height,RGBA),

	Vertex2D(-0.3 * width, 0.4 * height,RGBA),
	Vertex2D( 0.3 * width, 0.2 * height,RGBA),
	Vertex2D( 0.3 * width, 0.4 * height,RGBA),
	};

	newShape.vertices = screenData;
	return newShape;
}

shape2D ShapeGenerator::generateLetterF(float width, float height, glm::vec4 RGBA) 
{
	shape2D newShape;

	std::vector <Vertex2D> screenData
	{
	Vertex2D(-0.1 * width, 0.1 * height,RGBA),
	Vertex2D( 0.1 * width,-0.1 * height,RGBA),
	Vertex2D( 0.1 * width, 0.1 * height,RGBA),

	Vertex2D(-0.1 * width, 0.1 * height,RGBA),
	Vertex2D(-0.1 * width,-0.1 * height,RGBA),
	Vertex2D( 0.1 * width,-0.1 * height,RGBA),

	Vertex2D(-0.3 * width, 0.4 * height,RGBA),
	Vertex2D(-0.3 * width,-0.4 * height,RGBA),
	Vertex2D(-0.1 * width,-0.4 * height,RGBA),

	Vertex2D(-0.3 * width, 0.4 * height,RGBA),
	Vertex2D(-0.1 * width,-0.4 * height,RGBA),
	Vertex2D(-0.1 * width, 0.4 * height,RGBA),

	Vertex2D(-0.1 * width, 0.4 * height,RGBA),
	Vertex2D(-0.1 * width, 0.2 * height,RGBA),
	Vertex2D( 0.3 * width, 0.2 * height,RGBA),

	Vertex2D(-0.1 * width, 0.4 * height,RGBA),
	Vertex2D( 0.3 * width, 0.2 * height,RGBA),
	Vertex2D( 0.3 * width, 0.4 * height,RGBA),
	};

	newShape.vertices = screenData;
	return newShape;
}

shape2D ShapeGenerator::generateLetterG(float width, float height, glm::vec4 RGBA) 
{
	shape2D newShape;

	std::vector <Vertex2D> screenData
	{
	Vertex2D( 0.0 * width, 0.0 * height,RGBA),
	Vertex2D( 0.0 * width,-0.1 * height,RGBA),
	Vertex2D( 0.2 * width, 0.0 * height,RGBA),

	Vertex2D( 0.0 * width,-0.1 * height,RGBA),
	Vertex2D( 0.2 * width,-0.1 * height,RGBA),
	Vertex2D( 0.2 * width, 0.0 * height,RGBA),

	Vertex2D( 0.2 * width, 0.0 * height,RGBA),
	Vertex2D( 0.2 * width,-0.3 * height,RGBA),
	Vertex2D( 0.3 * width, 0.0 * height,RGBA),

	Vertex2D( 0.2 * width,-0.3 * height,RGBA),
	Vertex2D( 0.3 * width,-0.3 * height,RGBA),
	Vertex2D( 0.3 * width, 0.0 * height,RGBA),

	Vertex2D(-0.1 * width,-0.3 * height,RGBA),
	Vertex2D( 0.3 * width,-0.4 * height,RGBA),
	Vertex2D( 0.3 * width,-0.3 * height,RGBA),

	Vertex2D(-0.1 * width,-0.3 * height,RGBA),
	Vertex2D( 0.0 * width,-0.4 * height,RGBA),
	Vertex2D( 0.3 * width,-0.4 * height,RGBA),

	Vertex2D(-0.2 * width,-0.2 * height,RGBA),
	Vertex2D(-0.2 * width,-0.4 * height,RGBA),
	Vertex2D( 0.0 * width,-0.4 * height,RGBA),

	Vertex2D(-0.3 * width,-0.3 * height,RGBA),
	Vertex2D(-0.2 * width,-0.4 * height,RGBA),
	Vertex2D(-0.2 * width, 0.2 * height,RGBA),

	Vertex2D(-0.3 * width,-0.3 * height,RGBA),
	Vertex2D(-0.2 * width, 0.2 * height,RGBA),
	Vertex2D(-0.3 * width, 0.3 * height,RGBA),

	Vertex2D(-0.3 * width, 0.3 * height,RGBA),
	Vertex2D(-0.2 * width, 0.2 * height,RGBA),
	Vertex2D(-0.1 * width, 0.3 * height,RGBA),

	Vertex2D(-0.3 * width, 0.3 * height,RGBA),
	Vertex2D( 0.3 * width, 0.3 * height,RGBA),
	Vertex2D(-0.2 * width, 0.4 * height,RGBA),

	Vertex2D(-0.2 * width, 0.4 * height,RGBA),
	Vertex2D( 0.3 * width, 0.3 * height,RGBA),
	Vertex2D( 0.3 * width, 0.4 * height,RGBA),
	};

	newShape.vertices = screenData;
	return newShape;
}

shape2D ShapeGenerator::generateLetterH(float width, float height, glm::vec4 RGBA) 
{
	shape2D newShape;

	std::vector <Vertex2D> screenData
	{
	Vertex2D(-0.1 * width, 0.1 * height,RGBA),
	Vertex2D( 0.1 * width,-0.1 * height,RGBA),
	Vertex2D( 0.1 * width, 0.1 * height,RGBA),

	Vertex2D(-0.1 * width, 0.1 * height,RGBA),
	Vertex2D(-0.1 * width,-0.1 * height,RGBA),
	Vertex2D( 0.1 * width,-0.1 * height,RGBA),

	Vertex2D(-0.3 * width, 0.4 * height,RGBA),
	Vertex2D(-0.1 * width,-0.4 * height,RGBA),
	Vertex2D(-0.1 * width, 0.4 * height,RGBA),

	Vertex2D(-0.3 * width, 0.4 * height,RGBA),
	Vertex2D(-0.3 * width,-0.4 * height,RGBA),
	Vertex2D(-0.1 * width,-0.4 * height,RGBA),

	Vertex2D( 0.1 * width, 0.4 * height,RGBA),
	Vertex2D( 0.1 * width,-0.4 * height,RGBA),
	Vertex2D( 0.3 * width, 0.4 * height,RGBA),

	Vertex2D( 0.3 * width, 0.4 * height,RGBA),
	Vertex2D( 0.1 * width,-0.4 * height,RGBA),
	Vertex2D( 0.3 * width,-0.4 * height,RGBA),
	};

	newShape.vertices = screenData;
	return newShape;
}

shape2D ShapeGenerator::generateLetterI(float width, float height, glm::vec4 RGBA) 
{
	shape2D newShape;

	std::vector <Vertex2D> screenData
	{
	Vertex2D(-0.1 * width, 0.2 * height,RGBA),
	Vertex2D(-0.1 * width,-0.2 * height,RGBA),
	Vertex2D( 0.1 * width,-0.2 * height,RGBA),

	Vertex2D(-0.1 * width, 0.2 * height,RGBA),
	Vertex2D( 0.1 * width,-0.2 * height,RGBA),
	Vertex2D( 0.1 * width, 0.2 * height,RGBA),

	Vertex2D(-0.3 * width, 0.4 * height,RGBA),
	Vertex2D(-0.3 * width, 0.2 * height,RGBA),
	Vertex2D( 0.3 * width, 0.2 * height,RGBA),

	Vertex2D(-0.3 * width, 0.4 * height,RGBA),
	Vertex2D( 0.3 * width, 0.2 * height,RGBA),
	Vertex2D( 0.3 * width, 0.4 * height,RGBA),

	Vertex2D(-0.3 * width,-0.2 * height,RGBA),
	Vertex2D( 0.3 * width,-0.4 * height,RGBA),
	Vertex2D( 0.3 * width,-0.2 * height,RGBA),

	Vertex2D(-0.3 * width,-0.2 * height,RGBA),
	Vertex2D(-0.3 * width,-0.4 * height,RGBA),
	Vertex2D( 0.3 * width,-0.4 * height,RGBA),
	};

	newShape.vertices = screenData;
	return newShape;
}

shape2D ShapeGenerator::generateLetterJ(float width, float height, glm::vec4 RGBA) 
{
	shape2D newShape;

	std::vector <Vertex2D> screenData
	{
	Vertex2D(-0.3 * width,-0.1 * height,RGBA),
	Vertex2D(-0.2 * width,-0.3 * height,RGBA),
	Vertex2D(-0.2 * width,-0.1 * height,RGBA),

	Vertex2D(-0.3 * width,-0.1 * height,RGBA),
	Vertex2D(-0.3 * width,-0.3 * height,RGBA),
	Vertex2D(-0.2 * width,-0.3 * height,RGBA),

	Vertex2D(-0.3 * width,-0.3 * height,RGBA),
	Vertex2D(-0.2 * width,-0.4 * height,RGBA),
	Vertex2D( 0.1 * width,-0.3 * height,RGBA),

	Vertex2D(-0.2 * width,-0.4 * height,RGBA),
	Vertex2D( 0.0 * width,-0.4 * height,RGBA),
	Vertex2D( 0.1 * width,-0.3 * height,RGBA),

	Vertex2D(-0.1 * width, 0.2 * height,RGBA),
	Vertex2D(-0.1 * width,-0.3 * height,RGBA),
	Vertex2D( 0.1 * width,-0.3 * height,RGBA),

	Vertex2D(-0.1 * width, 0.2 * height,RGBA),
	Vertex2D( 0.1 * width,-0.3 * height,RGBA),
	Vertex2D( 0.1 * width, 0.2 * height,RGBA),

	Vertex2D(-0.3 * width, 0.4 * height,RGBA),
	Vertex2D(-0.3 * width, 0.2 * height,RGBA),
	Vertex2D( 0.3 * width, 0.2 * height,RGBA),

	Vertex2D(-0.3 * width, 0.4 * height,RGBA),
	Vertex2D( 0.3 * width, 0.2 * height,RGBA),
	Vertex2D( 0.3 * width, 0.4 * height,RGBA),
	};

	newShape.vertices = screenData;
	return newShape;
}

shape2D ShapeGenerator::generateLetterK(float width, float height, glm::vec4 RGBA) 
{
	shape2D newShape;

	std::vector <Vertex2D> screenData
	{
	Vertex2D(-0.3 * width, 0.4 * height,RGBA),
	Vertex2D(-0.3 * width,-0.4 * height,RGBA),
	Vertex2D(-0.1 * width,-0.4 * height,RGBA),

	Vertex2D(-0.3 * width, 0.4 * height,RGBA),
	Vertex2D(-0.1 * width,-0.4 * height,RGBA),
	Vertex2D(-0.1 * width, 0.4 * height,RGBA),

	Vertex2D(-0.1 * width, 0.1 * height,RGBA),
	Vertex2D(-0.1 * width,-0.1 * height,RGBA),
	Vertex2D( 0.1 * width, 0.0 * height,RGBA),

	Vertex2D(-0.1 * width, 0.1 * height,RGBA),
	Vertex2D( 0.1 * width, 0.0 * height,RGBA),
	Vertex2D( 0.1 * width, 0.4 * height,RGBA),

	Vertex2D( 0.1 * width, 0.4 * height,RGBA),
	Vertex2D( 0.1 * width, 0.0 * height,RGBA),
	Vertex2D( 0.3 * width, 0.4 * height,RGBA),

	Vertex2D( 0.1 * width, 0.0 * height,RGBA),
	Vertex2D(-0.1 * width,-0.1 * height,RGBA),
	Vertex2D( 0.3 * width,-0.4 * height,RGBA),

	Vertex2D(-0.1 * width,-0.1 * height,RGBA),
	Vertex2D( 0.1 * width,-0.4 * height,RGBA),
	Vertex2D( 0.3 * width,-0.4 * height,RGBA),
	};

	newShape.vertices = screenData;
	return newShape;
}

shape2D ShapeGenerator::generateLetterL(float width, float height, glm::vec4 RGBA) 
{
	shape2D newShape;

	std::vector <Vertex2D> screenData
	{
	Vertex2D(-0.3 * width, 0.4 * height,RGBA),
	Vertex2D(-0.1 * width,-0.4 * height,RGBA),
	Vertex2D(-0.1 * width, 0.4 * height,RGBA),

	Vertex2D(-0.3 * width, 0.4 * height,RGBA),
	Vertex2D(-0.3 * width,-0.4 * height,RGBA),
	Vertex2D(-0.1 * width,-0.4 * height,RGBA),

	Vertex2D(-0.1 * width,-0.2 * height,RGBA),
	Vertex2D(-0.1 * width,-0.4 * height,RGBA),
	Vertex2D( 0.3 * width,-0.4 * height,RGBA),

	Vertex2D(-0.1 * width,-0.2 * height,RGBA),
	Vertex2D( 0.3 * width,-0.4 * height,RGBA),
	Vertex2D( 0.3 * width,-0.2 * height,RGBA),
	};

	newShape.vertices = screenData;
	return newShape;
}

shape2D ShapeGenerator::generateLetterM(float width, float height, glm::vec4 RGBA) 
{
	shape2D newShape;

	std::vector <Vertex2D> screenData
	{
	Vertex2D(-0.3 * width, 0.4 * height,RGBA),
	Vertex2D(-0.3 * width,-0.4 * height,RGBA),
	Vertex2D(-0.2 * width,-0.4 * height,RGBA),

	Vertex2D(-0.3 * width, 0.4 * height,RGBA),
	Vertex2D(-0.2 * width,-0.4 * height,RGBA),
	Vertex2D(-0.2 * width, 0.2 * height,RGBA),

	Vertex2D(-0.3 * width, 0.4 * height,RGBA),
	Vertex2D(-0.2 * width, 0.2 * height,RGBA),
	Vertex2D(-0.1 * width, 0.4 * height,RGBA),

	Vertex2D(-0.1 * width, 0.4 * height,RGBA),
	Vertex2D(-0.2 * width, 0.2 * height,RGBA),
	Vertex2D( 0.0 * width,-0.1 * height,RGBA),

	Vertex2D(-0.2 * width, 0.2 * height,RGBA),
	Vertex2D( 0.0 * width,-0.4 * height,RGBA),
	Vertex2D( 0.0 * width,-0.1 * height,RGBA),

	Vertex2D( 0.0 * width,-0.1 * height,RGBA),
	Vertex2D( 0.0 * width,-0.4 * height,RGBA),
	Vertex2D( 0.2 * width, 0.2 * height,RGBA),

	Vertex2D( 0.0 * width,-0.1 * height,RGBA),
	Vertex2D( 0.2 * width, 0.2 * height,RGBA),
	Vertex2D( 0.1 * width, 0.4 * height,RGBA),

	Vertex2D( 0.1 * width, 0.4 * height,RGBA),
	Vertex2D( 0.2 * width, 0.2 * height,RGBA),
	Vertex2D( 0.3 * width, 0.4 * height,RGBA),

	Vertex2D( 0.3 * width, 0.4 * height,RGBA),
	Vertex2D( 0.2 * width, 0.2 * height,RGBA),
	Vertex2D( 0.2 * width,-0.4 * height,RGBA),

	Vertex2D( 0.3 * width, 0.4 * height,RGBA),
	Vertex2D( 0.2 * width,-0.4 * height,RGBA),
	Vertex2D( 0.3 * width,-0.4 * height,RGBA),
	};

	newShape.vertices = screenData;
	return newShape;
}

shape2D ShapeGenerator::generateLetterN(float width, float height, glm::vec4 RGBA) 
{
	shape2D newShape;

	std::vector <Vertex2D> screenData
	{
	Vertex2D(-0.3 * width, 0.4 * height,RGBA),
	Vertex2D(-0.3 * width,-0.4 * height,RGBA),
	Vertex2D(-0.1 * width,-0.4 * height,RGBA),

	Vertex2D(-0.3 * width, 0.4 * height,RGBA),
	Vertex2D(-0.1 * width,-0.4 * height,RGBA),
	Vertex2D(-0.1 * width, 0.4 * height,RGBA),

	Vertex2D(-0.1 * width, 0.4 * height,RGBA),
	Vertex2D(-0.1 * width, 0.0 * height,RGBA),
	Vertex2D( 0.1 * width, 0.0 * height,RGBA),

	Vertex2D(-0.1 * width, 0.0 * height,RGBA),
	Vertex2D( 0.1 * width,-0.4 * height,RGBA),
	Vertex2D( 0.1 * width, 0.0 * height,RGBA),

	Vertex2D( 0.1 * width, 0.4 * height,RGBA),
	Vertex2D( 0.1 * width,-0.4 * height,RGBA),
	Vertex2D( 0.3 * width,-0.4 * height,RGBA),

	Vertex2D( 0.1 * width, 0.4 * height,RGBA),
	Vertex2D( 0.3 * width,-0.4 * height,RGBA),
	Vertex2D( 0.3 * width, 0.4 * height,RGBA),
	};

	newShape.vertices = screenData;
	return newShape;
}

shape2D ShapeGenerator::generateLetterO(float width, float height, glm::vec4 RGBA) 
{
	shape2D newShape;

	std::vector <Vertex2D> screenData
	{
	Vertex2D(-0.3 * width, 0.4 * height,RGBA),
	Vertex2D(-0.3 * width,-0.4 * height,RGBA),
	Vertex2D(-0.1 * width,-0.4 * height,RGBA),

	Vertex2D(-0.3 * width, 0.4 * height,RGBA),
	Vertex2D(-0.1 * width,-0.4 * height,RGBA),
	Vertex2D(-0.1 * width, 0.4 * height,RGBA),

	Vertex2D(-0.1 * width,-0.2 * height,RGBA),
	Vertex2D(-0.1 * width,-0.4 * height,RGBA),
	Vertex2D( 0.1 * width,-0.4 * height,RGBA),

	Vertex2D(-0.1 * width,-0.2 * height,RGBA),
	Vertex2D( 0.1 * width,-0.4 * height,RGBA),
	Vertex2D( 0.1 * width,-0.2 * height,RGBA),

	Vertex2D(-0.1 * width, 0.4 * height,RGBA),
	Vertex2D(-0.1 * width, 0.2 * height,RGBA),
	Vertex2D( 0.1 * width, 0.2 * height,RGBA),

	Vertex2D(-0.1 * width, 0.4 * height,RGBA),
	Vertex2D( 0.1 * width, 0.2 * height,RGBA),
	Vertex2D( 0.1 * width, 0.4 * height,RGBA),

	Vertex2D( 0.1 * width, 0.4 * height,RGBA),
	Vertex2D( 0.1 * width,-0.4 * height,RGBA),
	Vertex2D( 0.3 * width,-0.4 * height,RGBA),

	Vertex2D( 0.1 * width, 0.4 * height,RGBA),
	Vertex2D( 0.3 * width,-0.4 * height,RGBA),
	Vertex2D( 0.3 * width, 0.4 * height,RGBA),
	};

	newShape.vertices = screenData;
	return newShape;
}

shape2D ShapeGenerator::generateLetterP(float width, float height, glm::vec4 RGBA) 
{
	shape2D newShape;

	std::vector <Vertex2D> screenData
	{
	Vertex2D(-0.3 * width, 0.4 * height,RGBA),
	Vertex2D(-0.3 * width,-0.4 * height,RGBA),
	Vertex2D(-0.1 * width,-0.4 * height,RGBA),

	Vertex2D(-0.3 * width, 0.4 * height,RGBA),
	Vertex2D(-0.1 * width,-0.4 * height,RGBA),
	Vertex2D(-0.1 * width, 0.4 * height,RGBA),

	Vertex2D(-0.1 * width, 0.4 * height,RGBA),
	Vertex2D(-0.1 * width, 0.2 * height,RGBA),
	Vertex2D( 0.1 * width, 0.4 * height,RGBA),

	Vertex2D( 0.0 * width, 0.3 * height,RGBA),
	Vertex2D( 0.1 * width, 0.2 * height,RGBA),
	Vertex2D( 0.1 * width, 0.4 * height,RGBA),

	Vertex2D( 0.1 * width, 0.4 * height,RGBA),
	Vertex2D( 0.1 * width, 0.2 * height,RGBA),
	Vertex2D( 0.2 * width, 0.4 * height,RGBA),

	Vertex2D( 0.1 * width, 0.2 * height,RGBA),
	Vertex2D( 0.3 * width, 0.3 * height,RGBA),
	Vertex2D( 0.2 * width, 0.4 * height,RGBA),

	Vertex2D( 0.1 * width, 0.2 * height,RGBA),
	Vertex2D( 0.3 * width, 0.0 * height,RGBA),
	Vertex2D( 0.3 * width, 0.3 * height,RGBA),

	Vertex2D( 0.1 * width, 0.2 * height,RGBA),
	Vertex2D( 0.1 * width, 0.1 * height,RGBA),
	Vertex2D( 0.3 * width, 0.0 * height,RGBA),

	Vertex2D( 0.1 * width, 0.1 * height,RGBA),
	Vertex2D( 0.2 * width,-0.1 * height,RGBA),
	Vertex2D( 0.3 * width, 0.0 * height,RGBA),

	Vertex2D( 0.1 * width, 0.1 * height,RGBA),
	Vertex2D( 0.1 * width,-0.1 * height,RGBA),
	Vertex2D( 0.2 * width,-0.1 * height,RGBA),

	Vertex2D( 0.0 * width, 0.0 * height,RGBA),
	Vertex2D( 0.1 * width,-0.1 * height,RGBA),
	Vertex2D( 0.1 * width, 0.1 * height,RGBA),

	Vertex2D(-0.1 * width, 0.1 * height,RGBA),
	Vertex2D(-0.1 * width,-0.1 * height,RGBA),
	Vertex2D( 0.1 * width,-0.1 * height,RGBA),
	};

	newShape.vertices = screenData;
	return newShape;
}

shape2D ShapeGenerator::generateLetterQ(float width, float height, glm::vec4 RGBA) 
{
	shape2D newShape;

	std::vector <Vertex2D> screenData
	{
	Vertex2D(-0.1 * width, 0.0 * height,RGBA),
	Vertex2D(-0.1 * width,-0.1 * height,RGBA),
	Vertex2D( 0.0 * width, 0.0 * height,RGBA),

	Vertex2D( 0.0 * width, 0.0 * height,RGBA),
	Vertex2D(-0.1 * width,-0.1 * height,RGBA),
	Vertex2D( 0.3 * width,-0.3 * height,RGBA),

	Vertex2D(-0.1 * width,-0.1 * height,RGBA),
	Vertex2D( 0.2 * width,-0.4 * height,RGBA),
	Vertex2D( 0.3 * width,-0.3 * height,RGBA),

	Vertex2D( 0.2 * width,-0.4 * height,RGBA),
	Vertex2D( 0.3 * width,-0.4 * height,RGBA),
	Vertex2D( 0.3 * width,-0.3 * height,RGBA),

	Vertex2D( 0.1 * width, 0.2 * height,RGBA),
	Vertex2D( 0.1 * width,-0.1 * height,RGBA),
	Vertex2D( 0.2 * width,-0.2 * height,RGBA),

	Vertex2D( 0.1 * width, 0.2 * height,RGBA),
	Vertex2D( 0.2 * width,-0.2 * height,RGBA),
	Vertex2D( 0.2 * width, 0.3 * height,RGBA),

	Vertex2D( 0.1 * width, 0.4 * height,RGBA),
	Vertex2D( 0.1 * width, 0.2 * height,RGBA),
	Vertex2D( 0.2 * width, 0.3 * height,RGBA),

	Vertex2D( 0.0 * width, 0.3 * height,RGBA),
	Vertex2D( 0.1 * width, 0.2 * height,RGBA),
	Vertex2D( 0.1 * width, 0.4 * height,RGBA),

	Vertex2D(-0.2 * width, 0.4 * height,RGBA),
	Vertex2D( 0.0 * width, 0.3 * height,RGBA),
	Vertex2D( 0.1 * width, 0.4 * height,RGBA),

	Vertex2D(-0.2 * width, 0.4 * height,RGBA),
	Vertex2D(-0.2 * width, 0.2 * height,RGBA),
	Vertex2D(-0.1 * width, 0.3 * height,RGBA),

	Vertex2D(-0.3 * width, 0.3 * height,RGBA),
	Vertex2D(-0.2 * width, 0.2 * height,RGBA),
	Vertex2D(-0.2 * width, 0.4 * height,RGBA),

	Vertex2D(-0.3 * width, 0.3 * height,RGBA),
	Vertex2D(-0.3 * width,-0.2 * height,RGBA),
	Vertex2D(-0.2 * width, 0.2 * height,RGBA),

	Vertex2D(-0.3 * width,-0.2 * height,RGBA),
	Vertex2D(-0.2 * width,-0.1 * height,RGBA),
	Vertex2D(-0.2 * width, 0.2 * height,RGBA),

	Vertex2D(-0.3 * width,-0.2 * height,RGBA),
	Vertex2D(-0.2 * width,-0.3 * height,RGBA),
	Vertex2D(-0.2 * width,-0.1 * height,RGBA),
	
	Vertex2D(-0.2 * width,-0.1 * height,RGBA),
	Vertex2D(-0.2 * width,-0.3 * height,RGBA),
	Vertex2D(-0.1 * width,-0.2 * height,RGBA),

	Vertex2D(-0.2 * width,-0.3 * height,RGBA),
	Vertex2D( 0.1 * width,-0.3 * height,RGBA),
	Vertex2D(-0.1 * width,-0.2 * height,RGBA),

	Vertex2D(-0.1 * width,-0.2 * height,RGBA),
	Vertex2D( 0.1 * width,-0.3 * height,RGBA),
	Vertex2D( 0.0 * width,-0.2 * height,RGBA),

	Vertex2D(-0.2 * width, 0.4 * height,RGBA),
	Vertex2D(-0.1 * width, 0.3 * height,RGBA),
	Vertex2D( 0.0 * width, 0.3 * height,RGBA),
	};

	newShape.vertices = screenData;
	return newShape;
}

shape2D ShapeGenerator::generateLetterR(float width, float height, glm::vec4 RGBA) 
{
	shape2D newShape;

	std::vector <Vertex2D> screenData
	{
	Vertex2D(-0.3 * width, 0.4 * height,RGBA),
	Vertex2D(-0.3 * width,-0.4 * height,RGBA),
	Vertex2D(-0.1 * width,-0.4 * height,RGBA),

	Vertex2D(-0.3 * width, 0.4 * height,RGBA),
	Vertex2D(-0.1 * width,-0.4 * height,RGBA),
	Vertex2D(-0.1 * width, 0.4 * height,RGBA),

	Vertex2D(-0.1 *width, 0.4 *height,RGBA),
	Vertex2D(-0.1 *width, 0.3 *height,RGBA),
	Vertex2D( 0.2 *width, 0.4 *height,RGBA),

	Vertex2D(-0.1 *width, 0.3 *height,RGBA),
	Vertex2D( 0.2 *width, 0.4 *height,RGBA),
	Vertex2D( 0.3 *width, 0.3 *height,RGBA),

	Vertex2D(0.1 *width, 0.3 *height,RGBA),
	Vertex2D(0.3 *width, 0.1 *height,RGBA),
	Vertex2D(0.3 *width, 0.3 *height,RGBA),

	Vertex2D(0.2 *width, 0.2 *height,RGBA),
	Vertex2D(0.2 *width, 0.0 *height,RGBA),
	Vertex2D(0.3 *width, 0.1 *height,RGBA),

	Vertex2D(0.1 *width, 0.1 *height,RGBA),
	Vertex2D(0.2 *width, 0.0 *height,RGBA),
	Vertex2D(0.2 *width, 0.2 *height,RGBA),

	Vertex2D(-0.1 *width, 0.1 *height,RGBA),
	Vertex2D(-0.1 *width, 0.0 *height,RGBA),
	Vertex2D(0.1 *width, 0.1 *height,RGBA),

	Vertex2D(-0.1 *width, 0.0 *height,RGBA),
	Vertex2D( 0.2 *width, 0.0 *height,RGBA),
	Vertex2D( 0.1 *width, 0.1 *height,RGBA),

	Vertex2D(-0.1 *width, 0.0 *height,RGBA),
	Vertex2D(-0.1 *width, -0.1 *height,RGBA),
	Vertex2D(0.0 *width, 0.0 *height,RGBA),

	Vertex2D( 0.0 *width,  0.0 *height,RGBA),
	Vertex2D(-0.1 *width, -0.1 *height,RGBA),
	Vertex2D( 0.1 *width, -0.4 *height,RGBA),

	Vertex2D(0.0 *width, 0.0 *height,RGBA),
	Vertex2D(0.1 *width, -0.4 *height,RGBA),
	Vertex2D(0.3 *width, -0.4 *height,RGBA),

	Vertex2D(0.0 * width,  0.0 * height,RGBA),
	Vertex2D(0.3 * width, -0.4 * height,RGBA),
	Vertex2D(0.1 * width,  0.0 * height,RGBA),
	};

	newShape.vertices = screenData;
	return newShape;
}

shape2D ShapeGenerator::generateLetterS(float width, float height, glm::vec4 RGBA) 
{
	shape2D newShape;

	std::vector <Vertex2D> screenData
	{
	Vertex2D( 0.2 * width, 0.3 * height,RGBA),
	Vertex2D( 0.3 * width, 0.2 * height,RGBA),
	Vertex2D( 0.3 * width, 0.4 * height,RGBA),

	Vertex2D(-0.2 * width, 0.4 * height,RGBA),
	Vertex2D( 0.2 * width, 0.3 * height,RGBA),
	Vertex2D( 0.3 * width, 0.4 * height,RGBA),

	Vertex2D(-0.2 * width, 0.4 * height,RGBA),
	Vertex2D(-0.1 * width, 0.3 * height,RGBA),
	Vertex2D( 0.2 * width, 0.3 * height,RGBA),

	Vertex2D(-0.2 * width, 0.4 * height,RGBA),
	Vertex2D(-0.2 * width, 0.2 * height,RGBA),
	Vertex2D(-0.1 * width, 0.3 * height,RGBA),

	Vertex2D(-0.3 * width, 0.3 * height,RGBA),
	Vertex2D(-0.2 * width, 0.2 * height,RGBA),
	Vertex2D(-0.2 * width, 0.4 * height,RGBA),

	Vertex2D(-0.3 * width, 0.3 * height,RGBA),
	Vertex2D(-0.3 * width, 0.1 * height,RGBA),
	Vertex2D( 0.2 * width,-0.2 * height,RGBA),

	Vertex2D(-0.2 * width, 0.2 * height,RGBA),
	Vertex2D( 0.2 * width,-0.2 * height,RGBA),
	Vertex2D( 0.3 * width,-0.1 * height,RGBA),

	Vertex2D( 0.1 * width,-0.3 * height,RGBA),
	Vertex2D( 0.3 * width,-0.3 * height,RGBA),
	Vertex2D( 0.3 * width,-0.1 * height,RGBA),

	Vertex2D(-0.2 * width,-0.3 * height,RGBA),
	Vertex2D( 0.2 * width,-0.4 * height,RGBA),
	Vertex2D( 0.3 * width,-0.3 * height,RGBA),

	Vertex2D(-0.3 * width,-0.4 * height,RGBA),
	Vertex2D( 0.2 * width,-0.4 * height,RGBA),
	Vertex2D(-0.2 * width,-0.3 * height,RGBA),

	Vertex2D(-0.3 * width,-0.2 * height,RGBA),
	Vertex2D(-0.3 * width,-0.4 * height,RGBA),
	Vertex2D(-0.2 * width,-0.3 * height,RGBA),
	};

	newShape.vertices = screenData;
	return newShape;
}

shape2D ShapeGenerator::generateLetterT(float width, float height, glm::vec4 RGBA) 
{
	shape2D newShape;

	std::vector <Vertex2D> screenData
	{
	Vertex2D(-0.3 * width, 0.4 * height,RGBA),
	Vertex2D(-0.3 * width, 0.2 * height,RGBA),
	Vertex2D( 0.3 * width, 0.2 * height,RGBA),

	Vertex2D(-0.1 * width, 0.2 * height,RGBA),
	Vertex2D(-0.1 * width,-0.4 * height,RGBA),
	Vertex2D( 0.1 * width, 0.2 * height,RGBA),

	Vertex2D(-0.1 * width,-0.4 * height,RGBA),
	Vertex2D( 0.1 * width,-0.4 * height,RGBA),
	Vertex2D( 0.1 * width, 0.2 * height,RGBA),

	Vertex2D(-0.3 * width, 0.4 * height,RGBA),
	Vertex2D( 0.3 * width, 0.2 * height,RGBA),
	Vertex2D( 0.3 * width, 0.4 * height,RGBA),
	};

	newShape.vertices = screenData;
	return newShape;
}

shape2D ShapeGenerator::generateLetterU(float width, float height, glm::vec4 RGBA) 
{
	shape2D newShape;

	std::vector <Vertex2D> screenData
	{
	Vertex2D(-0.3 * width, 0.4 * height,RGBA),
	Vertex2D(-0.3 * width,-0.2 * height,RGBA),
	Vertex2D(-0.1 * width, 0.4 * height,RGBA),

	Vertex2D(-0.3 * width,-0.2 * height,RGBA),
	Vertex2D(-0.1 * width,-0.4 * height,RGBA),
	Vertex2D(-0.1 * width, 0.4 * height,RGBA),

	Vertex2D(-0.1 * width,-0.1 * height,RGBA),
	Vertex2D(-0.1 * width,-0.4 * height,RGBA),
	Vertex2D( 0.0 * width,-0.2 * height,RGBA),

	Vertex2D( 0.0 * width,-0.2 * height,RGBA),
	Vertex2D(-0.1 * width,-0.4 * height,RGBA),
	Vertex2D( 0.1 * width,-0.4 * height,RGBA),

	Vertex2D( 0.0 * width,-0.2 * height,RGBA),
	Vertex2D( 0.1 * width,-0.4 * height,RGBA),
	Vertex2D( 0.1 * width,-0.1 * height,RGBA),

	Vertex2D( 0.1 * width, 0.4 * height,RGBA),
	Vertex2D( 0.1 * width,-0.4 * height,RGBA),
	Vertex2D( 0.3 * width,-0.2 * height,RGBA),

	Vertex2D( 0.1 * width, 0.4 * height,RGBA),
	Vertex2D( 0.3 * width,-0.2 * height,RGBA),
	Vertex2D( 0.3 * width, 0.4 * height,RGBA),
	};

	newShape.vertices = screenData;
	return newShape;
}

shape2D ShapeGenerator::generateLetterV(float width, float height, glm::vec4 RGBA) 
{
	shape2D newShape;

	std::vector <Vertex2D> screenData
	{
	Vertex2D(-0.3 * width, 0.4 * height,RGBA),
	Vertex2D(-0.1 * width,-0.4 * height,RGBA),
	Vertex2D(-0.1 * width, 0.4 * height,RGBA),

	Vertex2D(-0.1 * width, 0.4 * height,RGBA),
	Vertex2D(-0.1 * width,-0.4 * height,RGBA),
	Vertex2D( 0.0 * width,-0.1 * height,RGBA),

	Vertex2D(-0.1 * width,-0.4 * height,RGBA),
	Vertex2D( 0.0 * width,-0.1 * height,RGBA),
	Vertex2D( 0.1 * width,-0.4 * height,RGBA),

	Vertex2D( 0.0 * width,-0.1 * height,RGBA),
	Vertex2D( 0.1 * width,-0.4 * height,RGBA),
	Vertex2D( 0.1 * width, 0.4 * height,RGBA),

	Vertex2D( 0.1 * width, 0.4 * height,RGBA),
	Vertex2D( 0.1 * width,-0.4 * height,RGBA),
	Vertex2D( 0.3 * width, 0.4 * height,RGBA),
	};

	newShape.vertices = screenData;
	return newShape;
}

shape2D ShapeGenerator::generateLetterW(float width, float height, glm::vec4 RGBA) 
{
	shape2D newShape;

	std::vector <Vertex2D> screenData
	{
	Vertex2D(-0.3 * width, 0.4 * height,RGBA),
	Vertex2D(-0.3 * width,-0.3 * height,RGBA),
	Vertex2D(-0.2 * width,-0.3 * height,RGBA),

	Vertex2D(-0.3 * width, 0.4 * height,RGBA),
	Vertex2D(-0.2 * width,-0.3 * height,RGBA),
	Vertex2D(-0.2 * width, 0.4 * height,RGBA),

	Vertex2D(-0.3 * width,-0.3 * height,RGBA),
	Vertex2D(-0.2 * width,-0.3 * height,RGBA),
	Vertex2D(-0.2 * width,-0.4 * height,RGBA),

	Vertex2D(-0.2 * width,-0.3 * height,RGBA),
	Vertex2D(-0.2 * width,-0.4 * height,RGBA),
	Vertex2D(-0.1 * width,-0.4 * height,RGBA),

	Vertex2D(-0.2 * width,-0.3 * height,RGBA),
	Vertex2D(-0.1 * width, 0.3 * height,RGBA),
	Vertex2D( 0.0 * width, 0.2 * height,RGBA),

	Vertex2D(-0.2 * width,-0.3 * height,RGBA),
	Vertex2D(-0.1 * width,-0.4 * height,RGBA),
	Vertex2D( 0.0 * width, 0.2 * height,RGBA),

	Vertex2D(-0.1 * width, 0.3 * height,RGBA),
	Vertex2D( 0.0 * width, 0.2 * height,RGBA),
	Vertex2D( 0.1 * width, 0.3 * height,RGBA),

	Vertex2D( 0.0 * width, 0.2 * height,RGBA),
	Vertex2D( 0.2 * width,-0.3 * height,RGBA),
	Vertex2D( 0.1 * width, 0.3 * height,RGBA),

	Vertex2D( 0.0 * width, 0.2 * height,RGBA),
	Vertex2D( 0.1 * width,-0.4 * height,RGBA),
	Vertex2D( 0.2 * width,-0.3 * height,RGBA),

	Vertex2D( 0.1 * width,-0.4 * height,RGBA),
	Vertex2D( 0.2 * width,-0.4 * height,RGBA),
	Vertex2D( 0.2 * width,-0.3 * height,RGBA),

	Vertex2D( 0.2 * width,-0.3 * height,RGBA),
	Vertex2D( 0.2 * width,-0.4 * height,RGBA),
	Vertex2D( 0.3 * width,-0.3 * height,RGBA),

	Vertex2D( 0.2 * width, 0.4 * height,RGBA),
	Vertex2D( 0.2 * width,-0.3 * height,RGBA),
	Vertex2D( 0.3 * width, 0.4 * height,RGBA),

	Vertex2D( 0.2 * width,-0.3 * height,RGBA),
	Vertex2D( 0.3 * width,-0.3 * height,RGBA),
	Vertex2D( 0.3 * width, 0.4 * height,RGBA),
	};

	newShape.vertices = screenData;
	return newShape;
}

shape2D ShapeGenerator::generateLetterX(float width, float height, glm::vec4 RGBA) 
{
	shape2D newShape;

	std::vector <Vertex2D> screenData
	{
	Vertex2D(-0.3 * width, 0.4 * height,RGBA),
	Vertex2D(-0.1 * width, 0.0 * height,RGBA),
	Vertex2D(-0.1 * width, 0.4 * height,RGBA),

	Vertex2D(-0.1 * width, 0.4 * height,RGBA),
	Vertex2D(-0.1 * width, 0.0 * height,RGBA),
	Vertex2D( 0.0 * width, 0.1 * height,RGBA),

	Vertex2D(-0.1 * width, 0.0 * height,RGBA),
	Vertex2D( 0.0 * width,-0.1 * height,RGBA),
	Vertex2D( 0.0 * width, 0.1 * height,RGBA),

	Vertex2D(-0.1 * width, 0.0 * height,RGBA),
	Vertex2D(-0.1 * width,-0.4 * height,RGBA),
	Vertex2D( 0.0 * width,-0.1 * height,RGBA),

	Vertex2D(-0.3 * width,-0.4 * height,RGBA),
	Vertex2D(-0.1 * width,-0.4 * height,RGBA),
	Vertex2D(-0.1 * width, 0.0 * height,RGBA),

	Vertex2D( 0.0 * width, 0.1 * height,RGBA),
	Vertex2D( 0.0 * width,-0.1 * height,RGBA),
	Vertex2D( 0.1 * width, 0.0 * height,RGBA),

	Vertex2D( 0.0 * width, 0.1 * height,RGBA),
	Vertex2D( 0.1 * width, 0.0 * height,RGBA),
	Vertex2D( 0.1 * width, 0.4 * height,RGBA),

	Vertex2D( 0.1 * width, 0.4 * height,RGBA),
	Vertex2D( 0.1 * width, 0.0 * height,RGBA),
	Vertex2D( 0.3 * width, 0.4 * height,RGBA),

	Vertex2D( 0.0 * width,-0.1 * height,RGBA),
	Vertex2D( 0.1 * width,-0.4 * height,RGBA),
	Vertex2D( 0.1 * width, 0.1 * height,RGBA),

	Vertex2D( 0.1 * width, 0.0 * height,RGBA),
	Vertex2D( 0.1 * width,-0.4 * height,RGBA),
	Vertex2D( 0.3 * width,-0.4 * height,RGBA),
	};

	newShape.vertices = screenData;
	return newShape;
}

shape2D ShapeGenerator::generateLetterY(float width, float height, glm::vec4 RGBA) 
{
	shape2D newShape;

	std::vector <Vertex2D> screenData
	{
	Vertex2D(-0.3 * width, 0.4 * height,RGBA),
	Vertex2D(-0.1 * width, 0.0 * height,RGBA),
	Vertex2D(-0.1 * width, 0.4 * height,RGBA),

	Vertex2D(-0.1 * width, 0.4 * height,RGBA),
	Vertex2D(-0.1 * width, 0.0 * height,RGBA),
	Vertex2D( 0.0 * width, 0.1 * height,RGBA),

	Vertex2D(-0.1 * width, 0.0 * height,RGBA),
	Vertex2D( 0.0 * width, 0.1 * height,RGBA),
	Vertex2D( 0.1 * width, 0.0 * height,RGBA),

	Vertex2D( 0.0 * width, 0.1 * height,RGBA),
	Vertex2D( 0.1 * width, 0.0 * height,RGBA),
	Vertex2D( 0.1 * width, 0.4 * height,RGBA),

	Vertex2D( 0.1 * width, 0.4 * height,RGBA),
	Vertex2D( 0.1 * width, 0.0 * height,RGBA),
	Vertex2D( 0.3 * width, 0.4 * height,RGBA),

	Vertex2D(-0.1 * width, 0.0 * height,RGBA),
	Vertex2D( 0.1 * width,-0.4 * height,RGBA),
	Vertex2D( 0.1 * width, 0.0 * height,RGBA),

	Vertex2D(-0.1 * width, 0.0 * height,RGBA),
	Vertex2D(-0.1 * width,-0.4 * height,RGBA),
	Vertex2D( 0.1 * width,-0.4 * height,RGBA),
	};

	newShape.vertices = screenData;
	return newShape;
}

shape2D ShapeGenerator::generateLetterZ(float width, float height, glm::vec4 RGBA) 
{
	shape2D newShape;

	std::vector <Vertex2D> screenData
	{
	Vertex2D(-0.3 * width, 0.4 * height,RGBA),
	Vertex2D(-0.3 * width, 0.2 * height,RGBA),
	Vertex2D(-0.2 * width, 0.3 * height,RGBA),

	Vertex2D(-0.3 * width, 0.4 * height,RGBA),
	Vertex2D(-0.2 * width, 0.3 * height,RGBA),
	Vertex2D( 0.3 * width, 0.4 * height,RGBA),

	Vertex2D(-0.2 * width, 0.3 * height,RGBA),
	Vertex2D( 0.2 * width, 0.3 * height,RGBA),
	Vertex2D( 0.3 * width, 0.4 * height,RGBA),

	Vertex2D( 0.2 * width, 0.3 * height,RGBA),
	Vertex2D( 0.3 * width, 0.2 * height,RGBA),
	Vertex2D( 0.3 * width, 0.4 * height,RGBA),

	Vertex2D(-0.3 * width,-0.2 * height,RGBA),
	Vertex2D(-0.2 * width,-0.3 * height,RGBA),
	Vertex2D( 0.2 * width, 0.3 * height,RGBA),

	Vertex2D(-0.2 * width,-0.3 * height,RGBA),
	Vertex2D( 0.3 * width, 0.2 * height,RGBA),
	Vertex2D( 0.2 * width, 0.3 * height,RGBA),

	Vertex2D(-0.3 * width,-0.2 * height,RGBA),
	Vertex2D(-0.3 * width,-0.4 * height,RGBA),
	Vertex2D(-0.2 * width,-0.3 * height,RGBA),

	Vertex2D(-0.3 * width,-0.4 * height,RGBA),
	Vertex2D( 0.3 * width,-0.4 * height,RGBA),
	Vertex2D(-0.2 * width,-0.3 * height,RGBA),

	Vertex2D(-0.2 * width,-0.3 * height,RGBA),
	Vertex2D( 0.3 * width,-0.4 * height,RGBA),
	Vertex2D( 0.2 * width,-0.3 * height,RGBA),

	Vertex2D( 0.2 * width,-0.3 * height,RGBA),
	Vertex2D( 0.3 * width,-0.4 * height,RGBA),
	Vertex2D( 0.3 * width,-0.2 * height,RGBA),
	};

	newShape.vertices = screenData;
	return newShape;
}