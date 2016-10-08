// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "Geometry/Point2.h"
#include "Geometry/Point3.h"
#include "Geometry/Rotation3.h"



MEDUSA_BEGIN;

class PhysicsAlgorithm
{
public:
	static void SimulateProjectileDamping(Point3F start, Point3F velocity, float gravity, float damping, float timeStep, float minZ, Point3F& WorldLocation, float& timeElapsed, int& Steps);
	static void SimulateProjectileDampingStep(Point3F start, Point3F velocity, float gravity, float damping, float timeStep, Point3F& NextLocation, Point3F& NextVelocity);

	static bool SimluateInverseComputeProjectileDamping(Point3F start, Point3F target, Point3F parentVelocity, float velocity, float gravity, float damping, float timeStep, float rotatorStepDegree, 
		Rotation3F minRotator, Rotation3F maxRotator, Rotation3F& ResultRotator);

	

};

MEDUSA_END;
