#include "guiManager.h"

guiManager::guiManager(int* scrWidth, int* scrHeight, windowManager* newManager, scene* newScene)
{
	this->scrWidth = scrWidth;
	this->scrHeight = scrHeight;
	this->manager = newManager;
	this->currentScene = newScene;

	this->shaper = new ShapeGenerator();
}

guiManager::~guiManager()
{

}

void guiManager::updateMousePos()
{

}

void guiManager::updateGUI()
{

}

unsigned int guiManager::createGuiObject(glm::vec2 NDCpos, glm::vec2 NDCsize, glm::vec4 RGBA, std::string boxText)
{
	unsigned int newId = createUniqueID();

	this->objects[newId].renderBox = *new displayBox(RGBA,NDCpos,NDCsize);
	this->objects[newId].renderBox.boxShape = shaper->generateBox(NDCsize.x, NDCsize.y,RGBA);
	this->objects[newId].renderBox.boxShape.position = glm::vec3(NDCpos,0.0f);

	//this->objects[newId].renderText = textBox("continue", glm::vec2(0.0, 0.0), glm::vec2(0.3, 0.05), 1.5, 1.0, glm::vec4(0.3, 0.3, 0.3, 1.0));
	//
	////this->objects[newId].collisionBox;

	//this->currentScene->add2DScreenShape(this->objects[newId].renderBox.boxShape);

	//for(unsigned int i = 0; i < this->objects[newId].renderText.letters.size(); i++)
	//{
	//	currentScene->add2DScreenShape(this->objects[newId].renderText.letters[i]);
	//}
	

	return newId;
}

unsigned int guiManager::createUniqueID()
{
	this->idCounter++;
	return this->idCounter;
}

glm::vec2 guiManager::NDCtoScreenCoords(float x, float y)
{
	glm::vec2 screenCoords = glm::vec2(1.0f);




	return screenCoords;
}

glm::vec2 guiManager::ScreenCoordstoNDC(int x, int y)
{
	glm::vec2 NDCcoords = glm::vec2(1.0f);



	return NDCcoords;
}