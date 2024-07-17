#pragma once

#include <glad/glad.h>
#include "GLFW/glfw3.h"

#include <iostream>
#include <string>
#include <vector>

#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H

//this struct is for whenever a key changes state, if a key is pressed or released this struct is added to the keyboard input vector
struct keyState
{
	char key;  //the actual key in question
	bool down; //if it is currently being pressed down or up
};

class windowManager
{
public:

	windowManager();
	~windowManager();

	GLFWwindow* getCurrentWindow();

	//this function polls window events i.e. resize, key presses and swaps render buffers
	void pollWindowEvents();

	//this checks the state of a particular key
	bool checkKey(int key);
	//this returns the entire keyVector if the simulation manager wants it
	std::vector <int>* getKeyVector();

	void enableCursor();

	void disableCursor();

	bool getCursorStatus();

	void getMousePosition(double* x, double* y);

	void setScreenSize(int width, int height);

	void getScreenSize(int* width, int* height);

	bool leftClick();
	bool rightClick();
	bool middleClick();
private:

	GLFWwindow* currentWindow;
	//default values
	int screenWidth =  1920; //16:9 aspect ratio was 1600/800
	int screenHeight =  1080;

	//a bool array of keys each index is the key name/number as defined by GLFW
	bool keys[348];
	
	//for the current mouse cursor position, only useful if the cursor is not diabled
	double cursorX; 
	double cursorY;
	bool CursorEnabled = false; //initially is false

	bool leftMouse;
	bool middleMouse;
	bool rightMouse;

	double scrollOffset = 0;

	//this string will report all keys pressed this cycle and push them into this vector
	//it is the responsibility of the simulation manager to iterate through each keystroke and clear the keystrokes at the end of simulation manager processing the data
	std::vector <int> keyboardInputString;

	//this sets the keys in the keystate array
	void setKeys();

	bool getState(int key);

	void pollCursorPos();

	void pollMouseButtons();

	void pollScroll();


};

#endif