#include "objAnimator.h"

objAnimator::objAnimator(Model* model)
{
	for(unsigned int i = 0; i < 100; i++)
	{
		this->finalMatricies.push_back(glm::mat4(1.0f));
	}
	this->animModel = model;
}

void objAnimator::loadAnimation(std::string& animationName, std::string& animationFilePath, bool loopingAnimation)
{
	animation* newAnim = ResourceManager::loadAnimation(animationFilePath, animationName, this->animModel->name);
	newAnim->looping = loopingAnimation;
	this->animations[animationName] = newAnim;

}

void objAnimator::playAnimation(std::string& animationName)
{
	if(this->activeAnimation != animations[animationName])
	{
		this->activeAnimation = animations[animationName];
		this->currentAnimationTime = 0.0f; //reset the animation time and start from scratch for the new one
	}
	
}

void objAnimator::update(float deltaTime)
{
	this->currentTimeStep = deltaTime; // i dont think i actually need this anymore
	this->currentAnimationTime += deltaTime * this->activeAnimation->ticksPerSecond; //delta time is in seconds, animation should be 1000 ticks per second

	if(this->currentAnimationTime > this->activeAnimation->duration)
	{
		this->currentAnimationTime = 0.0f; //reset the timer if animation duration has been passed
	}

	this->activeAnimation;

	glm::mat4 Parent = glm::mat4(1.0f); //identity matrix for the root bone
	calculateFKTransforms(&this->activeAnimation->rootNode, Parent);
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
	this->animationSkeleton = newSkeleton;
}

void objAnimator::addBone(Bone& newBone)
{

}

void objAnimator::calculateFKTransforms(AssimpNodeData* node, glm::mat4& parentTransform)
{

	std::string nodeName = node->name;
	glm::mat4 nodeTransform = node->transformation;

	animBone* bone = this->activeAnimation->animBones[nodeName];
	if (bone)
	{
		nodeTransform = calculateLocalBoneTransform(node);
	}

	glm::mat4 globalTransformation = parentTransform * nodeTransform;

	Bone* tempBone = this->animationSkeleton->getBone(nodeName); //problems here make it so cannot support bones not accounted for in animation
	//the problem here is the only bones updated in the animation are ones listed in the animation due to the above line of code
	//to fix this issue eventually the code will need to be changed so we work down the skeleton and not the animation
	if (bone)
	{
		int index = tempBone->getId();
		glm::mat4 offset = tempBone->getOffsetMat();
		this->finalMatricies[index] = globalTransformation * offset;
	}

	//std::cout << "bone name: " << node->name << std::endl;

	for (int i = 0; i < node->childrenCount; i++)
	{
		std::cout << "children names: " << node->children[i].name << std::endl;
		//calculateFKTransforms(&node->children[i],globalTransformation);
	}
	
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
	glm::vec3 result(1.0f);

	result = ((1 - factor) * (valueA)) + (factor * valueB);

	return result;
}

glm::quat objAnimator::Slerp(glm::quat rotA, glm::quat rotB, float factor)
{
	glm::quat result(1.0, 0.0, 0.0, 0.0);

	result = ((1 - factor) * rotA) + (factor * rotB);

	return result;
}

glm::mat4 objAnimator::calculateLocalBoneTransform(AssimpNodeData* node)
{
	glm::mat4 localTransform(1.0f);

	glm::mat4 localTranslation = getLocalTranslation(node);

	glm::mat4 localRotation = getLocalRotation(node);
	//scaling is not currently supported

	localTransform = localTransform * localTranslation * localRotation;

	return localTransform;
}

