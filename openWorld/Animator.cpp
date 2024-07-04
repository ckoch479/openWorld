#include "Animator.h"

std::unordered_map<Model*, animation*>						      animator::activeAnimations;

std::unordered_map<animation*, std::vector <glm::mat4>>			  animator::animationMatrices;

std::vector <Model*>									          animator::activeModels;
								  
int animator::stepper;

void animator::addAnimation(Model* model, animation* animation)
{
	stepper = 0;
	activeAnimations[model] = animation;

	for (unsigned int i = 0; i < 100; i++)
	{
		animationMatrices[activeAnimations[model]].push_back(glm::mat4(1.0f));
		//model->boneMatrices[i] = glm::mat4(1.0f);
	}

	activeModels.push_back(model);
}

void animator::removeAnimation(Model* model, animation* animation)
{

}

void animator::changeAnimation(Model* model, animation* newAnimation)
{
	activeAnimations[model] = newAnimation;
	animationMatrices[activeAnimations[model]].clear();
	for(unsigned int i = 0; i < 100; i++)
	{
		animationMatrices[activeAnimations[model]].push_back(glm::mat4(1.0f));
	}
	
}

void animator::setAnimationMatrices(Model* model, Shader* shader)
{
	shader->use();
	animation* activeAnimation = activeAnimations[model];
	if (activeAnimation)
	{
		for (unsigned int i = 0; i < 100; i++) //data gets to here and nothing happens
		{
			//glm::mat4 transform = model->boneMatrices[i];
			glm::mat4 transform = animationMatrices[activeAnimation][i];
			std::string matrixString;
			matrixString = "finalBoneMatrices[" + std::to_string(i) + "]";
			shader->SetMatrix4(matrixString.c_str(), transform);
		}
	}
	else
	{
		for (unsigned int i = 0; i < 100; i++) //data gets to here and nothing happens
		{
			std::string matrixString;
			matrixString = "finalBoneMatrices[" + std::to_string(i) + "]";
			shader->SetMatrix4(matrixString.c_str(), glm::mat4(1.0f));
		}
	}
}

void animator::updateAnimations(float dt)
{
	//this will iterate through every active model/animation and update them, then it will add the correct matrices to the matrix map for use in the shader
	for (unsigned int i = 0; i < activeModels.size(); i++)
	{
		updateAnimation(activeAnimations[activeModels[i]], dt, activeModels[i]);
		stepAnimation(activeAnimations[activeModels[i]]);
	}
}

void animator::updateAnimation(animation* animation, float dt, Model* model)
{
	animation->currentTime += animation->ticksPerSecond * dt;
	animation->currentTime = fmod(animation->currentTime, animation->duration);

	CalculateBoneTransforms(&animation->rootNode, glm::mat4(1.0f), animation, model);
}

void animator::CalculateBoneTransforms(AssimpNodeData* Node, glm::mat4 parentTransform, animation* anim, Model* model)
{

	std::string nodeName = Node->name;
	glm::mat4 nodeTransform = Node->transformation;

	animBone* bone = anim->animBones[nodeName];
	if (bone)
	{
		//nodeTransform = calculateLocalBoneTransform(anim->currentTime,bone); //problem stepping to the next part of the animation is here
		nodeTransform = stepAnimations(anim->currentTime, bone);
		//std::cout << "node: " << bone->name << " transform: " << glm::to_string(nodeTransform) << std::endl;
		//std::cout << bone->name << std::endl;
	}

	glm::mat4 globalTransformation = parentTransform * nodeTransform;

	auto boneInfoMap = model->boneMap;
	if (boneInfoMap.find(nodeName) != boneInfoMap.end())
	{
		int index = boneInfoMap[nodeName].id;
		glm::mat4 offset = boneInfoMap[nodeName].offsetMatrix;
		//std::cout << index << std::endl;
		animationMatrices[anim][index] = globalTransformation * offset;
		//model->boneMatrices[index] = globalTransformation * offset;
	}

	for (int i = 0; i < Node->childrenCount; i++)
	{
		CalculateBoneTransforms(&Node->children[i], globalTransformation, anim, model);
	}
}

glm::mat4 animator::stepAnimations(float currentTime, animBone* bone)
{
	glm::mat4 localMatrix(1.0f);

	glm::mat4 translation(1.0f);
	if (bone->currentPosition + stepper < bone->numPositions)
	{
		translation = glm::translate(glm::mat4(1.0f), bone->positions[bone->currentPosition + stepper].position);
	}
	else
	{
		translation = glm::translate(glm::mat4(1.0f), bone->positions[0].position);
	}


	glm::mat4 rotation(1.0f);
	if (bone->currentRotation + stepper < bone->numRotations)
	{
		rotation = glm::toMat4(bone->rotations[bone->currentRotation + stepper].orientation);
	}
	else
	{
		rotation = glm::toMat4(bone->rotations[0].orientation);
	}

	glm::mat4 scale(1.0f);
	if (bone->currentScale + stepper < bone->numScales)
	{
		scale = glm::scale(glm::mat4(1.0f), bone->scales[bone->currentScale].scale);
	}
	else
	{
		scale = glm::scale(glm::mat4(1.0f), bone->scales[0].scale);
	}

	localMatrix = translation * rotation * scale;
	return localMatrix;
}

