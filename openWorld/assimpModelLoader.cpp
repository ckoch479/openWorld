#include "assimpModelLoader.h"
assimpModelLoader::assimpModelLoader(std::string filePath)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(filePath, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace | aiProcess_PopulateArmatureData);

	if (nullptr == scene)
	{
		std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
		assert(scene == nullptr); //throw an error and close the program if a model cannot be loaded
	}

	directory = filePath.substr(0, filePath.find_last_of('/'));

	processNode(scene, scene->mRootNode);

	if (normalTexturePath.size() > 0)
	{
		hasNormalTextures = true;
	}
	if (specularTexturePath.size() > 0)
	{
		hasSpecularTextures = true;
	}
}

bool assimpModelLoader::hasSpecular()
{
	return hasSpecularTextures;
}

bool assimpModelLoader::hasNormal()
{
	return hasNormalTextures;
}

assimpModelLoader::~assimpModelLoader()
{

}

Model assimpModelLoader::getModel()
{
	Model newModel;
	newModel.meshes = this->meshes;
	

	return newModel;
}

void assimpModelLoader::processNode(const aiScene* scene, aiNode* node)
{
	for (unsigned int i = 0; i < node->mNumMeshes; i++) //process and extract all meshes of this node
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		this->meshes.push_back(processMesh(mesh, scene));
	}

	for (unsigned int i = 0; i < node->mNumChildren; i++) //process each of this nodes children
	{
		processNode(scene, node->mChildren[i]);
	}

}

Mesh assimpModelLoader::processMesh(aiMesh* mesh, const aiScene* scene)
{
	std::vector <Vertex> vertices;
	std::vector <unsigned int> indices;
	std::vector <textureData> textures;
	Mesh newMesh;

	//extract all vertices
	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex newVertex;
		setVertexBoneDataToDefault(newVertex);

		newVertex.vertexPosition = AssimpGLMHelpers::GetGLMVec(mesh->mVertices[i]);

		if (mesh->HasNormals())
		{
			newVertex.normal = AssimpGLMHelpers::GetGLMVec(mesh->mNormals[i]);
		}
		else { newVertex.normal = glm::vec3(0, 0, 0); }

		if (mesh->mTextureCoords[0])
		{
			glm::vec2 textureCoords;
			textureCoords.x = mesh->mTextureCoords[0][i].x;
			textureCoords.y = mesh->mTextureCoords[0][i].y;
			newVertex.textureCoordinates = textureCoords;

			newVertex.tangent = AssimpGLMHelpers::GetGLMVec(mesh->mTangents[i]);

			newVertex.bitTangent = AssimpGLMHelpers::GetGLMVec(mesh->mBitangents[i]);
		}
		else { newVertex.textureCoordinates = glm::vec2(0, 0); }

		vertices.push_back(newVertex);
	}
	//extract all indices
	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++)
		{
			indices.push_back(face.mIndices[j]);
		}
	}
	//extract all textures
	aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

	//iterate through all diffuse textures
	for (unsigned int i = 0; i < material->GetTextureCount(aiTextureType_DIFFUSE); i++)
	{
		aiString str;
		material->GetTexture(aiTextureType_DIFFUSE, i, &str);

		textureData texture;
		texture.filePath = this->directory + '/' + str.C_Str();
		texture.uniqueName = str.C_Str();
		textures.push_back(texture);
		newMesh.material.diffuseData = texture;
	}

	for (unsigned int i = 0; i < material->GetTextureCount(aiTextureType_SPECULAR); i++)
	{
		aiString str;
		material->GetTexture(aiTextureType_SPECULAR, i, &str);


		textureData texture;
		texture.filePath = this->directory + '/' + str.C_Str();
		texture.uniqueName = str.C_Str();
		textures.push_back(texture);

		newMesh.material.specularData = texture;
		this->specularTexturePath.push_back(texture.filePath);
	}

	for (unsigned int i = 0; i < material->GetTextureCount(aiTextureType_HEIGHT); i++)
	{
		aiString str;
		material->GetTexture(aiTextureType_HEIGHT, i, &str);

		textureData texture;
		texture.filePath = this->directory + '/' + str.C_Str();
		texture.uniqueName = str.C_Str();
		textures.push_back(texture);

	}

	for (unsigned int i = 0; i < material->GetTextureCount(aiTextureType_NORMALS); i++)
	{
		aiString str;
		material->GetTexture(aiTextureType_NORMALS, i, &str);

		textureData texture;
		texture.filePath = this->directory + '/' + str.C_Str();
		texture.uniqueName = str.C_Str();
		textures.push_back(texture);

		newMesh.material.normalData = texture;
		this->normalTexturePath.push_back(texture.filePath);
	}

	//std::cout << "mesh: " << mesh->mName.data << std::endl << std::endl;
	extractBoneWeightForVertices(vertices, mesh, scene);

	newMesh.vertices = vertices;
	newMesh.indices = indices;


	return newMesh;
}

