#include "AssimpMesh.h"

AssimpMesh::AssimpMesh(std::vector <AssimpVertex> vertices, std::vector <unsigned int> indices)
{
	this->vertices = vertices;
	this->indices = indices;
}

AssimpMesh::AssimpMesh(std::vector <AssimpVertex> vertices, std::vector <unsigned int> indices, std::vector <std::string> DiffusetexturePaths, std::vector <std::string> SpeculartexturePaths)
{
	this->vertices = vertices;
	this->indices = indices;
	this->diffuseTextures = DiffusetexturePaths;
	this->specularTextures = SpeculartexturePaths;
}

std::vector <glm::vec3> AssimpMesh::getVertexPositions()
{
	std::vector <glm::vec3> vertexPositions;

	for(unsigned int i = 0; i < this->vertices.size(); i++)
	{
		vertexPositions.push_back(this->vertices[i].Position);
	}

	return vertexPositions;
}

std::vector <glm::vec3> AssimpMesh::getVertexNormals()
{
	std::vector <glm::vec3> vertexNormals;

	for (unsigned int i = 0; i < this->vertices.size(); i++)
	{
		vertexNormals.push_back(this->vertices[i].Normal);
	}

	return vertexNormals;
}

std::vector <glm::vec2> AssimpMesh::getVertexTexCoords()
{
	std::vector <glm::vec2> vertexTextureCoords;

	for (unsigned int i = 0; i < this->vertices.size(); i++)
	{
		vertexTextureCoords.push_back(this->vertices[i].TexCoords);
	}

	return vertexTextureCoords;
}

std::vector <unsigned int> AssimpMesh::getIndices() 
{
	return this->indices;
}

std::vector <AssimpVertex> AssimpMesh::getVertexData()
{
	return this->vertices;
}

std::vector <std::string> AssimpMesh::getDiffuseTexturePaths()
{
	return this->diffuseTextures;
}

std::vector <std::string> AssimpMesh::getSpecularTexturePaths()
{
	return this->specularTextures;
}

std::vector <std::string> AssimpMesh::getNormalTexturePaths()
{
	return this->normalTextures;
}

std::vector <std::string> AssimpMesh::getHeightTexturePaths()
{
	return this->heightTextures;
}