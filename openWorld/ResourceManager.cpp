#include "ResourceManager.h"

std::unordered_map <std::string, Texture>       ResourceManager::textures;  //container for textures
std::unordered_map <std::string, MeshData>      ResourceManager::meshes;    //container for mesh data
std::unordered_map <std::string, AnimationData> ResourceManager::animations;//container for animation data
std::unordered_map <std::string, ModelData>		ResourceManager::models;    //container for model data

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
	std::vector <Texture*> DiffuseTextures;
	std::vector <Texture*> SpecularTextures;

	for (unsigned int i = 0; i < meshes.size(); i++)
	{
		std::vector <AssimpVertex> assimpVertices = meshes[i].getVertexData();

		for(unsigned int vertexCounter = 0; vertexCounter < assimpVertices.size(); vertexCounter++)
		{
			Vertex tempVertex;

			tempVertex.vertexPosition = assimpVertices[vertexCounter].Position;
			tempVertex.Normal =         assimpVertices[vertexCounter].Normal;
			tempVertex.texCoords =      assimpVertices[vertexCounter].TexCoords;
			//only a bone influence of 4 is allowed as of now
			tempVertex.BoneIds[0] = assimpVertices[vertexCounter].BoneIDs[0]; //std::cout << tempVertex.BoneIds[0] << "bone" << assimpVertices[vertexCounter].BoneIDs[0] << std::endl;
			tempVertex.BoneIds[1] = assimpVertices[vertexCounter].BoneIDs[1];
			tempVertex.BoneIds[2] = assimpVertices[vertexCounter].BoneIDs[2];
			tempVertex.BoneIds[3] = assimpVertices[vertexCounter].BoneIDs[3];
			//bone weights
			tempVertex.boneWeights[0] = assimpVertices[vertexCounter].weights[0];
			tempVertex.boneWeights[1] = assimpVertices[vertexCounter].weights[1];
			tempVertex.boneWeights[2] = assimpVertices[vertexCounter].weights[2];
			tempVertex.boneWeights[3] = assimpVertices[vertexCounter].weights[3];

			Vertices.push_back(tempVertex);
		}
		indices = meshes[i].getIndices();

	}

	//load diffuse textures
	std::vector <std::string> diffuseTexturePaths = newModel.getDiffuseTexturePaths();
	for(unsigned int i = 0; i < diffuseTexturePaths.size(); i++)
	{
		
		Texture* newTexture = loadTexture(diffuseTexturePaths[i], filepath + "diffuse_Texture" + std::to_string(i));
		DiffuseTextures.push_back(newTexture);
	}

	//load specular textures
	std::vector <std::string> specularTexturePaths = newModel.getSpecularTexturePaths();
	for (unsigned int i = 0; i < specularTexturePaths.size(); i++)
	{
		
		Texture* newTexture = loadTexture(specularTexturePaths[i], filepath + "specular_Texture" + std::to_string(i));
		SpecularTextures.push_back(newTexture);
	}

	newMesh.vertices = Vertices;
	newMesh.indices = indices;
	newMesh.diffuseTextures = DiffuseTextures;
	newMesh.specularTextures = SpecularTextures;
	newMesh.skeleton;

	//get bones from the model

	for (unsigned int j = 0; j < newModel.getBoneCount(); j++)
	{
		BoneData newbone;
		newbone.boneName = newModel.getBoneNames()[j];
		newbone.BoneId = newModel.getBoneInfoMap()[newbone.boneName].id;
		newbone.boneMatrix = newModel.getBoneInfoMap()[newbone.boneName].offset;

		std::cout << "BoneNames resourceManager: " << newbone.boneName << std::endl;

		newMesh.skeleton.push_back(newbone);
	}

	return newMesh;
}

ModelData* ResourceManager::loadModel(const std::string filepath, std::string name)
{
	models[name] = loadModelDataFromFile(filepath);
	return &models[name];
}

ModelData* ResourceManager::getModel(std::string name)
{
	return &models[name];
}

