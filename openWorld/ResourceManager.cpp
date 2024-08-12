#include "ResourceManager.h"

std::unordered_map <std::string, Texture>      ResourceManager::textures;
std::unordered_map <std::string, Shader>       ResourceManager::shaders;
std::unordered_map <std::string, Mesh>		   ResourceManager::meshes;
std::unordered_map <std::string, Model>        ResourceManager::models;
std::unordered_map <std::string, animation>    ResourceManager::animations;
std::unordered_map <std::string, skeleton>     ResourceManager::skeletons;

std::vector <std::string>                      ResourceManager::loadedTextures; //makes sure we do not load textures multiple times into memory
std::vector <std::string>					   ResourceManager::loadedModels;
std::vector <std::string>					   ResourceManager::loadedAnimations;

Mesh* ResourceManager::loadMesh(std::string filePath, std::string name)
{
	meshes[name] = loadMeshFromFile(filePath);
	return &meshes[name];
}

Mesh* ResourceManager::getMesh(std::string name)
{
	return &meshes[name];
}

Model* ResourceManager::loadModel(std::string filePath, std::string name)
{
	bool hasBeenLoaded = false;
	for (unsigned int i = 0; i < loadedModels.size(); i++)
	{
		if (loadedModels[i] == name)
		{
			hasBeenLoaded = true;
		}
	}

	if (!hasBeenLoaded)
	{
		//std::cout << "loading model: " << filePath << std::endl;
		models[name] = loadModelFromFile(filePath);
		models[name].name = name;
		loadedModels.push_back(filePath);
	}

	return &models[name];
}

Model* ResourceManager::getModel(std::string name)
{
	return &models[name];
}

Texture* ResourceManager::loadTexture(const char* file, bool sRGB, std::string name)
{
	bool hasBeenLoaded = false;
	for (unsigned int i = 0; i < loadedTextures.size(); i++)
	{
		if (loadedTextures[i] == name)
		{
			hasBeenLoaded = true;
		}
	}

	if (!hasBeenLoaded)
	{
		textures[name] = loadTextureFromFile(file, sRGB);
		//std::cout << file << "\n";
		loadedTextures.push_back(name);
	}

	return &textures[name];
}

Texture* ResourceManager::getTexture(std::string name)
{
	return &textures[name];
}

Shader* ResourceManager::loadShader(const char* vertexFilepath, const char* fragmentFilePath, const char* geometryFilePath, std::string name)
{
	shaders[name] = loadShaderFromFile(vertexFilepath, fragmentFilePath, geometryFilePath);
	return &shaders[name];
}

Shader* ResourceManager::getShader(std::string name)
{
	return &shaders[name];
}

animation* ResourceManager::loadAnimation(std::string filePath, std::string name, std::string modelName)
{
	bool hasBeenLoaded = false;
	for (unsigned int i = 0; i < loadedAnimations.size(); i++)
	{
		if (loadedAnimations[i] == name)
		{
			hasBeenLoaded = true;
		}
	}

	if (!hasBeenLoaded)
	{
		Model* model = getModel(modelName);
		animations[name] = loadAnimationFromFile(filePath, model);
	//	std::cout << filePath << "\n";
		loadedAnimations.push_back(name);
	}

	return &animations[name];
}

animation* ResourceManager::getAnimation(std::string name)
{
	return &animations[name];
}

void ResourceManager::clear()
{
	//delete all shaders	
	for (auto iter : shaders)
		glDeleteProgram(iter.second.ID);

	//delete all textures
	for (auto iter : textures)
		glDeleteTextures(1, &iter.second.id);

}

Shader	ResourceManager::loadShaderFromFile(const char* vertexFilePath, const char* fragmentFilePath, const char* geometryFilePath)
{
	std::string vertexCode;
	std::string fragmentCode;
	std::string geometryCode;
	try
	{
		std::ifstream vertexShaderFile(vertexFilePath);
		std::ifstream fragmentShaderFile(fragmentFilePath);
		std::stringstream vShaderStream, fShaderStream;

		vShaderStream << vertexShaderFile.rdbuf();
		fShaderStream << fragmentShaderFile.rdbuf();

		vertexShaderFile.close();
		fragmentShaderFile.close();

		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();

		if (geometryFilePath != nullptr)
		{
			std::ifstream geometryShaderFile(geometryFilePath);
			std::stringstream gShaderStream;
			gShaderStream << geometryShaderFile.rdbuf();
			geometryShaderFile.close();
			geometryCode = gShaderStream.str();
		}
	}
	catch (std::exception e)
	{
		std::cout << "ERROR::SHADER: Failed to read shader files \n";
	}
	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();
	const char* gShaderCode = geometryCode.c_str();

	Shader shader;
	shader.Compile(vShaderCode, fShaderCode, geometryFilePath != nullptr ? gShaderCode : nullptr);
	return shader;
}

Texture ResourceManager::loadTextureFromFile(const char* file, bool sRGB)
{
	// stbi_set_flip_vertically_on_load(true);
	Texture newTexture;

	int width, height, nrChannels;

	unsigned char* data = stbi_load(file, &width, &height, &nrChannels, 0);

	if (data)
	{

		if (nrChannels == 1)
		{
			newTexture.internalFormat = GL_RED;
		}
		else if (nrChannels == 3)
		{
			if (sRGB == false)
			{
				newTexture.internalFormat = GL_RGB;
				newTexture.imageFormat = GL_RGB;
			}
			if (sRGB == true)
			{
				newTexture.internalFormat = GL_SRGB;
				newTexture.imageFormat = GL_RGB;
			}

		}
		else if (nrChannels == 4)
		{
			if (sRGB == false)
			{
				newTexture.internalFormat = GL_RGBA;
				newTexture.imageFormat = GL_RGBA;
			}
			if (sRGB == true)
			{
				newTexture.internalFormat = GL_SRGB_ALPHA;
				newTexture.imageFormat = GL_RGBA;
			}

		}

	}

	newTexture.generate(width, height, data);

	stbi_image_free(data);
	return newTexture;
}

