
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
#include "Shader.h"

#include "renderingInfoDefinitions.h"
#include "animationDataDefinitions.h"

#include "assimpModelLoader.h"
#include "assimpAnimationLoader.h"


#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

enum textureType
{
	diffuse,
	specular,
	normal,
};

//resource manager stores data of meshes, textures, ect
//loads data from files and stores in memory
class ResourceManager
{

public:
	//load a mesh object into memory. This function will return a meshData ptr.
	static Mesh* loadMesh(std::string filePath, std::string name);

	static Mesh* getMesh(std::string name);

	static Model* loadModel(std::string filePath, std::string name);

	static Model* getModel(std::string name);

	static Texture* loadTexture(const char* file, bool sRGB, std::string name);

	static Texture* getTexture(std::string name);

	static Shader* loadShader(const char* vertexFilepath, const char* fragmentFilePath, const char* geometryFilePath, std::string name);

	static Shader* getShader(std::string name);

	static animation* loadAnimation(std::string filePath, std::string name, std::string modelName);

	static animation* getAnimation(std::string name);

	static void clear();

private:
	ResourceManager() {};

	static std::unordered_map <std::string, Mesh> meshes;
	static std::unordered_map <std::string, Model> models;
	static std::unordered_map <std::string, Texture> textures;
	static std::unordered_map <std::string, Shader> shaders;
	static std::unordered_map <std::string, animation> animations;
	//animations

	static std::vector <std::string> loadedTextures;
	static std::vector <std::string> loadedModels;
	static std::vector <std::string> loadedAnimations;

	static Shader	loadShaderFromFile(const char* vertexFilePath, const char* fragmentFilePath, const char* geometryFilePath);
	static Texture	loadTextureFromFile(const char* file, bool sRGB);
	static Model	loadModelFromFile(std::string filePath);
	static Mesh		loadMeshFromFile(std::string filePath);
	static animation loadAnimationFromFile(std::string filePath, Model* model);



};

#endif
