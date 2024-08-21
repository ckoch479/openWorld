#pragma once


#include <iostream>
#include <vector>

#include "includes/glm/glm.hpp"
#include "Includes/glm/gtc/type_ptr.hpp"
#include "Includes/glm/gtc/quaternion.hpp"
#include "Includes/glm/gtx/matrix_decompose.hpp"

#include "skeleton.h"
#include "PhysicsWorld.h"
#include "objAnimator.h"
#include "orientedBoundingBox.h"

#ifndef PLAYERCOLLIDER_H
#define PLAYERCOLLIDER_H

class playerCollider
{
public:

	playerCollider(PhysicsWorld* world, skeleton* playerSkeleton, objAnimator* playerAnimator, glm::vec3* playerPos , glm::quat* playerOrient);
	~playerCollider();

	void updateColliders(float dt);

	unsigned int getMainBoxId();

	orientedBoundingBox* getMainBox();

	std::vector <unsigned int> getBoneColliderIds();

	//std::vector <orientedBoundingBox*> getBoneColliders();

private:

	void generateMainPlayerCollider();

	void generateBoneColliders();

	PhysicsWorld* world;
	skeleton* playerSkeleton;
	objAnimator* playerAnimator;

	glm::vec3* playerPos;
	glm::quat* playerOrient;

	//main collision box surrounding the player, mainly will be used for environmental collisions
	orientedBoundingBox* mainBox; 
	unsigned int mainBoxId;

	std::vector <unsigned int> OBBids;
	std::unordered_map<unsigned int, int> boneOBBidMap;

	//bones excluded from being a collider bone by their ids
	std::vector <int> excludedBones 
	{
		11,12,13,14,15,16,17,18,
		19,20,21,22,23,24,25,26,
		27,28,29,30,31,36,37,38,
		39,40,41,42,43,44,45,46,
		47,48,49,50,51,52,53,54,
		55,56,61,66
	};

};

#endif

//
//mixamorig:Neck: 4
//mixamorig : Head : 5
//mixamorig : LeftShoulder : 7
//mixamorig : RightShoulder : 32
//mixamorig : LeftFoot : 59
//mixamorig : LeftToeBase : 60
//mixamorig : RightFoot : 64
//mixamorig : RightToeBase : 65
//size : 0.2, 0.2, 0.2;
//
//special sizes :
//mixamorig:RightArm: 33
//mixamorig : RightForeArm : 34
//mixamorig : LeftArm : 8
//mixamorig : LeftForeArm : 9
//size : 0.1, 0.3, 0.1;
//
//mixamorig:Hips: 0
//mixamorig : Spine : 1
//mixamorig : Spine1 : 2
//mixamorig : Spine2 : 3
//size : 0.3, 0.4, 0.1;
//
//mixamorig:RightHand: 35
//mixamorig : LeftHand : 10
//mixamorig : HeadTop_End : 6
//size : 0.1, 0.1, 0.1;
//
//mixamorig:LeftUpLeg: 57
//mixamorig : LeftLeg : 58
//mixamorig : RightUpLeg : 62
//mixamorig : RightLeg : 63
//size : 0.15, 0.35, 0.15;

//non collider bones
//boneNames: mixamorig:LeftHandThumb1: 11
//boneNames : mixamorig : LeftHandThumb2 : 12
//boneNames : mixamorig : LeftHandThumb3 : 13
//boneNames : mixamorig : LeftHandThumb4 : 14
//boneNames : mixamorig : LeftHandIndex1 : 15
//boneNames : mixamorig : LeftHandIndex2 : 16
//boneNames : mixamorig : LeftHandIndex3 : 17
//boneNames : mixamorig : LeftHandIndex4 : 18
//boneNames : mixamorig : LeftHandMiddle1 : 19
//boneNames : mixamorig : LeftHandMiddle2 : 20
//boneNames : mixamorig : LeftHandMiddle3 : 21
//boneNames : mixamorig : LeftHandMiddle4 : 22
//boneNames : mixamorig : LeftHandRing1 : 23
//boneNames : mixamorig : LeftHandRing2 : 24
//boneNames : mixamorig : LeftHandRing3 : 25
//boneNames : mixamorig : LeftHandRing4 : 26
//boneNames : mixamorig : LeftHandPinky1 : 27
//boneNames : mixamorig : LeftHandPinky2 : 28
//boneNames : mixamorig : LeftHandPinky3 : 29
//boneNames : mixamorig : LeftHandPinky4 : 30
//boneNames : leftSocket : 31
//
//boneNames : mixamorig : RightHandThumb1 : 36
//boneNames : mixamorig : RightHandThumb2 : 37
//boneNames : mixamorig : RightHandThumb3 : 38
//boneNames : mixamorig : RightHandThumb4 : 39
//boneNames : mixamorig : RightHandIndex1 : 40
//boneNames : mixamorig : RightHandIndex2 : 41
//boneNames : mixamorig : RightHandIndex3 : 42
//boneNames : mixamorig : RightHandIndex4 : 43
//boneNames : mixamorig : RightHandMiddle1 : 44
//boneNames : mixamorig : RightHandMiddle2 : 45
//boneNames : mixamorig : RightHandMiddle3 : 46
//boneNames : mixamorig : RightHandMiddle4 : 47
//boneNames : mixamorig : RightHandRing1 : 48
//boneNames : mixamorig : RightHandRing2 : 49
//boneNames : mixamorig : RightHandRing3 : 50
//boneNames : mixamorig : RightHandRing4 : 51
//boneNames : mixamorig : RightHandPinky1 : 52
//boneNames : mixamorig : RightHandPinky2 : 53
//boneNames : mixamorig : RightHandPinky3 : 54
//boneNames : mixamorig : RightHandPinky4 : 55
//boneNames : rightSocket : 56
//boneNames : mixamorig : LeftToe_End : 61
//boneNames : mixamorig : RightToe_End : 66