#include "objAnimator.h"

objAnimator::objAnimator(Model* model)
{
	for(unsigned int i = 0; i < 100; i++)
	{
		this->finalMatricies.push_back(glm::mat4(1.0f));
	}
	this->animModel = model;
	this->animationSkeleton = model->skeleton; //itll be assumed you're using the models skeleton however it can be changed manually afterwards (maybe a modified version of its normal?)

	for(int i = 0; i < model->skeleton->getBoneCount(); i++)
	{
		Bone* currentBone = model->skeleton->getBone(i); //iterate through each bone;
		if(currentBone->getId() > 0) //if the bone has an id greater that 0 add it to its parents
		{
			int parentBone = currentBone->getParent();
			model->skeleton->getBone(parentBone)->addChild(currentBone->getId());
		}
	}

	/*for(unsigned int i = 0; i < model->skeleton->getBoneCount(); i++)
	{
		int tempId = i;
		Bone* bone = this->animationSkeleton->getBone(tempId);
		int boneId = 0;
		int parentId = 0;
		int numChildren = 0;
		std::vector <int> childrenIds;
		std::string name;

		boneId = bone->getId();
		name = bone->getName();
		parentId = bone->getParent();
		numChildren = bone->getNumChildren();
		childrenIds = bone->getChildren();


		std::cout << "bone: " << name << " id: " << boneId << " parent id: " << parentId << " numChildren: " << numChildren << " children ids: ";
		for(unsigned int j = 0; j < childrenIds.size(); j++)
		{
			std::cout << childrenIds[j] << " ";
		}
		std::cout << std::endl;
	}*/
}

void objAnimator::loadAnimation(std::string& animationName, std::string& animationFilePath, bool loopingAnimation)
{
	std::cout << "loading animation: " << animationName << std::endl;
	animation* newAnim = ResourceManager::loadAnimation(animationFilePath, animationName, this->animModel->name);
	newAnim->looping = loopingAnimation;
	this->animations[animationName] = newAnim;

}

//repeating animation
void objAnimator::playAnimation(std::string animationName)
{	//its ugly but it works :D
	//still need to fix when two animations are attempting to play at once (decide who wins and is shown)
	if(this->activeAnimation != ResourceManager::getAnimation(animationName))
	{	//if the current animation is a non looping animation it can not be changed until it is done playing
		if (this->activeAnimation)
		{
			if (this->activeAnimation->looping == true)
			{
				//handle non looping animations
				if (animations[animationName]->looping == false)
				{
					this->returnAnimation = this->activeAnimation;
					this->activeAnimation = ResourceManager::getAnimation(animationName);
				}
				//handle looping animations
				if (animations[animationName]->looping == true)
				{
					this->activeAnimation = ResourceManager::getAnimation(animationName);
				}

				this->currentAnimationTime = 0.0f; //reset the animation time and start from scratch for the new one
				//std::cout << "animation change! : " << this->activeAnimation->name << std::endl;
			}
		}
		if(!this->activeAnimation)
		{
			this->activeAnimation = ResourceManager::getAnimation(animationName);
		}

	}
	//this->isblendAnimation = false;
}

void objAnimator::playBlendAnimation(std::string animationA, std::string animationB, float blendFactor)
{
	this->blendFactor = blendFactor;

	if (this->activeAnimation != animations[animationA] && this->blendAnimation != animations[animationB])
	{
		this->activeAnimation = animations[animationA];
		this->blendAnimation = animations[animationB];
		this->isblendAnimation = true;
	}
}

