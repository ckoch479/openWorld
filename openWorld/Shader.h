#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
	//Shader Program ID
	unsigned int shaderID;

	//load Shader from a .vs and .fs file
	Shader(const char* vertexPath, const char* fragmentPath);

	//load shader from a string
	Shader(std::string VertexString, std::string FragmentString);

	void use();

	const void setBool(const std::string& name,bool value);

	const void setInt(const std::string& name, int value);

	const void setFloat(const std::string& name, float value);

	const void setVec2(const std::string& name, float x, float y);

	const void setVec3(const std::string& name, float x, float y, float z);

	const void setVec4(const std::string& name, float x, float y, float z, float w);


};


#endif
