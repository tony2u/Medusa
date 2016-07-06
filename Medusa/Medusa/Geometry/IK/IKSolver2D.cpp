// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "IKSolver2D.h"
#include "Core/Math/Math.h"
MEDUSA_BEGIN;


bool IKSolver2D::AnalyzeTwoBone(float boneLength1, float boneLength2, float targetX, float targetY, bool isBendPositive, float& outBoneAngle1, float& outBoneAngle2)
{
	const float epsilon = 0.0001f; // used to prevent division by small numbers
	bool foundValidSolution = true;
	float targetDistSqr = (targetX*targetX + targetY*targetY);

	// Compute a new value for outBoneAngle2 along with its cosine
	float sinAngle2;
	float cosAngle2;

	float cosAngle2_denom = 2 * boneLength1*boneLength2;
	if (cosAngle2_denom > epsilon)
	{
		cosAngle2 = (targetDistSqr - boneLength1*boneLength1 - boneLength2*boneLength2) / (cosAngle2_denom);

		// if our result is not in the legal cosine range, we can not find a
		// legal solution for the target
		if ((cosAngle2 < -1.f) || (cosAngle2 > 1.f))
			foundValidSolution = false;

		// clamp our value into range so we can calculate the best
		// solution when there are no valid ones
		cosAngle2 = Math::Clamp(cosAngle2, -1.f, 1.f);

		// compute a new value for outBoneAngle2
		outBoneAngle2 = Math::Acos(cosAngle2);

		// adjust for the desired bend direction
		if (!isBendPositive)
			outBoneAngle2 = -outBoneAngle2;

		// compute the sine of our angle
		sinAngle2 = Math::Sin(outBoneAngle2);
	}
	else
	{
		// At least one of the bones had a zero length. This means our
		// solvable domain is a circle around the origin with a radius
		// equal to the sum of our bone lengths.
		float totalLenSqr = (boneLength1 + boneLength2) * (boneLength1 + boneLength2);

		if (!Math::IsEqual(totalLenSqr, targetDistSqr))
		{
			foundValidSolution = false;
		}

		// Only the value of outBoneAngle1 matters at this point. We can just
		// set outBoneAngle2 to zero. 
		outBoneAngle2 = 0.f;
		cosAngle2 = 1.f;
		sinAngle2 = 0.f;
	}

	// Compute the value of outBoneAngle1 based on the sine and cosine of outBoneAngle2
	float triAdjacent = boneLength1 + boneLength2*cosAngle2;
	float triOpposite = boneLength2*sinAngle2;

	float tanY = targetY*triAdjacent - targetX*triOpposite;
	float tanX = targetX*triAdjacent + targetY*triOpposite;

	// Note that it is safe to call Atan2(0,0) which will happen if targetX and
	// targetY are zero
	outBoneAngle1 = Math::Atan2(tanY, tanX);

	return foundValidSolution;
}

bool IKSolver2D::AnalyzeAllTwoBone(float boneLength1, float boneLength2, float targetX, float targetY, float& outBoneAngle1_1, float& outBoneAngle2_1, float& outBoneAngle1_2, float& outBoneAngle2_2)
{
	const float epsilon = 0.0001f; // used to prevent division by small numbers
	bool foundValidSolution = true;
	float targetDistSqr = (targetX*targetX + targetY*targetY);

	// Compute a new value for outBoneAngle2 along with its cosine
	float sinAngle2;
	float cosAngle2;

	float cosAngle2_denom = 2 * boneLength1*boneLength2;
	if (cosAngle2_denom > epsilon)
	{
		cosAngle2 = (targetDistSqr - boneLength1*boneLength1 - boneLength2*boneLength2) / (cosAngle2_denom);

		// if our result is not in the legal cosine range, we can not find a
		// legal solution for the target
		if ((cosAngle2 < -1.f) || (cosAngle2 > 1.f))
			foundValidSolution = false;

		// clamp our value into range so we can calculate the best
		// solution when there are no valid ones
		cosAngle2 = Math::Clamp(cosAngle2, -1.f, 1.f);

		// compute a new value for outBoneAngle2
		outBoneAngle2_1 = Math::Acos(cosAngle2);

		// compute the sine of our angle
		sinAngle2 = Math::Sin(outBoneAngle2_1);
	}
	else
	{
		// At least one of the bones had a zero length. This means our
		// solvable domain is a circle around the origin with a radius
		// equal to the sum of our bone lengths.
		float totalLenSqr = (boneLength1 + boneLength2) * (boneLength1 + boneLength2);

		if (!Math::IsEqual(totalLenSqr, targetDistSqr))
		{
			foundValidSolution = false;
		}

		// Only the value of outBoneAngle1 matters at this point. We can just
		// set outBoneAngle2 to zero. 
		outBoneAngle2_1 = 0.f;
		cosAngle2 = 1.f;
		sinAngle2 = 0.f;
	}

	// Compute the value of outBoneAngle1 based on the sine and cosine of outBoneAngle2
	float triAdjacent = boneLength1 + boneLength2*cosAngle2;
	float triOpposite = boneLength2*sinAngle2;

	// Note that it is safe to call Atan2(0,0) which will happen if targetX and
	// targetY are zero
	outBoneAngle1_1 = Math::Atan2(targetY*triAdjacent - targetX*triOpposite, targetX*triAdjacent + targetY*triOpposite);

	outBoneAngle1_2 = -outBoneAngle2_1;
	outBoneAngle2_2 = Math::Atan2(targetY*triAdjacent + targetX*triOpposite, targetX*triAdjacent - targetY*triOpposite);


	return foundValidSolution;
}


