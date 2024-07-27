#include "objAnimator.h"

objAnimator::objAnimator(Model* model)
{
	for(unsigned int i = 0; i < 100; i++)
	{
		this->finalMatricies.push_back(glm::mat4(1.0f));
	}
}

void objAnimator::loadAnimation(std::string& animationName, std::string& animationFilePath)
{
	animation* newAnim = ResourceManager::loadAnimation(animationFilePath, animationName, this->animModel->name);
	this->animations[animationName] = newAnim;
}

void objAnimator::playAnimation(std::string& animationName)
{
	if(this->activeAnimation != animations[animationName])
	{
		this->activeAnimation = animations[animationName];
	}
	
}

void objAnimator::update(float deltaTime)
{

}

void objAnimator::applyForwardKinematics(std::string& boneName, glm::quat& rotation)
{

}

void objAnimator::applyInverseKinematics(std::string& endEffector, glm::vec3& targetPosition)
{

}

void objAnimator::solveIK()
{

}

void objAnimator::setSkeleton(skeleton* newSkeleton)
{

}

void objAnimator::addBone(Bone& newBone)
{

}

void objAnimator::calculateFKTransforms(AssimpNodeData* node, glm::mat4& parentTransform)
{

}

void objAnimator::updateForwardKinematics()
{

}

void objAnimator::updateInverseKinematics()
{

}

void objAnimator::blendAnimations()
{

}

glm::vec3 objAnimator::Lerp(glm::vec3 valueA, glm::vec3 valueB, float factor)
{
	return glm::vec3(1.0f);
}

glm::quat objAnimator::Slerp(glm::quat rotA, glm::quat rotB, float factor)
{
	return glm::vec3(1.0f);
}