ModelData ResourceManager::loadModelDataFromFile(const std::string filepath)
{
	ModelData newModel;

	AssimpModel model(filepath);

	std::vector <AssimpMesh> modelMeshes = model.getMeshes();
	if(modelMeshes.size() <= 0)
	{
		std::cout << "error occured in modelMeshes!\n";
	}

	for(int i = 0; i < modelMeshes.size(); i++)
	{
		AssimpMesh* tempMesh = &modelMeshes[i];
		MeshData newMesh;
		
		std::vector <AssimpVertex> AssimpVertices = tempMesh->getVertexData();
		for (int j = 0; j < AssimpVertices.size(); j++)
		{
			Vertex newVertex;

			newVertex.vertexPosition = AssimpVertices[j].Position;
			newVertex.Normal = AssimpVertices[j].Normal;
			newVertex.texCoords = AssimpVertices[j].TexCoords;

			newVertex.BoneIds[0] = AssimpVertices[j].BoneIDs[0];
			newVertex.BoneIds[1] = AssimpVertices[j].BoneIDs[1];
			newVertex.BoneIds[2] = AssimpVertices[j].BoneIDs[2];
			newVertex.BoneIds[3] = AssimpVertices[j].BoneIDs[3];

			newVertex.boneWeights[0] = AssimpVertices[j].weights[0];
			newVertex.boneWeights[1] = AssimpVertices[j].weights[1];
			newVertex.boneWeights[2] = AssimpVertices[j].weights[2];
			newVertex.boneWeights[3] = AssimpVertices[j].weights[3];

			newMesh.vertices.push_back(newVertex);
		}

		newMesh.indices = tempMesh->getIndices();

		std::vector <std::string> diffuseTexturePaths = tempMesh->getDiffuseTexturePaths();
		std::vector <std::string> specularTexturePaths = tempMesh->getSpecularTexturePaths();

		//extract diffuse textures and load them with the resource manager
		for (int DiffuseCounter = 0; DiffuseCounter < diffuseTexturePaths.size(); DiffuseCounter++) 
		{
			std::cout <<  "diffuse texture paths: " << diffuseTexturePaths[DiffuseCounter] << "number of times loaded: " << DiffuseCounter << std::endl;
			newMesh.diffuseTextures.push_back(ResourceManager::loadTexture(diffuseTexturePaths[DiffuseCounter], "diffuse_texture" + std::to_string(DiffuseCounter)));
		}
		
		//exract specular textures and load them with the resource manager
		for (int SpecularCounter = 0; SpecularCounter < specularTexturePaths.size(); SpecularCounter++)
		{
			newMesh.specularTextures.push_back(ResourceManager::loadTexture(diffuseTexturePaths[SpecularCounter], "specular_texture" + std::to_string(SpecularCounter)));
		}


		newModel.meshes.push_back(newMesh);
	}

	//get skeleton info for the new model from the assimp model
	for (unsigned int j = 0; j < model.getBoneCount(); j++)
	{
		BoneData newbone;
		newbone.boneName = model.getBoneNames()[j];
		newbone.BoneId = model.getBoneInfoMap()[newbone.boneName].id;
		newbone.boneMatrix = model.getBoneInfoMap()[newbone.boneName].offset;

		newModel.skeleton.push_back(newbone);
	}

	
	return newModel;
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
	

	if(data)
	{
		std::cout << width << " " << height << " " << (int)data << " filepath:" << filepath << std::endl;
		std::cout << newTexture.id << "ID " << std::endl;
		newTexture.generate(width, height, data);
	}

	if(!data)
	{
		std::cout << "ERROR::TEXTURE::NOT::FOUND::AT::" << filepath << std::endl;
	}


	return newTexture;
}

AnimationData* ResourceManager::loadAnimation(const std::string filepath, std::string name)
{
	animations[name] = loadAnimationFromFile(filepath);
	return &animations[name];
}

AnimationData* ResourceManager::getAnimation(std::string name)
{
	return &animations[name];
}

void ResourceManager::getBoneData(AnimationBoneData &newBone, AssimpNodeData &boneNode, AssimpSkeletalAnimation& animation)
{

	assert(&newBone);

	newBone.name = boneNode.name;
	newBone.localTransformation = boneNode.transformation;
	newBone.childrenCount = boneNode.childrenCount;

	Bone* tempBone = animation.FindBone(newBone.name);

	if(tempBone != nullptr)
	{
		newBone.numPositions = animation.FindBone(newBone.name)->getNumPositions();
		newBone.numRotations = animation.FindBone(newBone.name)->getNumRotations();
		newBone.numScalings = animation.FindBone(newBone.name)->getNumScalings();

		newBone.Positions = animation.FindBone(newBone.name)->getPositions();
		newBone.Rotations = animation.FindBone(newBone.name)->getRotations();
		newBone.Scalings = animation.FindBone(newBone.name)->getScalings();
		newBone.boneNode = true;
	}

	if(tempBone == nullptr)
	{
		newBone.boneNode = false;
	}

	for(unsigned int i = 0; i < newBone.childrenCount; ++i)
	{
		AnimationBoneData childBone;
		getBoneData(childBone, boneNode.children[i], animation);

		newBone.children.push_back(childBone);
	}
}

AnimationData ResourceManager::loadAnimationFromFile(std::string filepath)
{
	AnimationData newAnimation;
	
	AssimpSkeletalAnimation animation(filepath);

	newAnimation.duration = animation.GetDuration();
	newAnimation.ticksPerSecond = animation.GetTicksPerSecond();

	getBoneData(newAnimation.rootBone, animation.GetRootNode() , animation);

	

	return newAnimation;
}