glm::mat4 objAnimator::getLocalTranslation(AssimpNodeData* node)
{
	glm::mat4 localTransform(1.0f);

	auto positionKeys = this->activeAnimation->animBones[node->name]->positions;
	int numPositions = this->activeAnimation->animBones[node->name]->numPositions;

	int index1 = 0; //current position keyframe
	int index2 = 0; //current position + 1

	for(int i = 0; i < numPositions; i++)
	{
		float indexTime = positionKeys[i].timeStamp;
		//find closest index to the current time to get index1

		if (this->currentAnimationTime < positionKeys[0].timeStamp)
		{
			index1 = 0;
			if(numPositions > 1)
			{
				index2 = 1; //have to check incase there is only 1 single time stamps position
			}
			break; //can break early if it is the first part of the animation
		}

		if (this->currentAnimationTime > positionKeys[numPositions].timeStamp)
		{
			index1 = numPositions; //if the time is greater than the last time stamp it is the last time stamp either reset or hold there
			index2 = 0;
			break; //break early it's the last frame
		}

		if (i + 1 < numPositions)
		{
			if (this->currentAnimationTime > indexTime && this->currentAnimationTime < positionKeys[i + 1].timeStamp)
			{
				index1 = i; //this will have issues for the first and last index so those two cases will need to be handled
				index2 = i + 1;
				break; //break early no need to keep searching
			}
		}
	}
	//after finding the closest two frames we have to interpolate between the two for that buttery smoothness in the animation
	float scaleFactor = calculateScaleFactor(positionKeys[index1].timeStamp,positionKeys[index2].timeStamp, this->currentAnimationTime);

	glm::vec3 finalTranslation = Lerp(positionKeys[index1].position, positionKeys[index2].position, scaleFactor);

	localTransform = glm::translate(localTransform, finalTranslation);
	return localTransform;
}

glm::mat4 objAnimator::getLocalRotation(AssimpNodeData* node)
{
	glm::mat4 localTransform(1.0f);

	auto rotationKeys = this->activeAnimation->animBones[node->name]->rotations;
	int numRotations = this->activeAnimation->animBones[node->name]->numRotations;

	int index1 = 0; //current position keyframe
	int index2 = 0; //current position + 1

	for (int i = 0; i < numRotations; i++)
	{
		float indexTime = rotationKeys[i].timeStamp;
		//find closest index to the current time to get index1

		if (this->currentAnimationTime < rotationKeys[0].timeStamp)
		{
			index1 = 0;
			if (numRotations > 1)
			{
				index2 = 1; //have to check incase there is only 1 single time stamps position
			}
			break; //can break early if it is the first part of the animation
		}

		if (this->currentAnimationTime > rotationKeys[numRotations].timeStamp)
		{
			index1 = numRotations; //if the time is greater than the last time stamp it is the last time stamp either reset or hold there
			index2 = 0;
			break; //break early it's the last frame
		}

		if (i + 1 < numRotations)
		{
			if (this->currentAnimationTime > indexTime && this->currentAnimationTime < rotationKeys[i + 1].timeStamp)
			{
				index1 = i; //this will have issues for the first and last index so those two cases will need to be handled
				index2 = i + 1;
				break; //break early no need to keep searching
			}
		}
	}
	//after finding the closest two frames we have to interpolate between the two for that buttery smoothness in the animation
	float scaleFactor = calculateScaleFactor(rotationKeys[index1].timeStamp, rotationKeys[index2].timeStamp, this->currentAnimationTime);

	glm::quat finalRotation = Slerp(rotationKeys[index1].orientation, rotationKeys[index2].orientation, scaleFactor);

	localTransform = localTransform * glm::toMat4(finalRotation);

	return localTransform;
}

float objAnimator::calculateScaleFactor(float lastTimeStamp, float nextTimeStamp, float currentTime)
{
	float scaleFactor = 0.0f;
	float midWayLength = currentTime - lastTimeStamp;
	float framesDiff = nextTimeStamp - lastTimeStamp;
	scaleFactor = midWayLength / framesDiff;
	return scaleFactor;
}

std::vector <glm::mat4> objAnimator::getAnimationTransforms()
{
	return this->finalMatricies;
}