void objAnimator::update(float deltaTime)
{
	for(int i = 0; i < 100; i++)
	{
		this->updateBone[i] = false; //reset the bool array
	}

	this->currentTimeStep = deltaTime; // i dont think i actually need this anymore
	this->currentAnimationTime += deltaTime * this->activeAnimation->ticksPerSecond; //delta time is in seconds, animation should be 1000 ticks per second

	if(this->activeAnimation->looping == false) //if this is a non looping animation play until it is over
	{
		//run animation as normal until time is up when time is up reset animation to return animation
		if (this->currentAnimationTime > this->activeAnimation->duration)
		{
			this->activeAnimation = returnAnimation;
			this->currentAnimationTime = 0.0f; //reset the timer if animation duration has been passed
		}

	    glm::mat4 Parent = glm::mat4(1.0f); //identity matrix for the root bone
		calculateFKTransforms(&this->activeAnimation->rootNode, Parent);
	}
	else //if the animation does loop just play as normal
	{
		if (this->currentAnimationTime > this->activeAnimation->duration)
		{
			this->currentAnimationTime = 0.0f; //reset the timer if animation duration has been passed
		}

		glm::mat4 Parent = glm::mat4(1.0f); //identity matrix for the root bone
		calculateFKTransforms(&this->activeAnimation->rootNode, Parent);
	}

	//idk if itll work yet but we'll find out
	//solveIK();
	this->IKchains.clear(); //doesnt work so act as if it doesnt exsist for now
	this->modifiers.clear();//clear the modifer list after applying them
	//iterate through all non updated bones
	for(int i = 0; i < 100; i++)
	{
		bool hasBeenUpdated = this->updateBone[i];
		if(!hasBeenUpdated)
		{
		//update bones that have not been updated by their parent bone now
			
			Bone* tempBone = this->animationSkeleton->getBone(i);
			if(tempBone->getName() != "NO::BONE")
			{
				int parentID = tempBone->getParent();
				Bone* parentBone = this->animationSkeleton->getBone(parentID);

				//i believe node transform is bone transform relative to it's parent (i was right, leaving this in here just in case i need it later to refer to (or if i doubt myself again))

				glm::mat4 parentTransform = this->finalMatricies[parentID] * glm::inverse(parentBone->getOffsetMat()); //moves the transform back to bonespace
				
				glm::mat4 localTransform(1.0f);
				localTransform = tempBone->getBindPose(); //gets the bone's transform relative to it's parent loaded in when the model is loaded
				
				glm::mat4 globalTransform = parentTransform * localTransform;
				this->finalMatricies[i] = globalTransform * tempBone->getOffsetMat(); //works for the most part however the bone is in the parent's position not it's own i think due to
				//the node transform

			}
		}
	}
	
	
}

void objAnimator::applyInverseKinematics(std::string& endEffectorName, glm::vec3& targetPosition)
{
	Bone* endEffector = this->animationSkeleton->getBone(endEffectorName);
	if(endEffector)
	{
		inverseKinematicChain chain;
		chain.endEffector = endEffector;
		chain.targetPosition = targetPosition; //this needs to be in local coordinates!
		

		Bone* current = endEffector;
		for (int i = 0; i < 4; i++)
		{
			chain.bones.push_back(current);
			int parentID = current->getParent();
			current = this->animationSkeleton->getBone(parentID);
			if(current->getId() == 0)
			{
				break;
			}
		}
		IKchains.push_back(chain);
	}


}

void objAnimator::solveIK()
{	//iterate through inverse kinematic chains
	for(auto& chain : IKchains)
	{
		for(int iter = 0; iter < 10; ++iter)
		{
			for (int i = 0; i < chain.bones.size(); i++) //this in theory should start at the furthest bone and then work its way down until the bone before the endEffector
			{
				Bone* bone = chain.bones[i]; std::cout << "bone id: " << bone->getId() << " name: " << bone->getName() << std::endl;
				glm::vec3 endBonePosition = glm::vec4(1.0f) * (this->finalMatricies[chain.endEffector->getId()]); //in local space
				glm::vec3 currentBonePosition = glm::vec4(1.0f) * this->finalMatricies[bone->getId()]; std::cout << "current bone position: " << glm::to_string(currentBonePosition) << std::endl;
				glm::vec3 toEndEffector = endBonePosition - currentBonePosition; std::cout << "vector to end effector: " << glm::to_string(toEndEffector) << std::endl;
				glm::vec3 toTarget = chain.targetPosition - currentBonePosition; std::cout << "to target: " << glm::to_string(toTarget) << std::endl;


				//final mats are in local space
				//multiplying by inverse boneOffset moves to local space
				//target pos is not correct either it needs to be move to model pos as well

				//std::cout << "target Position: " << glm::to_string(chain.targetPosition) << std::endl;

				if(bone->getId() == chain.endEffector->getId())
				{
					//std::cout << "end effector selected error!\n";
					continue;
				}

				float angle = 0.0f;
				glm::vec3 axis(0,1,0);

				glm::quat newRotation(1.0,0.0,0.0,0.0);

				float cosTheta = glm::dot(toTarget, toEndEffector);
				if(cosTheta < 0.999) 
				{
					angle = acos(cosTheta);
					axis = glm::normalize( glm::cross(toEndEffector, toTarget));

					glm::quat rotation = glm::angleAxis(angle, axis);
					newRotation = glm::normalize(rotation);
				}

				glm::mat4 transformMatrix(1.0f);
				updateBones(bone, axis, angle);


				glm::vec3 endEffectorPos = glm::vec4(1.0f) * this->finalMatricies[chain.endEffector->getId()]; //pos of the target bone in world space
				//break the loop if the end effector has reached close enough to the target point
				float length = glm::length((endEffectorPos - chain.targetPosition));
				if (length < 0.01)
				{
					break;
				}

			}

		}


	}

	this->IKchains.clear();

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
		nodeTransform = calculateLocalBoneTransform(node); //problem here (again)
		for(int i = 0; i < this->modifiers.size(); i++)
		{
			if(this->modifiers[i].boneName == nodeName)
			{
				//apply modifer that matches this bone name
				nodeTransform = nodeTransform;// *glm::toMat4(modifiers[i].rotation);
			}
		}
	}

	glm::mat4 globalTransformation = parentTransform * nodeTransform;

	Bone* tempBone = this->animationSkeleton->getBone(nodeName); //problems here make it so cannot support bones not accounted for in animation
	//the problem here is the only bones updated in the animation are ones listed in the animation due to the above line of code
	//to fix this issue eventually the code will need to be changed so we work down the skeleton and not the animation
	if (tempBone)
	{
		int index = tempBone->getId();
		glm::mat4 offset = tempBone->getOffsetMat();
		this->finalMatricies[index] = globalTransformation * offset; //should be from bone space to local space
		this->updateBone[index] = true;
	}

	for (int i = 0; i < node->childrenCount; ++i)
	{
		calculateFKTransforms(&node->children[i],globalTransformation);
	}

}

