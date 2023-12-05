
#include "glad/glad.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>

#include "includes/glm/glm.hpp"
#include "Includes/glm/gtc/type_ptr.hpp"
#include "lookup_table.h"
#include "Texture.h"

//basic mesh data ie vertices,texcoords,normals,indices,ect


struct Vertex
{
	glm::vec3 vertexPosition;
	glm::vec2 texCoords;
	glm::vec3 Normal;
};

struct MeshData
{
	std::vector <Vertex> vertices;
	//std::vector <Texture> textures;
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

	static Texture* loadTexture(const std::string filepath, std::string name);
	
	static Texture* getTexture(std::string name);

private:
	lookup_table<MeshData> meshes;
	static std::unordered_map <std::string,Texture> textures;

	//loads mesh data from a file, gltf is currently only supported
	MeshData loadMeshDataFromFile(const std::string filepath);


};

#endif
