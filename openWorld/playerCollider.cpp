#include "playerCollider.h"

playerCollider::playerCollider(PhysicsWorld* world, skeleton* playerSkeleton, objAnimator* playerAnimator, glm::vec3* playerPos, glm::quat* playerOrient)
{
	this->world = world;
	this->playerSkeleton = playerSkeleton;
	this->playerAnimator = playerAnimator;
	this->playerPos = playerPos;
	this->playerOrient = playerOrient;

	generateMainPlayerCollider();
	generateBoneColliders();

}

playerCollider::~playerCollider()
{

}

void playerCollider::generateMainPlayerCollider()
{
	this->mainBoxId = this->world->createOBB(glm::vec3(0.6, 1.7, 0.6));
	this->world->updateOBBtransform(*this->playerPos + glm::vec3(0, 0.85, 0), glm::inverse(*this->playerOrient), this->mainBoxId);
}

void playerCollider::generateBoneColliders()
{
	std::vector <Bone*> colliderBones;

	for(int i = 0; i < this->playerSkeleton->getBoneCount(); i++)
	{
		bool isExcludedBone = false;
		Bone* currentBone = this->playerSkeleton->getBone(i);
		//seach the vector of excluded bones and set the exclude flag if it is present
		for(int j = 0; j < this->excludedBones.size(); j++)
		{
			if(currentBone->getId() == this->excludedBones[j])
			{
				isExcludedBone = true;
				break;
			}
		}
		if(isExcludedBone == false)
		{
			colliderBones.push_back(currentBone);
		}
	}
	//bones should be sorted if they are collider bones are not, now generate colliders for the remaining bones;

	for(unsigned int i = 0; i < colliderBones.size(); i++)
	{
		Bone* currentBone = colliderBones[i];
		int boneId = currentBone->getId();

		if(boneId == 33 || boneId == 34 || boneId == 8 || boneId == 9)
		{
			unsigned int OBBID = this->world->createOBB(glm::vec3(0.1, 0.3, 0.1));
			this->OBBids.push_back(OBBID);
			this->boneOBBidMap[OBBID] = currentBone->getId();
			continue;
		}

		else if (boneId == 0 || boneId == 1 || boneId == 2 || boneId == 3)
		{
			unsigned int OBBID = this->world->createOBB(glm::vec3(0.3, 0.4, 0.1));
			this->OBBids.push_back(OBBID);
			this->boneOBBidMap[OBBID] = currentBone->getId();
			continue;
		}

		else if (boneId == 35 || boneId == 10 || boneId == 6)
		{
			unsigned int OBBID = this->world->createOBB(glm::vec3(0.1, 0.1, 0.1));
			this->OBBids.push_back(OBBID);
			this->boneOBBidMap[OBBID] = currentBone->getId();
			continue;
		}

		else if (boneId == 57 || boneId == 58 || boneId == 62 || boneId == 63)
		{
			unsigned int OBBID = this->world->createOBB(glm::vec3(0.15, 0.35, 0.15));
			this->OBBids.push_back(OBBID);
			this->boneOBBidMap[OBBID] = currentBone->getId();
			continue;
		}

		else
		{
			unsigned int OBBID = this->world->createOBB(glm::vec3(0.2, 0.2, 0.2));
			this->OBBids.push_back(OBBID);
			this->boneOBBidMap[OBBID] = currentBone->getId();
		}

	}
}

void playerCollider::updateColliders(float dt)
{
	this->world->updateOBBtransform(*this->playerPos + glm::vec3(0, 0.85, 0), glm::inverse(*this->playerOrient), this->mainBoxId);

	glm::mat4 playerMat(1.0f);
	playerMat = glm::translate(playerMat, *this->playerPos);
	playerMat = playerMat * glm::toMat4(glm::inverse(*this->playerOrient));
	playerMat = glm::scale(playerMat, glm::vec3(1.0f));

	for (int i = 0; i < this->OBBids.size(); i++)
	{
		int boneId = this->boneOBBidMap[OBBids[i]];
		Bone* currentBone = this->playerSkeleton->getBone(boneId);
		
		glm::mat4 boneTransform(1.0f);
		boneTransform = playerAnimator->getFinalBoneTransform(currentBone->getName());
		boneTransform = boneTransform * glm::inverse(currentBone->getOffsetMat());

		glm::mat4 handMat(1.0f);
		handMat = playerMat * boneTransform; 
		
		glm::vec3 skew;
		glm::vec4 perspective;
		glm::vec3 position;
		glm::quat orientation;
		glm::vec3 scale;
		glm::decompose(handMat, scale, orientation, position, skew, perspective); //decompose mat4
		this->world->updateOBBtransform(position, orientation, OBBids[i]);
	}
	
}

unsigned int playerCollider::getMainBoxId()
{
	return this->mainBoxId;
}

orientedBoundingBox* playerCollider::getMainBox()
{
	return this->mainBox;
}

std::vector <unsigned int> playerCollider::getBoneColliderIds()
{
	return this->OBBids;
}

//std::vector <orientedBoundingBox*> playerCollider::getBoneColliders()
//{
//
//}
