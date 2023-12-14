
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

#include "AssimpModel.h"
#include "AssimpMesh.h"
#include "Bone.h"
#include "AssimpSkeletalAnimation.h"


#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H
//basic mesh data i.e. vertices,texcoords,normals,indices,ect
struct Vertex
{
	glm::vec3 vertexPosition;
	glm::vec2 texCoords;
	glm::vec3 Normal;

	int BoneIds[MAX_BONE_INFLUENCE];

	float boneWeights[MAX_BONE_INFLUENCE];
};

struct BoneData
{
	int BoneId;
	std::string boneName;
	glm::mat4 boneMatrix;
};

//this animation bone data is to determine the heirarchy of bones for the animation Bone data itself is for which bones are attached to the mesh itself
struct AnimationBoneData
{
	glm::mat4 localTransformation;
	std::string name;
	int childrenCount;
	std::vector<AnimationBoneData> children;

	std::vector <KeyPosition> Positions;
	std::vector <KeyRotation> Rotations;
	std::vector <KeyScale> Scalings;

	int numPositions;
	int numRotations;
	int numScalings;

	//placed here incase this is just a transform node and not an actual bone
	bool boneNode;
};

struct MeshData
{
	std::vector <Vertex> vertices;
	std::vector <Texture*> diffuseTextures;
	std::vector <Texture*> specularTextures;
	std::vector <unsigned> indices;

	std::vector <BoneData> skeleton;
};

struct AnimationData
{
	float duration;
	int ticksPerSecond;
	AnimationBoneData rootBone;
};


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

	static AnimationData* loadAnimation(const std::string filepath, std::string name);

	static AnimationData* getAnimation(std::string name);

private:
	static std::unordered_map <std::string, MeshData> meshes;
	static std::unordered_map <std::string, Texture> textures;
	static std::unordered_map <std::string, AnimationData> animations;

	//loads mesh data from a file
	static MeshData loadMeshDataFromFile(const std::string filepath);
	//loads texture from a file
	static Texture loadTextureFromFile(std::string filepath);

	static AnimationData loadAnimationFromFile(std::string filepath);

	static void getBoneData(AnimationBoneData& newBone, AssimpNodeData& boneNode, AssimpSkeletalAnimation& animation);

};

#endif
