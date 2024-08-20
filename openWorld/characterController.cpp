#include "characterController.h"

characterController::characterController(windowManager* manager)
{
	this->inputManager = manager;
	//setDefaultMappings();
}

characterController::~characterController()
{

}

void characterController::setDefaultMappings()
{
	/*this->keyMap['w'] = 87;
	this->keyMap['a'] = 65;
	this->keyMap['s'] = 83;
	this->keyMap['d'] = 68;

	this->keyMap['q'];
	this->keyMap['e'];
	this->keyMap[' '] = 32;

	this->keyMap['Lctr'] = 341;
	this->keyMap['caps'] = 280;
	this->keyMap['tab'] = 258;

	this->keyMap['lshf'] = 340;
	
	this->keyMap['z'];
	this->keyMap['x'];*/

}

void characterController::updateInputs()
{
	this->keyStates = this->inputManager->getKeyStates();
}

	//this->playerMainColliderID = this->world->createOBB(glm::vec3(0.6, 1.7, 0.6));
	//this->world->updateOBBtransform(this->player->getPlayersTransform()->position, this->player->getPlayersTransform()->orientation, this->playerMainColliderID);
	//std::vector <Bone*> playerBones = this->player->getBones();
	////create obb of based on the players bones below
	//for(int i = 0; i < playerBones.size(); i++)
	//{
	//	Bone* currentBone = playerBones[i];
	//	std::string boneName = currentBone->getName();
	//	
	//	//std::cout << "bone name: " << boneName << std::endl;

	//	if (boneName == "mixamorig:LeftHandThumb1"  || boneName == "mixamorig:LeftHandThumb2" || boneName == "mixamorig:LeftHandThumb3" || boneName == "mixamorig:LeftHandThumb4")
	//	{
	//		continue;
	//	}
	//	if (boneName == "mixamorig:LeftHandIndex1" || boneName == "mixamorig:LeftHandIndex2" || boneName == "mixamorig:LeftHandIndex3" || boneName == "mixamorig:LeftHandIndex4")
	//	{
	//		continue;
	//	}
	//	if (boneName == "mixamorig:LeftHandMiddle1" || boneName == "mixamorig:LeftHandMiddle2" || boneName == "mixamorig:LeftHandMiddle3" || boneName == "mixamorig:LeftHandMiddle4")
	//	{
	//		continue;
	//	}
	//	if (boneName == "mixamorig:LeftHandRing1" || boneName == "mixamorig:LeftHandRing2" || boneName == "mixamorig:LeftHandRing3" || boneName == "mixamorig:LeftHandRing4")
	//	{
	//		continue;
	//	}
	//	if (boneName == "mixamorig:LeftHandPinky1" || boneName == "mixamorig:LeftHandPinky2" || boneName == "mixamorig:LeftHandPinky3" || boneName == "mixamorig:LeftHandPinky4")
	//	{
	//		continue;
	//	}
	//	
	//	if (boneName == "mixamorig:RightHandThumb1" || boneName == "mixamorig:RightHandThumb2" || boneName == "mixamorig:RightHandThumb3"    || boneName == "mixamorig:RightHandThumb4")
	//	{
	//		continue;
	//	}
	//	if (boneName == "mixamorig:RightHandIndex1" || boneName == "mixamorig:RightHandIndex2" || boneName == "mixamorig:RightHandIndex3"    || boneName == "mixamorig:RightHandIndex4")
	//	{
	//		continue;
	//	}
	//	if (boneName == "mixamorig:RightHandMiddle1" || boneName == "mixamorig:RightHandMiddle2" || boneName == "mixamorig:RightHandMiddle3" || boneName == "mixamorig:RightHandMiddle4")
	//	{
	//		continue;
	//	}
	//	if (boneName == "mixamorig:RightHandRing1" || boneName == "mixamorig:RightHandRing2" || boneName == "mixamorig:RightHandRing3"		 || boneName == "mixamorig:RightHandRing4")
	//	{
	//		continue;
	//	}
	//	if (boneName == "mixamorig:RightHandPinky1" || boneName == "mixamorig:RightHandPinky2"  || boneName == "mixamorig:RightHandPinky3"   || boneName == "mixamorig:RightHandPinky4")
	//	{
	//		continue;
	//	}

	//	if (boneName == "rightSocket" || boneName == "leftSocket" || boneName == "mixamorig:LeftToe_End" || boneName == "mixamorig:RightToe_End")
	//	{
	//		continue;
	//	}
	//	if (boneName == "mixamorig:RightArm" || boneName == "mixamorig:RightForeArm" || boneName == "mixamorig:LeftArm" || boneName == "mixamorig:LeftForeArm")
	//	{
	//		unsigned int OBBID = this->world->createOBB(glm::vec3(0.1, 0.3, 0.1));
	//		this->OBBids.push_back(OBBID);
	//		this->boneOBBidMap[OBBID] = currentBone->getId();
	//		continue;
	//	}
	//
	//	if (boneName == "mixamorig:Hips" || boneName == "mixamorig:Spine" || boneName == "mixamorig:Spine1" || boneName == "mixamorig:Spine2")
	//	{
	//		unsigned int OBBID = this->world->createOBB(glm::vec3(0.3, 0.4, 0.1));
	//		this->OBBids.push_back(OBBID);
	//		this->boneOBBidMap[OBBID] = currentBone->getId();
	//		continue;
	//	}

	//	if (boneName == "mixamorig:RightHand" || boneName == "mixamorig:LeftHand" || boneName == "mixamorig:HeadTop_End")
	//	{
	//		unsigned int OBBID = this->world->createOBB(glm::vec3(0.1, 0.1, 0.1));
	//		this->OBBids.push_back(OBBID);
	//		this->boneOBBidMap[OBBID] = currentBone->getId();
	//		continue;
	//	}

	//	if (boneName == "mixamorig:LeftUpLeg" || boneName == "mixamorig:LeftLeg" || boneName == "mixamorig:RightUpLeg" || boneName == "mixamorig:RightLeg")
	//	{
	//		unsigned int OBBID = this->world->createOBB(glm::vec3(0.15, 0.35, 0.15));
	//		this->OBBids.push_back(OBBID);
	//		this->boneOBBidMap[OBBID] = currentBone->getId();
	//		continue;
	//	}

	//	unsigned int OBBID = this->world->createOBB(glm::vec3(0.2,0.2,0.2));
	//	this->OBBids.push_back(OBBID);
	//	this->boneOBBidMap[OBBID] = currentBone->getId();
	//}


