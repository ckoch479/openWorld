#include "windowManager.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

void errorCallback(int error, const char* msg);

void key_callback(GLFWwindow* window, int key, int scanCode, int action, int mods);

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

double mouseScrollY = 0.0f;

windowManager::windowManager()
{
	//init opengl and set opengl version
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//create window object
	this->currentWindow = glfwCreateWindow(this->screenWidth, this->screenHeight, "openWorld", NULL, NULL);

	//this->currentWindow = glfwCreateWindow(this->screenWidth, this->screenHeight, "openWorld", glfwGetPrimaryMonitor(), NULL); //for full screen window
	if (this->currentWindow == NULL)
	{
		std::cout << "Failed to create GLFW window!" << std::endl;
		glfwTerminate();
	}
	glfwMakeContextCurrent(this->currentWindow);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD!" << std::endl;
	}

	glViewport(0, 0, this->screenWidth, this->screenHeight);

	glfwSetFramebufferSizeCallback(this->currentWindow, framebuffer_size_callback);
	glfwSetKeyCallback(this->currentWindow, key_callback);
	glfwSetScrollCallback(this->currentWindow, scroll_callback);
	glfwSetErrorCallback(errorCallback);

	glfwSetInputMode(this->currentWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	this->scrollOffset = 0.0f;
}

void windowManager::setScreenSize(int width, int height)
{
	glViewport(0, 0, width, height);
}

void windowManager::getScreenSize(int* width, int* height)
{
	*width = this->screenWidth;
	*height = this->screenHeight;
}

windowManager::~windowManager() 
{
	glfwDestroyWindow(this->currentWindow);
	glfwTerminate();
}

GLFWwindow* windowManager::getCurrentWindow()
{
	return this->currentWindow;
}

void windowManager::pollWindowEvents()
{
	this->keyboardInputString.clear();
	glfwSwapBuffers(this->currentWindow);
	glfwPollEvents();
	setKeys();
	pollCursorPos();
	pollMouseButtons();
	pollScroll();

}

bool windowManager::getState(int key)
{
	bool pressed = false;
	int state = glfwGetKey(this->currentWindow,key);
	if (state == GLFW_PRESS)
	{
		pressed = true;
		this->keyboardInputString.push_back(key); //pushes back only keys that are pressed
	}
	return pressed;
}

void windowManager::setKeys()
{
	for(unsigned int i = 32; i < 348; i++)
	{
		keys[i] = getState(i);
	}
}

bool windowManager::checkKey(int key)
{
	return keys[key];
}

std::vector <int> windowManager::getKeyVector()
{
	return this->keyboardInputString;
}

std::unordered_map<int, bool> windowManager::getKeyStates()
{
	return this->keys;
}

void windowManager::enableCursor()
{
	glfwSetInputMode(this->currentWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	this->CursorEnabled = true;
}

void windowManager::disableCursor()
{
	glfwSetInputMode(this->currentWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	this->CursorEnabled = false;
}

bool windowManager::getCursorStatus()
{
	return this->CursorEnabled;
}

void windowManager::getMousePosition(double* x, double* y)
{
	pollCursorPos();
	*x = this->cursorX;
	*y = this->cursorY;
}

double windowManager::getMouseX()
{
	return this->cursorX;
}

double windowManager::getMouseY()
{
	return this->cursorY;
}

void windowManager::pollCursorPos()
{
	glfwGetCursorPos(this->currentWindow, &this->cursorX, &this->cursorY);
}

void windowManager::pollMouseButtons()
{
	int state = glfwGetMouseButton(this->currentWindow, GLFW_MOUSE_BUTTON_LEFT);
	if (state == GLFW_PRESS) { leftMouse = true; }
	if (state == GLFW_RELEASE) { leftMouse = false; }

	state = glfwGetMouseButton(this->currentWindow, GLFW_MOUSE_BUTTON_RIGHT);
	if (state == GLFW_PRESS) { rightMouse = true; }
	if (state == GLFW_RELEASE) { rightMouse = false; }

	state = glfwGetMouseButton(this->currentWindow, GLFW_MOUSE_BUTTON_MIDDLE);
	if (state == GLFW_PRESS) { middleMouse = true; }
	if (state == GLFW_RELEASE) { middleMouse = false; }
}

void windowManager::pollScroll()
{
	this->scrollOffset = mouseScrollY;
}

bool windowManager::leftClick()
{
	return this->leftMouse;
}
bool windowManager::rightClick()
{
	return this->rightMouse;
}
bool windowManager::middleClick()
{
	return this->middleMouse;
}

float windowManager::getMouseScroll()
{
	return this->scrollOffset;
}

//these as far as i know right now cannot be class methods 
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void errorCallback(int error, const char* msg)
{
	std::string s;
	s = " [" + std::to_string(error) + "] " + msg + '\n';
	std::cerr << s << std::endl;
}

//issues with this guy sooooo its gonna sit for now
void key_callback(GLFWwindow* window, int key, int scanCode, int action, int mods)
{
	
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	mouseScrollY += yoffset;

	//30 and -45

	if (mouseScrollY > 30) { mouseScrollY = 30; }
	if (mouseScrollY < -45) { mouseScrollY = -45; }
}
