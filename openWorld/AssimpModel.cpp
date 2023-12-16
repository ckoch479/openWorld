#include "AssimpModel.h"

AssimpModel::AssimpModel(std::string path)
{
    Assimp::Importer import;
    const aiScene * scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
        return;
    }
    directory = path.substr(0, path.find_last_of('/'));

    this->numMeshes = 0;

    processNode(scene->mRootNode, scene);
}

std::map <std::string, BoneInfo>& AssimpModel::getBoneInfoMap()
{
    return m_BoneInfoMap;
}

int& AssimpModel::getBoneCount()
{
    return m_BoneCounter;
}

void AssimpModel::processNode(aiNode* node, const aiScene* scene)
{
    // process all the node's meshes (if any)
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(processMesh(mesh, scene));
    }
    // then do the same for each of its children
    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene);
    }
}

AssimpMesh AssimpModel::processMesh(aiMesh* mesh, const aiScene* scene)
{
   

    std::vector<AssimpVertex> vertices;
    std::vector<unsigned int> indices;

    std::vector <std::string> diffuseTexturePaths;
    std::vector <std::string> specularTexturePaths;
    std::vector <std::string> heightTexturePaths;
    std::vector <std::string> normalTexturePaths;

    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        AssimpVertex vertex;
        SetVertexBoneDataToDefault(vertex);
        vertex.Position = AssimpGLMHelpers::GetGLMVec(mesh->mVertices[i]);
        vertex.Normal = AssimpGLMHelpers::GetGLMVec(mesh->mNormals[i]);

        if (mesh->mTextureCoords[0])
        {
            glm::vec2 vec;
            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.TexCoords = vec;
        }
        else
            vertex.TexCoords = glm::vec2(0.0f, 0.0f);

        vertices.push_back(vertex);
    }

    // process indices
    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        // retrieve all indices of the face and store them in the indices vector
        for (unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }
    // process material
    aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
 
    // 1. diffuse maps
    loadMaterialTextures(material, aiTextureType_DIFFUSE, Diffuse, diffuseTexturePaths);

    // 2. specular maps
    loadMaterialTextures(material, aiTextureType_SPECULAR, Specular, specularTexturePaths);

    // 3. normal maps
     loadMaterialTextures(material, aiTextureType_HEIGHT, Normal, normalTexturePaths);
  
    // 4. height maps
    loadMaterialTextures(material, aiTextureType_AMBIENT, Height,heightTexturePaths);
    

    ExtractBoneWeightForVertices(vertices, mesh, scene);

    // return a mesh object created from the extracted mesh data
    this->numMeshes++;
    return AssimpMesh(vertices, indices, diffuseTexturePaths,specularTexturePaths);
}

void AssimpModel::SetVertexBoneDataToDefault(AssimpVertex& vertex)
{
    for (int i = 0; i < MAX_BONE_INFLUENCE; i++)
    {
        //fills the array in mesh with bone IDs and Bone weights at a default value
        vertex.BoneIDs[i] = -1;
        vertex.weights[i] = 0.0f;
    }
}

void AssimpModel::SetVertexBoneData(AssimpVertex& vertex, int boneID, float weight)
{
    for (int i = 0; i < MAX_BONE_INFLUENCE; ++i)
    {
        if (vertex.BoneIDs[i] < 0)
        {
            //fills the array in mesh with bone IDs and Bone weights
            vertex.weights[i] = weight;
            vertex.BoneIDs[i] = boneID;
            break;
        }
    }
}

void AssimpModel::ExtractBoneWeightForVertices(std::vector<AssimpVertex>& vertices, aiMesh* mesh, const aiScene* scene)
{
    auto& boneInfoMap = m_BoneInfoMap; // Class map attached to the model/mesh containing bone info
    // boneinfo contained the ID or index of the final bone matrices and a bone offset matrix which goes from model space to bone space

    int& boneCount = m_BoneCounter; // Counter for bones

    //using assimp finds the amount of bones in a mesh and then creates a for loop to iterate through each of the bones
    for (int boneIndex = 0; boneIndex < mesh->mNumBones; ++boneIndex)
    {
        int boneID = -1;
        // name of the bone is pulled from assimp at the boneIndex number and moved to boneName string
        std::string boneName = mesh->mBones[boneIndex]->mName.C_Str();

        boneNames.push_back(boneName);

        //if when searching through the class map Bone info the current bone name is at the end
        if (boneInfoMap.find(boneName) == boneInfoMap.end())
        {
            //Creates new bone
            BoneInfo newBoneInfo;
            //ID of the bone is created using bonecount
            newBoneInfo.id = boneCount;
            //offset matrix is pulled from assimp bone array at bone index number using a function to convert from assimp format to glm format
            newBoneInfo.offset = AssimpGLMHelpers::ConvertMatrixToGLMFormat(mesh->mBones[boneIndex]->mOffsetMatrix);
            //adds the bone created above into the bone map with the info pulled from assimp
            boneInfoMap[boneName] = newBoneInfo;
            //bone ID is set to the bone count
            boneID = boneCount;
            //incriment the bonecount
            boneCount++;
            
            
        }
        else
        {// if the bone found in the mesh is not at the end or found elsewhere in the map bone ID is set to the ID of the bone found
            boneID = boneInfoMap[boneName].id;
        }
        assert(boneID != -1);
        // weights is pulled from assimp at the boneIndex and given to weights
        // this should contain the info for how much vertices are affected at the current vertex index
        auto weights = mesh->mBones[boneIndex]->mWeights;

        // how many vertices are affected by this bone
        int numWeights = mesh->mBones[boneIndex]->mNumWeights;

        for (int weightIndex = 0; weightIndex < numWeights; ++weightIndex)
        {
            //finds the ID of vertex that is influenced by the current bone
            int vertexId = weights[weightIndex].mVertexId;
            // weight is set to the strength of influence 
            float weight = weights[weightIndex].mWeight;
            assert(vertexId <= vertices.size());
            //set the vertex at vertexID boneID and weight.
            SetVertexBoneData(vertices[vertexId], boneID, weight);
        }
    }
}

void AssimpModel::loadMaterialTextures(aiMaterial* mat, aiTextureType type, textureType typeName, std::vector <std::string> &texturePaths) 
{
    for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString str; // texture path
        mat->GetTexture(type, i, &str); // material get path 

        const char* path = str.C_Str();
        std::string filename = path;
        filename = directory + '/' + filename;


        texturePaths.push_back(filename);
    }
}

std::vector <AssimpMesh> AssimpModel::getMeshes() 
{
    return this->meshes;
}

std::vector <std::string> AssimpModel::getDiffuseTexturePaths() 
{
    return this->diffuseTextures;
}

std::vector <std::string> AssimpModel::getSpecularTexturePaths() 
{
    return this->specularTextures;
}

std::vector <std::string> AssimpModel::getNormalTexturePaths() 
{
    return this->normalTextures;
}

std::vector <std::string> AssimpModel::getHeightTexturePaths() 
{
    return this->heightTextures;
}

std::vector <std::string> AssimpModel::getBoneNames() 
{
    return this->boneNames;
}