//void characterController::updateOBBs()
//{
//	//update large player collider
//	this->world->updateOBBtransform(this->player->getPlayersTransform()->position + glm::vec3(0,0.85,0), this->player->getPlayersTransform()->orientation, this->playerMainColliderID);
//
//	objAnimator* playerAnimator = this->player->getPlayerAnimator();
//
//	transform playerTransform = *this->player->getPlayersTransform();
//	glm::mat4 playerMat(1.0f); //create player model matrix (model space to world space)
//	playerMat = glm::translate(playerMat, playerTransform.position);
//	playerMat = playerMat * glm::toMat4(playerTransform.orientation);
//	playerMat = glm::scale(playerMat, playerTransform.scale);
//	
//	for(int i = 0; i < this->OBBids.size(); i++)
//	{
//		int boneId = this->boneOBBidMap[OBBids[i]];
//		Bone* currentBone = this->player->getPlayerModel()->skeleton->getBone(boneId);
//		
//		glm::mat4 boneTransform(1.0f);
//		boneTransform = playerAnimator->getFinalBoneTransform(currentBone->getName());
//		boneTransform = boneTransform * glm::inverse(currentBone->getOffsetMat());
//
//		glm::mat4 handMat(1.0f);
//		handMat = playerMat * boneTransform; 
//		
//		glm::vec3 skew;
//		glm::vec4 perspective;
//		glm::vec3 position;
//		glm::quat orientation;
//		glm::vec3 scale;
//		glm::decompose(handMat, scale, orientation, position, skew, perspective); //decompose mat4
//
//		this->world->updateOBBtransform(position, orientation, OBBids[i]);
//	}
//}


playerActions characterController::updateController()
{
	updateInputs();

	playerActions currentAction = idle;

	if(keyStates[87]) //w
	{
		currentAction = walkForward;
	}
	else if(keyStates[87] && keyStates[340]) //w and LShift
	{
		currentAction = jogForward;
	}

	else if (keyStates[65]) //a
	{
		currentAction = walkLeft;
	}
	else if (keyStates[65] && keyStates[340]) //a and LShift
	{
		currentAction = jogLeft;
	}

	else if (keyStates[83]) //s
	{
		currentAction = walkBack;
	}
	else if (keyStates[83] && keyStates[340]) //s and LShift
	{
		currentAction = jogBack;
	}

	else if (keyStates[68]) //d
	{
		currentAction = walkRight;
	}
	else if (keyStates[68] && keyStates[340]) //d and LShift
	{
		currentAction = jogRight;
	}

	else if(keyStates[32]) //space
	{
		currentAction = jump;
	}
	else if(keyStates[341])//Lcrtl
	{
		currentAction = crouch;
	}
	else if(keyStates[342]) //Lalt
	{
		currentAction = evading;
	}

	return currentAction;
}

void characterController::checkCombinationKeys()
{

}