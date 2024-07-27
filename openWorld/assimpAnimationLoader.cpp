#include "assimpAnimationLoader.h"
assimpAnimationLoader::assimpAnimationLoader(const std::string& filePath, Model* model)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(filePath, aiProcess_Triangulate);
	assert(scene && scene->mRootNode);
	aiAnimation* animation = scene->mAnimations[0];
	this->name = animation->mName.data;
	this->Duration = animation->mDuration;
	this->ticksPerSecond = animation->mTicksPerSecond;
	aiMatrix4x4 globalTransformation = scene->mRootNode->mTransformation;
	globalTransformation = globalTransformation.Inverse();
	readHierarchyData(this->rootNode, scene->mRootNode);
	readMissingBones(animation, model);
}

assimpAnimationLoader::~assimpAnimationLoader()
{

}

animation assimpAnimationLoader::getAnimation()
{
	animation newAnimation;
	newAnimation.duration = this->Duration;
	newAnimation.name = this->name;
	newAnimation.ticksPerSecond = this->ticksPerSecond;
	newAnimation.bones = this->bones;
	newAnimation.rootNode = this->rootNode;

	return newAnimation;
}

animBone* assimpAnimationLoader::findBone(const std::string& name)
{
	auto iter = std::find_if(bones.begin(), bones.end(), [&](const animBone& bone)
		{
			return bone.name == name;
		}
	);
	if (iter == bones.end()) return nullptr;
	else return &(*iter);
}

void assimpAnimationLoader::readMissingBones(const aiAnimation* animation, Model* model)
{
	int size = animation->mNumChannels;

	
	int boneCount = model->skeleton->getBoneCount();

	for (int i = 0; i < size; ++i)
	{
		auto channel = animation->mChannels[i];
		std::string boneName = channel->mNodeName.data;

		Bone* tempBone = model->skeleton->getBone(boneName);
		if(tempBone == NULL)
		{
			//offset matrix isnt correct but animation really shouldnt be adding in bones to begin with so thatll be gone
			Bone newBone(boneCount, boneName, glm::mat4(1.0f));
			model->skeleton->addBone(newBone);
			std::cout << "new bone added in animation!\n";
		}

		bones.push_back(createBoneNode(channel->mNodeName.data, model->skeleton->getBone(boneName)->getId(), channel));
	}
	
	
}

void assimpAnimationLoader::readHierarchyData(AssimpNodeData& dest, const aiNode* src)
{
	assert(src);

	dest.name = src->mName.data;
	dest.transformation = AssimpGLMHelpers::ConvertMatrixToGLMFormat(src->mTransformation);
	dest.childrenCount = src->mNumChildren;

	for (int i = 0; i < src->mNumChildren; ++i)
	{
		AssimpNodeData newData;
		readHierarchyData(newData, src->mChildren[i]);
		dest.children.push_back(newData);
	}
}

animBone assimpAnimationLoader::createBoneNode(std::string name, int id, const aiNodeAnim* channel)
{
	animBone newBone;

	newBone.name = name;
	newBone.id = id;
	newBone.localTransform = glm::mat4(1.0f);

	newBone.numPositions = channel->mNumPositionKeys;
	newBone.numRotations = channel->mNumRotationKeys;
	newBone.numScales = channel->mNumScalingKeys;

	for (int positionIndex = 0; positionIndex < newBone.numPositions; positionIndex++)
	{
		aiVector3D aiPosition = channel->mPositionKeys[positionIndex].mValue;
		float timeStamp = channel->mPositionKeys[positionIndex].mTime;
		KeyPosition data;
		data.position = AssimpGLMHelpers::GetGLMVec(aiPosition);
		data.timeStamp = timeStamp;
		newBone.positions.push_back(data);
	}

	for (int rotationIndex = 0; rotationIndex < newBone.numRotations; rotationIndex++)
	{
		aiQuaternion aiOrientation = channel->mRotationKeys[rotationIndex].mValue;
		float timeStamp = channel->mRotationKeys[rotationIndex].mTime;
		keyRotation data;
		data.orientation = AssimpGLMHelpers::GetGLMQuat(aiOrientation);
		data.timeStamp = timeStamp;
		newBone.rotations.push_back(data);
	}

	for (int scaleIndex = 0; scaleIndex < newBone.numScales; scaleIndex++)
	{
		aiVector3D scale = channel->mScalingKeys[scaleIndex].mValue;
		float timeStamp = channel->mScalingKeys[scaleIndex].mTime;
		keyScale data;
		data.scale = AssimpGLMHelpers::GetGLMVec(scale);
		data.timeStamp = timeStamp;
		newBone.scales.push_back(data);
	}

	return newBone;
}