animation ResourceManager::loadAnimationFromFile(std::string filePath, Model* model)
{
	animation newAnimation;

	assimpAnimationLoader newLoader(filePath, model);
	newAnimation = newLoader.getAnimation();

	for (unsigned int i = 0; i < newAnimation.bones.size(); i++)
	{
		newAnimation.animBones[newAnimation.bones[i].name] = &newAnimation.bones[i]; //again makes it easier for me to find the data i need 
	}

	//std::cout << "animation loaded from: " << filePath << " \nanimation has a duration of: " << newAnimation.duration << " with: " << newAnimation.ticksPerSecond << " ticks per second\n";
	//this is to make sure that ticks per second is actually being loaded in which it is but im going to keep it for now just in case

	return newAnimation;
}


Model ResourceManager::loadModelFromFile(std::string filePath)
{
	Model newModel;

	assimpModelLoader loader(filePath); //load model using the assimp model loading class
	newModel = loader.getModel();
	//textures still need to be added to the resource manager
	//iterate through each mesh and load in their textures
	for (unsigned int i = 0; i < newModel.meshes.size(); i++)
	{
		Mesh* mesh = &newModel.meshes[i];

		mesh->material.diffuse0 = ResourceManager::loadTexture(mesh->material.diffuseData.filePath.c_str(), true, mesh->material.diffuseData.uniqueName.c_str());

		if (loader.hasSpecular())
		{
			mesh->material.specular0 = ResourceManager::loadTexture(mesh->material.specularData.filePath.c_str(), false, mesh->material.specularData.uniqueName.c_str());

		}
		if (!loader.hasSpecular())
		{
			mesh->material.specular0 = nullptr;
		}

		if (loader.hasNormal())
		{
			mesh->material.normalMap0 = ResourceManager::loadTexture(mesh->material.normalData.filePath.c_str(), false, mesh->material.normalData.uniqueName.c_str());

		}
		if (!loader.hasNormal())
		{
			mesh->material.normalMap0 = nullptr;
		}

		mesh->material.shininess = 128.0f;

		//this is a fix for the first vertex in every mesh not loading its boneid and weights for some reason
		for (unsigned int j = 0; j < newModel.meshes[i].vertices.size(); j++)
		{


			//std::cout << "mesh vertex: " << j << " boneID: " << newModel.meshes[i].vertices[j].boneIDs[0] << std::endl;// " boneName: " << newModel.Skeleton[newModel.meshes[i].vertices[j].boneIDs[0]].name << std::endl;
			if (newModel.meshes[i].vertices[j].boneWeights[0] == 0.0f)
			{

				//std::cout << "mesh of: " << i << " has vertex: " << j << " with a bone weight of 0.0f!\n";

				/*std::cout << "bone weight 0: " << newModel.meshes[i].vertices[j].boneWeights[0] << std::endl;
				std::cout << "bone weight 1: " << newModel.meshes[i].vertices[j].boneWeights[1] << std::endl;
				std::cout << "bone weight 2: " << newModel.meshes[i].vertices[j].boneWeights[2] << std::endl;
				std::cout << "bone weight 3: " << newModel.meshes[i].vertices[j].boneWeights[3] << std::endl;

				std::cout << "bone id 0: " << newModel.meshes[i].vertices[j].boneIDs[0] << std::endl;
				std::cout << "bone id 1: " << newModel.meshes[i].vertices[j].boneIDs[1] << std::endl;
				std::cout << "bone id 2: " << newModel.meshes[i].vertices[j].boneIDs[2] << std::endl;
				std::cout << "bone id 3: " << newModel.meshes[i].vertices[j].boneIDs[3] << std::endl;*/

				//for some reason the first vertex of every mesh loaded does not add bone data to it's vertices and im not sure why
				if (j < newModel.meshes[i].vertices.size() - 1)
				{
					newModel.meshes[i].vertices[j].boneIDs[0] = newModel.meshes[i].vertices[j + 1].boneIDs[0];
					newModel.meshes[i].vertices[j].boneIDs[1] = newModel.meshes[i].vertices[j + 1].boneIDs[1];
					newModel.meshes[i].vertices[j].boneIDs[2] = newModel.meshes[i].vertices[j + 1].boneIDs[2];
					newModel.meshes[i].vertices[j].boneIDs[3] = newModel.meshes[i].vertices[j + 1].boneIDs[3];

					newModel.meshes[i].vertices[j].boneWeights[0] = newModel.meshes[i].vertices[j + 1].boneWeights[0];
					newModel.meshes[i].vertices[j].boneWeights[1] = newModel.meshes[i].vertices[j + 1].boneWeights[1];
					newModel.meshes[i].vertices[j].boneWeights[2] = newModel.meshes[i].vertices[j + 1].boneWeights[2];
					newModel.meshes[i].vertices[j].boneWeights[3] = newModel.meshes[i].vertices[j + 1].boneWeights[3];
				}

			}

		}
	}
	std::vector <Bone> modelBones = loader.getSkeleton();
	skeleton newSkeleton(modelBones);
	
	skeletons[filePath] = newSkeleton;

	newModel.skeleton = &skeletons[filePath];

	return newModel;
}

Mesh ResourceManager::loadMeshFromFile(std::string filePath)
{
	Mesh newMesh;
	std::cout << "WARNING::FUNCTION::NOT::IMPLIMENTED!\n";

	return newMesh;
}
