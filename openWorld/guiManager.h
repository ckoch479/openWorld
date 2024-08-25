#pragma once

#include <iostream>
#include <unordered_map>

#include "windowManager.h"
#include "Scene.h"

#include "includes/glm/glm.hpp"
#include "Includes/glm/gtc/type_ptr.hpp"

#include "ShapeGenerator.h"

#ifndef GUIMANAGER_H
#define GUIMANAGER_H

//was a work in progress sorta isnt very good
struct menuButton
{
	bool isPressable = false; //using this so i can "gray" out menu buttons that have no functionality at the time
	bool pressed = false;
	//"collision" testing for mouse position and clicking
	glm::vec2 screenPos = glm::vec2(0.0f); //center of the box
	glm::vec2 halfSize; //half width and half height in screen coordinates
};

struct textBox
{
	std::string text; //what test should be displayed int he box;
	glm::vec2 renderPos = glm::vec2(0.0f);//position in screen coordinates for rendering, center of the box
	glm::vec2 size = glm::vec2(0.1f); //half width and halfHeight of the box in screen coordinates

	std::vector <shape2D> letters;

	textBox() {}

	textBox(std::string text,glm::vec2 NDCcoords, glm::vec2 NDCscale, float spacing, float height, glm::vec4 RGBA)
	{
		this->text = text;
		this->renderPos = NDCcoords;
		this->size = NDCscale;

		//generate individual letters for shape2D letters
		//first determine each individual letter and amount of space available
		int numLetters = 0;
		std::vector <char> singleLetters;

		for(unsigned int i = 0; i < text.size(); i++)
		{
			numLetters++;
			singleLetters.push_back(text[i]);
		}

		//this is a little fucky wucky
		float smallestX = this->renderPos.x - this->size.x;
		float largestX = this->renderPos.x + this->size.x;

		float smallestY = this->renderPos.y - this->size.y;
		float largestY = this->renderPos.y + this->size.y;

		float xOffset = (largestX - smallestX) / numLetters; //how much space each letter can fill in the x direction;
		float yOffset = largestY - smallestY;
		float currentOffset = smallestX;

		ShapeGenerator shaper;
		
		for(unsigned int i = 0; i < singleLetters.size(); i++)
		{
			shape2D newShape = shaper.generateCharacter(singleLetters[i], spacing, height, RGBA);
			newShape.position = glm::vec3(currentOffset, renderPos.y,0.0f);
			newShape.scale = glm::vec3(xOffset,yOffset,1);
			letters.push_back(newShape);
			currentOffset += xOffset;
		}

	}
};

struct displayBox
{
	glm::vec4 color = glm::vec4(1.0f); //default white and solid, does support alpha colors
	glm::vec2 renderPos; //position in NDC coordinates for rendering, center of the box
	glm::vec2 size; //half width and halfHeight of the box in NDC coordinates
	//eventually will also support textures
	shape2D boxShape;

	displayBox(glm::vec4 RGBA, glm::vec2 rendPos, glm::vec2 scale)
	{
		this->color = RGBA;
		this->renderPos = rendPos;
		this->size = scale;
	}

	displayBox()
	{
	
	}

};

struct GUIobject
{
	displayBox renderBox;
	textBox renderText;
	menuButton collisionBox;

	GUIobject() 
	{
		renderBox = *new displayBox();
		renderText = *new textBox();
		collisionBox = *new menuButton();
	};
};

//manager for all things like menu buttons, text boxes, HUDs, and more
class guiManager
{
public:
	guiManager(int* scrWidth, int* scrHeight, windowManager* newManager, scene* newScene);

	~guiManager();

	void updateMousePos(); //call on window manager for newest mouse position

	void updateGUI(); //iterate through each gui object and check for mouse collisions and movement updates

	unsigned int createGuiObject(glm::vec2 NDCpos, glm::vec2 NDCsize, glm::vec4 RGBA, std::string boxText);

private:

	int* scrWidth;
	int* scrHeight;

	windowManager* manager;
	scene* currentScene; //for rendering ease of use
	ShapeGenerator* shaper;

	double mouseX; //current position of the mouse on screen
	double mouseY;

	unsigned int createUniqueID();

	glm::vec2 NDCtoScreenCoords(float x, float y);

	glm::vec2 ScreenCoordstoNDC(int x, int y);

	unsigned int idCounter = 0;

	std::unordered_map <unsigned int, GUIobject> objects;

};

#endif