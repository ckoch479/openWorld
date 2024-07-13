#pragma once
#ifndef ASSIMPMODELLOADER_H
#define ASSIMPMODELLOADER_H

#include <iostream>
#include <vector>
#include <string>

#include <fstream>
#include <sstream>
#include <map>

#include "includes/glm/glm.hpp"
#include "Includes/glm/gtc/type_ptr.hpp"
#include <glm/gtx/string_cast.hpp>

#include <assimp/Importer.hpp>
#include <Assimp/scene.h>
#include <assimp/postprocess.h>

#include "renderingInfoDefinitions.h"
#include "assimpGLMConverter.h"

class assimpModelLoader
{
public:
	assimpModelLoader(std::string filePath);
	~assimpModelLoader();

	Model getModel();

	void processNode(const aiScene* scene, aiNode* node);

	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	//returns a bool for if it has specular textures or not
	bool hasSpecular();
	//returns a bool for if it has normal textures or not
	bool hasNormal();

	std::vector <Bone> getSkeleton();


private:

	void setVertexBoneDataToDefault(Vertex& vertex);

	void setVertexBoneData(Vertex& vertex, int boneID, float weight);

	void extractBoneWeightForVertices(std::vector <Vertex>& vertices, aiMesh* mesh, const aiScene* scene);

	bool hasSpecularTextures = false;
	bool hasNormalTextures = false;


	std::vector <textureData> textures;

	std::vector <std::string> diffuseTexturePaths;
	std::vector <std::string> specularTexturePath;
	std::vector <std::string> normalTexturePath;
	std::vector <std::string> emissionTexturePaths;


	std::vector <Mesh> meshes;
	std::vector <Bone> skeleton;

	std::map <std::string, Bone> boneMap;
	int boneCounter = 1;

	std::string filePath;
	std::string directory;
};

#endif // !ASSIMPMODELLOADER_H