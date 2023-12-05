#pragma once

#include <glad/glad.h>
#include "GLFW/glfw3.h"

#include <iostream>


#ifndef TEXTURE_H
#define TEXTURE_H

class Texture
{
public:

	Texture();
	~Texture();

	unsigned int id;
	unsigned int width, height;

	unsigned int internalFormat;
	unsigned int imageFormat;

	unsigned int wrapS;
	unsigned int wrapT;
	unsigned int filterMin;
	unsigned int filterMax;

	void generate(unsigned int width, unsigned int height, unsigned char* data);

	void bind() const;

private:

};
#endif

