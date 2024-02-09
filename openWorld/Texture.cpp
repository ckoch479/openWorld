#include "Texture.h"

#include <iostream>


Texture::Texture() : width(0),height(0),internalFormat(GL_RGBA),imageFormat(GL_RGBA),wrapS(GL_REPEAT),wrapT(GL_REPEAT),filterMin(GL_LINEAR),filterMax(GL_LINEAR)
{
	this->width = width;
	this->height = height;
	this->internalFormat = internalFormat;
	this->imageFormat = imageFormat;
	this->wrapS = wrapS;
	this->wrapT = wrapT;
	this->filterMin = filterMin;
	this->filterMax = filterMax;
	glGenTextures(1, &this->id);
}

Texture::~Texture() 
{

}

void Texture::generate(unsigned int width, unsigned int height, unsigned char* data)
{
	this->width = width;
	this->height = height;

	std::cout << "image format type: " << this->imageFormat << std::endl;

	glBindTexture(GL_TEXTURE_2D, this->id);
	glTexImage2D(GL_TEXTURE_2D, 0, this->internalFormat, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->wrapS);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->wrapT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->filterMin);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->filterMax);
	// unbind texture
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::bind() const
{
	glBindTexture(GL_TEXTURE_2D, this->id);
}