void IKSolver2D::CalculateWorldBone(List<Bone, NoCompare>& bones)
{
	// Start with the root bone.
	Bone& rootWorldBone = bones[0];
	rootWorldBone.WorldAngle = bones[0].Angle;
	rootWorldBone.WorldCosine = Math::Cos(rootWorldBone.WorldAngle);
	rootWorldBone.WorldSine = Math::Sin(rootWorldBone.WorldAngle);

	size_t count = bones.Count();
	FOR_EACH_SIZE_BEGIN_END(i, 1, count - 1)
	{
		Bone& prevWorldBone = bones[i - 1];
		Bone& curLocalBone = bones[i];

		//convert to parent space
		curLocalBone.X = prevWorldBone.X + prevWorldBone.WorldCosine*curLocalBone.X - prevWorldBone.WorldSine*curLocalBone.Y;
		curLocalBone.Y = prevWorldBone.Y + prevWorldBone.WorldSine*curLocalBone.X + prevWorldBone.WorldCosine*curLocalBone.Y;
		curLocalBone.WorldAngle = prevWorldBone.WorldAngle + curLocalBone.Angle;
		curLocalBone.WorldCosine = Math::Cos(curLocalBone.WorldAngle);
		curLocalBone.WorldSine = Math::Sin(curLocalBone.WorldAngle);

	}
}


IKSolver2D::CCDResult IKSolver2D::CyclicCoordinateDescent(List<Bone, NoCompare>& bones, float targetX, float targetY, float arrivalDistance)
{
	// Set an epsilon value to prevent division by small numbers.
	const float epsilon = 0.0001f;

	// Set max arc length a bone can move the end effector an be considered no motion
	// so that we can detect a failure state.
	const float trivialArcLength = 0.00001f;

	size_t numBones = bones.Count();

	float arrivalDistSqr = arrivalDistance*arrivalDistance;

	//===
	// Track the end effector position (the final bone)
	float endX = bones[numBones - 1].WorldX;
	float endY = bones[numBones - 1].WorldY;

	//===
	// Perform CCD on the bones by optimizing each bone in a loop 
	// from the final bone to the root bone
	bool modifiedBones = false;
	for (int boneIdx = (int)numBones - 2; boneIdx >= 0; --boneIdx)
	{
		// Get the vector from the current bone to the end effector position.
		float curToEndX = endX - bones[boneIdx].WorldX;
		float curToEndY = endY - bones[boneIdx].WorldY;
		float curToEndMag = Math::Hypot(curToEndX, curToEndY);

		// Get the vector from the current bone to the target position.
		float curToTargetX = targetX - bones[boneIdx].WorldX;
		float curToTargetY = targetY - bones[boneIdx].WorldY;
		float curToTargetMag = Math::Hypot(curToTargetX, curToTargetY);

		// Get rotation to place the end effector on the line from the current
		// joint position to the target position.
		float cosRotAng;
		float sinRotAng;
		float endTargetMag = (curToEndMag*curToTargetMag);
		if (endTargetMag <= epsilon)
		{
			cosRotAng = 1;
			sinRotAng = 0;
		}
		else
		{
			cosRotAng = (curToEndX*curToTargetX + curToEndY*curToTargetY) / endTargetMag;
			sinRotAng = (curToEndX*curToTargetY - curToEndY*curToTargetX) / endTargetMag;
		}

		// Clamp the cosine into range when computing the angle (might be out of range
		// due to floating point error).

		float rotAng = Math::Acos(Math::Clamp(cosRotAng,-1.f,1.f));
		if (sinRotAng < 0.0)
			rotAng = -rotAng;

		// Rotate the end effector position.
		endX = bones[boneIdx].WorldX + cosRotAng*curToEndX - sinRotAng*curToEndY;
		endY = bones[boneIdx].WorldY + sinRotAng*curToEndX + cosRotAng*curToEndY;

		// Rotate the current bone in local space (this value is output to the user)
		bones[boneIdx].WorldAngle = Math::WrapToPI(bones[boneIdx].WorldAngle + rotAng);

		// Check for termination
		float endToTargetX = (targetX - endX);
		float endToTargetY = (targetY - endY);
		if (endToTargetX*endToTargetX + endToTargetY*endToTargetY <= arrivalDistSqr)
		{
			// We found a valid solution.
			return CCDResult::Success;
		}

		// Track if the arc length that we moved the end effector was
		// a nontrivial distance.
		if (!modifiedBones && Math::Abs(rotAng)*curToEndMag > trivialArcLength)
		{
			modifiedBones = true;
		}
	}

	// We failed to find a valid solution during this iteration.
	if (modifiedBones)
		return CCDResult::Processing;
	else
		return CCDResult::Failure;
}

MEDUSA_END;