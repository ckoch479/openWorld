#include "ResourceManager.h"

std::unordered_map <std::string, Texture> ResourceManager::textures; //container for textures
std::unordered_map <std::string, MeshData> ResourceManager::meshes;  //container for mesh data

MeshData* ResourceManager::loadMesh(std::string filepath, std::string name)
{
	meshes[name] = loadMeshDataFromFile(filepath);
	return &meshes[name];
}

MeshData* ResourceManager::getMesh(std::string name)
{
	return &meshes[name];
}

MeshData ResourceManager::loadMeshDataFromFile(std::string filepath)
{
	Assimp::Importer import;

	const aiScene* scene = import.ReadFile(filepath,aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) 
	{
		std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
	}

	scene->mRootNode;
}

Texture* ResourceManager::loadTexture(const std::string filepath, std::string name)
{
	textures[name] = loadTextureFromFile(filepath);
	return &textures[name];
}

Texture* ResourceManager::getTexture(std::string name)
{
	return &textures[name];
}

Texture ResourceManager::loadTextureFromFile(std::string filepath)
{
	int width;
	int height;
	int nrChannels;

	unsigned char* data = stbi_load(filepath.c_str(), &width, &height, &nrChannels, 0);

	Texture newTexture;
	newTexture.generate(width, height, data);

	return newTexture;
}