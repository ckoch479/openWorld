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

    std::string directory = filepath.substr(0, filepath.find_last_of('/'));

	std::vector <Vertex> vertices;
	std::vector <int> indices;
	std::vector <Texture*> diffuseTextures;
	std::vector <Texture*> specularTextures;
	

	if (scene->HasMeshes() == true)
	{
		aiMesh* tempMesh = scene->mMeshes[0];
		
		//vertices
		for (unsigned int i = 0; i < tempMesh->mNumVertices; i++)
		{
			Vertex newVertex;

			newVertex.vertexPosition = glm::vec3(tempMesh->mVertices[i].x, tempMesh->mVertices[i].y, tempMesh->mVertices[i].z);

			newVertex.Normal = glm::vec3(tempMesh->mNormals[i].x, tempMesh->mNormals[i].y, tempMesh->mNormals[i].z);

			if (tempMesh->mTextureCoords[0]) 
			{
				newVertex.texCoords = glm::vec2(tempMesh->mTextureCoords[0][i].x, tempMesh->mTextureCoords[0][i].x);
			}
			else
			{
				newVertex.texCoords = glm::vec2(0.0f, 0.0f);
			}

			vertices.push_back(newVertex);
		}
		//indices
		for(unsigned int i = 0; i < tempMesh->mNumFaces; i++)
		{
			aiFace face = tempMesh->mFaces[i];
			// retrieve all indices of the face and store them in the indices vector
			for (unsigned int j = 0; j < face.mNumIndices; j++)
				indices.push_back(face.mIndices[j]);
		}

		//textures

	}
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




