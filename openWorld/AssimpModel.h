#pragma once
#include "glad/glad.h"

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

#include "Includes/glm/glm.hpp"
#include "Includes/glm/gtc/type_ptr.hpp"

#include "AssimpMesh.h"
#include "assimp_glm_helpers.h"

struct BoneInfo
{
	/*id is index in finalBoneMatrices*/
	int id;

	/*offset matrix transforms vertex from model space to bone space*/
	glm::mat4 offset;

};

enum textureType
{
    Diffuse,
    Specular,
    NormalT,
    Height
};

#ifndef ASSIMPMODEL_H
#define ASSIMPMODEL_H
class AssimpModel
{
public:
	AssimpModel(std::string path);

    std::map <std::string, BoneInfo>& getBoneInfoMap();

	int& getBoneCount();

    std::vector <AssimpMesh> getMeshes();

    std::vector <std::string> getDiffuseTexturePaths();

    std::vector <std::string> getSpecularTexturePaths();

    std::vector <std::string> getNormalTexturePaths();

    std::vector <std::string> getHeightTexturePaths();

    std::vector <std::string> getBoneNames();

private:

    std::vector<AssimpMesh> meshes;
    int numMeshes;

    std::string directory;

    std::vector <std::string> diffuseTextures;
    std::vector <std::string> specularTextures;
    std::vector <std::string> normalTextures;
    std::vector <std::string> heightTextures;

    std::vector <std::string> boneNames;

    //Animation Data
    std::map <std::string, BoneInfo> m_BoneInfoMap; // Map containing the name of each bone, the bone ID, and 
    //the matrix used to locate the bone from model space

    int m_BoneCounter = 0; // Number of bones in this mesh

    void processNode(aiNode* node, const aiScene* scene);

    AssimpMesh processMesh(aiMesh* mesh, const aiScene* scene);

    void SetVertexBoneDataToDefault(AssimpVertex& vertex);

    void SetVertexBoneData(AssimpVertex& vertex, int boneID, float weight);

    void ExtractBoneWeightForVertices(std::vector<AssimpVertex>& vertices, aiMesh* mesh, const aiScene* scene);

    void loadMaterialTextures(aiMaterial* mat, aiTextureType type, textureType typeName, std::vector <std::string>& texturePaths);
};

#endif