#include "AssimpSkeletalAnimation.h"

AssimpSkeletalAnimation::AssimpSkeletalAnimation(const std::string animationPath) 
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(animationPath, aiProcess_Triangulate);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
        return;
    }

    if(scene->HasAnimations() == true)
    {
        aiAnimation* animation = scene->mAnimations[0];

        this->Duration = animation->mDuration;

        this->ticksPerSecond = animation->mTicksPerSecond;

        aiMatrix4x4 globaltransform = scene->mRootNode->mTransformation;

        globaltransform = globaltransform.Inverse();

        ReadHierarchyData(this->rootNode, scene->mRootNode);
        populateBoneData(animation);
    }
   
    if(scene->HasAnimations() == false)
    {
        std::cout << "No Animations Found!\n";
    }
   
}

AssimpSkeletalAnimation::~AssimpSkeletalAnimation() 
{

}

void AssimpSkeletalAnimation::ReadHierarchyData(AssimpNodeData& dest, const aiNode* src)
{
    if(!src)
    {
        std::cout << "ERROR::NO:ANIMATION::SOURCE::DATA!\n";
        return;
    }

    dest.name = src->mName.data;
    dest.transformation = AssimpGLMHelpers::ConvertMatrixToGLMFormat(src->mTransformation);
    dest.childrenCount = src->mNumChildren;

    for(unsigned int i = 0; i < src->mNumChildren; i++)
    {
        AssimpNodeData newData;
        ReadHierarchyData(newData, src->mChildren[i]);
        dest.children.push_back(newData);
    }
}

void AssimpSkeletalAnimation::populateBoneData(const aiAnimation* animation)
{
    int size = animation->mNumChannels;

    for(unsigned int i = 0; i < size; i++)
    {
        aiNodeAnim* channel = animation->mChannels[i];
        std::string boneName = channel->mNodeName.data;
        Bone newBone(boneName, 0, channel);
        Bones.push_back(newBone);
    }

}

Bone* AssimpSkeletalAnimation::FindBone(const std::string& name)
{
    auto iter = std::find_if(Bones.begin(), Bones.end(),
        [&](const Bone& Bone)
        {
            return Bone.getBoneName() == name;
        }
    );
    if (iter == Bones.end()) {return nullptr;}
    else return &(*iter);
}

float AssimpSkeletalAnimation::GetTicksPerSecond()
{
    return this->ticksPerSecond;
}

float AssimpSkeletalAnimation::GetDuration()
{
    return this->Duration;
}

AssimpNodeData& AssimpSkeletalAnimation::GetRootNode()
{
    return this->rootNode;
}