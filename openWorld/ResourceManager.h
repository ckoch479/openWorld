
#include "glad/glad.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <map>


#include "includes/glm/glm.hpp"
#include "Includes/glm/gtc/type_ptr.hpp"
#include "lookup_table.h"

//basic mesh data ie vertices,texcoords,normals,indices,ect
struct Vertex
{
	glm::vec3 vertexPosition;
	glm::vec2 texCoords;
	glm::vec3 Normal;
};

struct Texture
{
	int TextID;
};

struct MeshData
{
	std::vector <Vertex> vertices;
	std::vector <Texture> textures;
};

struct Material
{
	std::string name;

	float Ambient[3];
	float Diffuse[3];
	float Specular[3];
	float Shininess;
};

#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H
//resource manager stores data of meshes, textures, ect
class ResourceManager
{

public:
	//load a mesh object into memory. This function will return an id that can be used to access this mesh data for later.
	ID loadMesh(const std::string filepath);

	//returns the mesh data of the object via this ID
	MeshData* getMesh(ID& id);
	

private:
	lookup_table<MeshData> meshes;
	lookup_table<Texture> textures;

	//loads mesh data from a file, gltf is currently only supported
	MeshData loadMeshDataFromFile(const std::string filepath);


};

#endif
