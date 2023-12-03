#pragma once

#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H
class InputManager
{
	InputManager() {};
	~InputManager() {};

	void Init();

	//bool checkKeystate(int key);

	static void setKeyState(int key, bool pressed);

	//keeps track of current mouse position, relative mouse movements, and key inputs

	static bool Keys[1024];
	static float currentMouse;
	static float lastMouse;
	static bool firstMouse;
};

#endif