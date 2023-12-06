
#include "glad/glad.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>

#include "Includes/stb_image.h"

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

#include "includes/glm/glm.hpp"
#include "Includes/glm/gtc/type_ptr.hpp"
#include "lookup_table.h"
#include "Texture.h"

//basic mesh data i.e. vertices,texcoords,normals,indices,ect
struct Vertex
{
	glm::vec3 vertexPosition;
	glm::vec2 texCoords;
	glm::vec3 Normal;
};

struct MeshData
{
	std::vector <Vertex> vertices;
	std::vector <Texture*> textures;
	std::vector <int> indices;
};



#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H
//resource manager stores data of meshes, textures, ect
//loads data from files and stores in memory
class ResourceManager
{

public:
	//load a mesh object into memory. This function will return a meshData ptr.
	static MeshData* loadMesh(const std::string filepath, std::string name);

	static MeshData* getMesh(std::string name);

	static Texture* loadTexture(const std::string filepath, std::string name);
	
	static Texture* getTexture(std::string name);

private:
	static std::unordered_map <std::string, MeshData> meshes;
	static std::unordered_map <std::string,Texture> textures;

	//loads mesh data from a file
	static MeshData loadMeshDataFromFile(const std::string filepath);
	//loads texture from a file
	static Texture loadTextureFromFile(std::string filepath);


};

#endif