std::vector <Bone> assimpModelLoader::getSkeleton()
{
	return this->skeleton;
}

void assimpModelLoader::setVertexBoneDataToDefault(Vertex& vertex)
{
	for (unsigned int i = 0; i < 4; ++i) //4 is set because that is the max amount of bones that can influence one vertex
	{
		vertex.boneIDs[i] = -1;
		vertex.boneWeights[i] = 0.0f;
	}
}

void assimpModelLoader::setVertexBoneData(Vertex& vertex, int boneID, float weight)
{
	for (unsigned int i = 0; i < 4; ++i)
	{
		if (vertex.boneIDs[i] < 0)
		{
			vertex.boneWeights[i] = weight;
			vertex.boneIDs[i] = boneID;
			break;
		}

	}
}

//this whole thing here really needs to be redone to ensure bone relationships are correct and data is properly transferred over 
void assimpModelLoader::extractBoneWeightForVertices(std::vector <Vertex>& vertices, aiMesh* mesh, const aiScene* scene)
{
	std::map <std::string, Bone>& boneInfoMap = this->boneMap;
	int& boneCount = this->boneCounter;

	//this preloads the model bonemap with bones
	for (int boneIndex = 0; boneIndex < mesh->mNumBones; boneIndex++)
	{
	
		int boneID = -1;
		std::string boneName = mesh->mBones[boneIndex]->mName.C_Str(); //this top code block gets the bone info from assimp like its name offset and sets an id for it
		if (boneInfoMap.find(boneName) == boneInfoMap.end())
		{
			Bone newBone(boneCount, boneName, AssimpGLMHelpers::ConvertMatrixToGLMFormat(mesh->mBones[boneIndex]->mOffsetMatrix));
			//newBone.id = boneCount;
			//newBone.offsetMatrix = AssimpGLMHelpers::ConvertMatrixToGLMFormat(mesh->mBones[boneIndex]->mOffsetMatrix);
			//newBone.name = boneName;
			boneInfoMap[boneName] = newBone;
			boneID = boneCount;
			boneCount++;
			this->skeleton.push_back(newBone);
		}
		else
		{
			boneID = boneInfoMap[boneName].getId();
		}
		assert(boneID != -1);
		auto weights = mesh->mBones[boneIndex]->mWeights;
		int numWeights = mesh->mBones[boneIndex]->mNumWeights;

		for (int weightIndex = 0; weightIndex < numWeights; ++weightIndex) //this code block sets the bone id and weights to the Vertex itself
		{
			int vertexID = weights[weightIndex].mVertexId;
			float weight = weights[weightIndex].mWeight;
			assert(vertexID <= vertices.size());

			setVertexBoneData(vertices[vertexID], boneID, weight);
		}

		//std::cout << "end of bone: " << boneIndex << std::endl;
	}

	//once all the bones have been "sorted through now add their parent/child relationship
	for(unsigned int i = 0; i < mesh->mNumBones; i++)
	{
		std::string boneName = mesh->mBones[i]->mName.C_Str();
		Bone* currentBone = &boneMap[boneName];
		aiBone* assimpBone = mesh->mBones[i];

		int parentId;

		parentId = boneMap[assimpBone->mNode->mParent->mName.C_Str()].getId();

		currentBone->setParent(parentId);
	}

}