#include "Bone.h"

Bone::Bone(const std::string& name, int ID, const aiNodeAnim* channel)
{
	this->name = name;
	this->boneID = ID;
	this->localTransform = glm::mat4(1.0f);

	//get bone position keys;
	numPositions = channel->mNumPositionKeys;

	for (int positionIndex = 0; positionIndex < numPositions; ++positionIndex)
	{
		aiVector3D aiPosition = channel->mPositionKeys[positionIndex].mValue;
		float timeStamp = channel->mPositionKeys[positionIndex].mTime;
		KeyPosition data;
		data.position = AssimpGLMHelpers::GetGLMVec(aiPosition);
		data.timestamp = timeStamp;
		Positions.push_back(data);
	}

	//get bone rotation keys;
	this->numRotations = channel->mNumRotationKeys;

	for (int rotationIndex = 0; rotationIndex < numRotations; ++rotationIndex)
	{
		aiQuaternion aiOrientation = channel->mRotationKeys[rotationIndex].mValue;
		float timeStamp = channel->mRotationKeys[rotationIndex].mTime;
		KeyRotation data;
		data.rotation = AssimpGLMHelpers::GetGLMQuat(aiOrientation);
		data.timestamp = timeStamp;
		Rotations.push_back(data);
	}

	//get bone scaling keys;
	this->numScalings = channel->mNumScalingKeys;

	for (int keyIndex = 0; keyIndex < numScalings; ++keyIndex)
	{
		aiVector3D scale = channel->mScalingKeys[keyIndex].mValue;
		float timeStamp = channel->mScalingKeys[keyIndex].mTime;
		KeyScale data;
		data.scale = AssimpGLMHelpers::GetGLMVec(scale);
		data.timestamp = timeStamp;
		Scalings.push_back(data);
	}

}

Bone::~Bone()
{

}

glm::mat4 Bone::getLocalTransform()
{
	return this->localTransform;
}

std::string Bone::getBoneName() const
{
	return this->name;
}

int Bone::getBoneID()
{
	return this->boneID;
}

int Bone::getNumPositions()
{
	return this->numPositions;
}

int Bone::getNumRotations()
{
	return this->numRotations;
}

int Bone::getNumScalings()
{
	return this->numScalings;
}

std::vector <KeyPosition> Bone::getPositions()
{
	return this->Positions;
}

std::vector <KeyRotation> Bone::getRotations()
{
	return this->Rotations;
}

std::vector <KeyScale> Bone::getScalings()
{
	return this->Scalings;
}
