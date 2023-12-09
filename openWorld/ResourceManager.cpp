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
	MeshData newMesh;

	//get data from assimpMesh class
	AssimpModel newModel(filepath);
	std::vector <AssimpMesh> meshes = newModel.getMeshes();

	std::vector <Vertex> Vertices;
	std::vector <unsigned int> indices;
	std::vector <Texture*> Textures;

	for (unsigned int i = 0; i < meshes.size(); i++)
	{
		std::vector <glm::vec3> positions = meshes[i].getVertexPositions();
		std::vector <glm::vec3> normals = meshes[i].getVertexNormals();
		std::vector <glm::vec2> texcoords = meshes[i].getVertexTexCoords();

		for(unsigned int j = 0; j < positions.size(); j++)
		{
			Vertex tempVertex;

			tempVertex.vertexPosition = positions[j];
			tempVertex.Normal = normals[j];
			tempVertex.texCoords = texcoords[j];

			Vertices.push_back(tempVertex);
		}

		indices = meshes[i].getIndices();
		
	}

	//load diffuse textures
	std::vector <std::string> diffuseTexturePaths = newModel.getDiffuseTexturePaths();
	for(unsigned int i = 0; i < diffuseTexturePaths.size(); i++)
	{
		Texture* newTexture = loadTexture(diffuseTexturePaths[i], filepath + "diffuse_Texture");
		Textures.push_back(newTexture);
	}

	newMesh.vertices = Vertices;
	newMesh.indices = indices;
	newMesh.diffuseTextures = Textures;

	return newMesh;
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




