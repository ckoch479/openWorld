#include "ResourceManager.h"

std::unordered_map <std::string, Texture>       ResourceManager::textures;  //container for textures
std::unordered_map <std::string, MeshData>      ResourceManager::meshes;    //container for mesh data
std::unordered_map <std::string, AnimationData> ResourceManager::animations;//container for animation data

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
		DiffuseTextures.push_back(newTexture);
	}

	//load specular textures
	std::vector <std::string> specularTexturePaths = newModel.getSpecularTexturePaths();
	for (unsigned int i = 0; i < specularTexturePaths.size(); i++)
	{
		Texture* newTexture = loadTexture(specularTexturePaths[i], filepath + "specular_Texture");
		SpecularTextures.push_back(newTexture);
	}

	newMesh.vertices = Vertices;
	newMesh.indices = indices;
	newMesh.diffuseTextures = DiffuseTextures;
	newMesh.specularTextures = SpecularTextures;


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

	std::cout << newBone.name << std::endl;

	Bone* tempBone = animation.FindBone(newBone.name);

	if(tempBone != nullptr)
	{
		newBone.numPositions = animation.FindBone(newBone.name)->getNumPositions();
		newBone.numRotations = animation.FindBone(newBone.name)->getNumRotations();
		newBone.numScalings = animation.FindBone(newBone.name)->getNumScalings();

		newBone.Positions = animation.FindBone(newBone.name)->getPositions();
		newBone.Rotations = animation.FindBone(newBone.name)->getRotations();
		newBone.Scalings = animation.FindBone(newBone.name)->getScalings();
	}

	for(unsigned int i = 0; i < newBone.childrenCount; ++i)
	{
		AnimationBoneData childBone;
		getBoneData(childBone, boneNode.children[i], animation);

		if (newBone.name == " ") { std::cout << "no name!\n"; }
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


