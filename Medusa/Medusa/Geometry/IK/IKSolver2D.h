// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "Core/Collection/List.h"


MEDUSA_BEGIN;

/*

*/

class IKSolver2D
{
public:

	/************************************
	Method:    	AnalyzeTwoBone
	Returns:   	bool		:True when a valid solution was found.
	Parameter: 	float boneLength1
	Parameter: 	float boneLength2
	Parameter: 	float targetX
	Parameter: 	float targetY
	Parameter: 	bool isBendPositive	:Solve for positive angle 2 instead of negative angle 2
	Parameter: 	float & outBoneAngle1
	Parameter: 	float & outBoneAngle2
	Comment: 	
	Given a two bone chain located at the origin (bone1 is the parent of bone2), this
	function will compute the bone angles needed for the end of the chain to line up
	with a target position. If there is no valid solution, the angles will be set to
	get as close to the target as possible.
	http://www.ryanjuckett.com/programming/analytic-two-bone-ik-in-2d/
	************************************/
	static bool AnalyzeTwoBone(float boneLength1,float boneLength2,float targetX,float targetY,bool isBendPositive,float& outBoneAngle1,float& outBoneAngle2);

	

	/************************************
	Method:    	AnalyzeAllTwoBone
	Returns:   	bool	:True when a valid solution was found.
	Parameter: 	float boneLength1
	Parameter: 	float boneLength2
	Parameter: 	float targetX
	Parameter: 	float targetY
	Parameter: 	float & outBoneAngle1_1
	Parameter: 	float & outBoneAngle2_1
	Parameter: 	float & outBoneAngle1_2
	Parameter: 	float & outBoneAngle2_2
	Comment: 	
	Given a two bone chain located at the origin (bone1 is the parent of bone2), this
	function will compute both possible solutions of bone angles needed for the end of
	the chain to line up with a target position. If there is no valid solution, the
	angles will be set to get as close to the target as possible.
	http://www.ryanjuckett.com/programming/analytic-two-bone-ik-in-2d/
	************************************/
	static bool AnalyzeAllTwoBone(float boneLength1, float boneLength2, float targetX, float targetY, float& outBoneAngle1_1, float& outBoneAngle2_1, float& outBoneAngle1_2, float& outBoneAngle2_2);

	enum class CCDResult
	{
		Success,    // the target was reached
		Processing, // still trying to reach the target
		Failure,    // failed to reach the target
	};

	struct Bone
	{
		float X;     // x position in parent space
		float Y;     // y position in parent space
		float Angle; // angle in parent space

		float WorldX;     // x position in world space
		float WorldY;     // y position in world space
		float WorldAngle; // angle in world space
		float WorldCosine; //cosine of world angle
		float WorldSine; // sine of world angle
	};
	
	static void CalculateWorldBone(List<Bone,NoCompare>& bones);


	/************************************
	Method:    	CyclicCoordinateDescent
	Returns:   	IKSolver2D::CCDResult
	Parameter: 	List<Bone> & bones
	Parameter: 	float targetX
	Parameter: 	float targetY
	Parameter: 	float arrivalDistance	:Must get within this range of the target
	Comment: 	
	Given a bone chain located at the origin, this function will perform a single cyclic
	coordinate descent (CCD) iteration. This finds a solution of bone angles that places
	the final bone in the given chain at a target position. The supplied bone angles are
	used to prime the CCD iteration. If a valid solution does not exist, the angles will
	move as close to the target as possible. The user should resupply the updated angles
	until a valid solution is found (or until an iteration limit is met).
	http://www.ryanjuckett.com/programming/cyclic-coordinate-descent-in-2d/
	************************************/
	static CCDResult CyclicCoordinateDescent(List<Bone, NoCompare>& bones, float targetX, float targetY, float arrivalDistance);
	
};

MEDUSA_END;