void objAnimator::blendAnimations(animation* animA, animation* animB, float factor)
{	//bad no no, dont interpolate matrices
	//std::vector <glm::mat4> animAFinalMats;
	//std::vector <glm::mat4> animBFinalMats;
	//for (int i = 0; i < 100; i++) { animAFinalMats.push_back(glm::mat4(1.0f)); animBFinalMats.push_back(glm::mat4(1.0f)); }

	//glm::mat4 Parent = glm::mat4(1.0f); //identity matrix for the root bone
	//for anim a
	//calculateFKblend(&animA->rootNode, Parent, animAFinalMats);
    //for anim b
	//calculateFKblend(&animB->rootNode, Parent, animBFinalMats);



}

void objAnimator::calculateFKblend(AssimpNodeData* node, glm::mat4& parentTransform)
{
	std::string nodeName = node->name;
	glm::mat4 nodeTransform = node->transformation;
	
	animBone* bone = this->activeAnimation->animBones[nodeName];
	if (bone)
	{
		nodeTransform = calculateLocalBoneTransform(node); //problem here (again)

		for (int i = 0; i < this->modifiers.size(); i++)
		{
			if (this->modifiers[i].boneName == nodeName)
			{
				//apply modifer that matches this bone name
				nodeTransform = nodeTransform;// *glm::toMat4(modifiers[i].rotation);
			}
		}
	}

	glm::mat4 globalTransformation = parentTransform * nodeTransform;

	Bone* tempBone = this->animationSkeleton->getBone(nodeName); //problems here make it so cannot support bones not accounted for in animation
	//the problem here is the only bones updated in the animation are ones listed in the animation due to the above line of code
	//to fix this issue eventually the code will need to be changed so we work down the skeleton and not the animation
	if (tempBone)
	{
		int index = tempBone->getId();
		glm::mat4 offset = tempBone->getOffsetMat();
		this->finalMatricies[index] = globalTransformation * offset; //should be from bone space to local space
		this->updateBone[index] = true;
	}

	for (int i = 0; i < node->childrenCount; ++i)
	{
		calculateFKTransforms(&node->children[i], globalTransformation);
	}
}

glm::vec3 objAnimator::Lerp(glm::vec3 valueA, glm::vec3 valueB, float factor)
{
	glm::vec3 result(1.0f);

	result = ((1 - factor) * (valueA)) + (factor * valueB);

	return result;
}