void animator::stepAnimation(animation* anim)
{
	/*stepper++;
	if(stepper > 100)
	{
		stepper = 0;
	}*/
	for (unsigned int i = 0; i < anim->bones.size(); i++)
	{
		animBone* bone = &anim->bones[i];
		bone->stepPosition();
		bone->stepRotation();
		bone->stepScale();
	}

}

glm::mat4 animator::calculateLocalBoneTransform(float currentTime, animBone* bone)
{
	glm::mat4 localMatrix(1.0f);

	glm::mat4 translation = interpolatePosition(currentTime, bone);

	glm::mat4 rotation = interpolateRotation(currentTime, bone);

	glm::mat4 scale = interpolateScale(currentTime, bone);

	localMatrix = translation * rotation * scale;
	return localMatrix;
}
//doesnt work right
glm::mat4 animator::interpolatePosition(float animationTime, animBone* bone)
{
	if (1 == bone->numPositions)
	{
		return glm::translate(glm::mat4(1.0f), bone->positions[0].position);
	}

	int p0Index = bone->currentPosition;
	for (int index = 0; index < bone->numPositions - 1; ++index)
	{
		if (animationTime < bone->positions[index + 1].timeStamp)
		{
			p0Index = index;
		}
	}
	int p1Index = p0Index + 1;

	float scaleFactor = 0.0f;// calculateScaleFactor(bone->positions[p0Index].timeStamp, bone->positions[p1Index].timeStamp, animationTime);

	glm::vec3 finalPosition = glm::mix(bone->positions[p0Index].position, bone->positions[p1Index].position, scaleFactor);
	bone->currentPosition = p1Index;

	return glm::translate(glm::mat4(1.0f), finalPosition);
}
//doesnt work right
glm::mat4 animator::interpolateRotation(float animationTime, animBone* bone)
{
	if (1 == bone->numRotations)
	{
		auto rotation = glm::normalize(bone->rotations[0].orientation);
		return glm::toMat4(rotation);
	}

	int p0Index = bone->currentRotation;
	for (int index = 0; index < bone->numRotations - 1; ++index)
	{
		if (animationTime < bone->rotations[index + 1].timeStamp)
		{
			p0Index = index;
		}
	}

	int p1Index = p0Index + 1;
	float scaleFactor = calculateScaleFactor(bone->rotations[p0Index].timeStamp, bone->rotations[p1Index].timeStamp, animationTime);

	glm::quat finalRotation = glm::slerp(bone->rotations[p0Index].orientation, bone->rotations[p1Index].orientation, scaleFactor);

	bone->currentRotation = p1Index;
	return glm::toMat4(finalRotation);
}
//doesnt work right
glm::mat4 animator::interpolateScale(float animationTime, animBone* bone)
{
	if (1 == bone->numScales)
	{
		return glm::scale(glm::mat4(1.0f), bone->scales[0].scale);
	}

	int p0Index = 0;
	for (int index = 0; index < bone->numScales - 1; ++index)
	{
		if (animationTime < bone->scales[index + 1].timeStamp)
		{
			p0Index = index;
		}
	}
	int p1Index = p0Index + 1;

	float scaleFactor = calculateScaleFactor(bone->scales[p0Index].timeStamp, bone->scales[p1Index].timeStamp, animationTime);

	glm::vec3 finalScale = glm::mix(bone->scales[p0Index].scale, bone->scales[p1Index].scale, scaleFactor);

	return glm::scale(glm::mat4(1.0f), finalScale);
}

float animator::calculateScaleFactor(float lastTimeStamp, float nextTimeStamp, float currentTime)
{
	float scaleFactor = 0.0f;
	float midWayLength = currentTime - lastTimeStamp;
	float framesDiff = nextTimeStamp - lastTimeStamp;
	scaleFactor = midWayLength / framesDiff;
	return scaleFactor;
}

glm::mat4 animator::getBoneCurrentTransform(std::string name, Model* model)
{
	glm::mat4 boneTransform;

	unsigned int boneID = model->boneMap[name].id;
	boneTransform = animationMatrices[activeAnimations[model]][boneID];

	return boneTransform;
}