//slerp is fixed using glm, apparently i suck at math
glm::quat objAnimator::Slerp(glm::quat rotA, glm::quat rotB, float factor)
{
	glm::quat result(1.0, 0.0, 0.0, 0.0);

	//result = ((1 - factor) * rotA) + (factor * rotB);
	result = glm::slerp(rotA, rotB, factor);

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
			if(numPositions > 0)
			{
				index2 = 1; //have to check incase there is only 1 single time stamps position
			}
			else { index2 = 0; }
			break; //can break early if it is the first part of the animation
		}

		if (this->currentAnimationTime > positionKeys[numPositions - 1].timeStamp)
		{
			index1 = numPositions - 1; //if the time is greater than the last time stamp it is the last time stamp either reset or hold there
			index2 = index1;
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

	//intercept here if a blend is happening
	if(this->blendAnimation && this->isblendAnimation)
	{
		glm::vec3 animBfinalTranslation(1.0f);

		 positionKeys = this->blendAnimation->animBones[node->name]->positions;

		numPositions = this->blendAnimation->animBones[node->name]->numPositions;

		index1 = 0; //current position keyframe
		index2 = 0; //current position + 1

		for (int i = 0; i < numPositions; i++)
		{
			float indexTime = positionKeys[i].timeStamp;
			//find closest index to the current time to get index1

			if (this->currentAnimationTime < positionKeys[0].timeStamp)
			{
				index1 = 0;
				if (numPositions > 0)
				{
					index2 = 1; //have to check incase there is only 1 single time stamps position
				}
				else { index2 = 0; }
				break; //can break early if it is the first part of the animation
			}

			if (this->currentAnimationTime > positionKeys[numPositions - 1].timeStamp)
			{
				index1 = numPositions - 1; //if the time is greater than the last time stamp it is the last time stamp either reset or hold there
				index2 = index1;
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
		float scaleFactor = calculateScaleFactor(positionKeys[index1].timeStamp, positionKeys[index2].timeStamp, this->currentAnimationTime);

		animBfinalTranslation = Lerp(positionKeys[index1].position, positionKeys[index2].position, scaleFactor);

		finalTranslation = Lerp(finalTranslation, animBfinalTranslation, this->blendFactor);
	}
	
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

		if (this->currentAnimationTime > rotationKeys[numRotations - 1].timeStamp)
		{
			index1 = numRotations - 1; //if the time is greater than the last time stamp it is the last time stamp either reset or hold there
			index2 = index1;
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

	if (this->blendAnimation && this->isblendAnimation)
	{
		glm::quat finalRotationB(1.0, 0.0, 0.0, 0.0);

		 rotationKeys = this->blendAnimation->animBones[node->name]->rotations;
		numRotations = this->blendAnimation->animBones[node->name]->numRotations;

		index1 = 0; //current position keyframe
		index2 = 0; //current position + 1

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

			if (this->currentAnimationTime > rotationKeys[numRotations - 1].timeStamp)
			{
				index1 = numRotations - 1; //if the time is greater than the last time stamp it is the last time stamp either reset or hold there
				index2 = index1;
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

		finalRotationB = Slerp(rotationKeys[index1].orientation, rotationKeys[index2].orientation, scaleFactor);
	//	std::cout << "final secondary rotation: " << glm::to_string(finalRotationB) << std::endl;
	//	std::cout << "animation blend value: " << this->blendFactor << std::endl;
		finalRotation = Slerp(finalRotation, finalRotationB, this->blendFactor);
	}

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

std::vector <glm::mat4>* objAnimator::getAnimationTransforms()
{
	return &this->finalMatricies;
}

glm::mat4 objAnimator::getFinalBoneTransform(std::string boneName)
{
	int boneId = this->animationSkeleton->getBone(boneName)->getId();
	glm::mat4 finalMatrix(1.0f);

	if (this->activeAnimation)
	{
		finalMatrix = this->finalMatricies[boneId];
	}
	if (!this->activeAnimation)
	{
		std::cout << "ERROR::MODEL::DOES::NOT::HAVE::CURRENT::ANIMATION\n";
	}

	return finalMatrix;
}

void objAnimator::updateBones(Bone* bone, glm::vec3 axis, float angle)
{
	//apply transform to each bone then to each of its children
	glm::mat4 globalTransform = this->finalMatricies[bone->getId()] * glm::inverse(bone->getOffsetMat());//sets the transform into local bone space

	globalTransform = glm::rotate(globalTransform,angle,axis); // not sure if this is correct

	this->finalMatricies[bone->getId()] = (globalTransform) *bone->getOffsetMat(); //apply transform given by the IK method in local space then transform to world space

	for(unsigned int i = 0; i < bone->getNumChildren(); i++)
	{
		updateBones(this->animationSkeleton->getBone(bone->getChildren()[i]), axis,angle);
	}
}

void objAnimator::addModifier(std::string boneName, glm::quat rotation)
{
	animationModifier newModifier;
	newModifier.rotation = rotation;
	newModifier.boneName = boneName;

	this->modifiers.push_back(newModifier);
}

void objAnimator::useBlendAnimations(bool setter)
{
	this->isblendAnimation = setter;
}

//final matrices are in local space, initial transforms are in bone space, target point is usually going to be in world space
