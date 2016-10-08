// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "PhysicsAlgorithm.h"
#include "Core/Math/Math.h"
#include "Lib/Common/Box2D/Box2D.h"

MEDUSA_BEGIN;

/*
m: mass
v0: initial velocity
a: angle
t: time
g: gravity

Projectile formula:
x=v0*cosa*t
y=v0*sina*t-g*t^2*0.5
t=2*v0*sina/g
d=v0^2*sin2a/g


Projectile with damping formula:
F=-k*v


x=(m/k)(v0*cosa)(1-e^(-k*t/m))
y=(m/k)(v0*sina+mg/k)(1-e^(-k*t/m))-m*g*t/k

t~=(2*m*v0*sina)/(k*v0*sina+m*g)
distance:
d~=(m^2*g*v0^2*sin2a)/(k*v0*sina+m*g)^2

*/

void PhysicsAlgorithm::SimulateProjectileDamping(Point3F start, Point3F velocity, float gravity, float damping, float timeStep, float minZ, Point3F& WorldLocation, float& timeElapsed, int& Steps)
{
	Point3F current = start;
	Point3F next = start;
	for (int i = 0;; ++i)
	{
		current = next;
		SimulateProjectileDampingStep(current, velocity, gravity, damping, timeStep, next, velocity);
		if (next.Z < minZ)
		{
			WorldLocation = current;
			WorldLocation.Z = minZ;
			Steps = i + 1;
			timeElapsed = Steps*timeStep;
			break;
		}
	}
}


void PhysicsAlgorithm::SimulateProjectileDampingStep(Point3F start, Point3F velocity, float gravity, float damping, float timeStep, Point3F& NextLocation, Point3F& NextVelocity)
{
	NextLocation = start + velocity*timeStep;

	NextVelocity = velocity;
	Point3F dampingVelocity = NextVelocity*damping*timeStep;
	NextVelocity -= dampingVelocity;
	NextVelocity.Z -= gravity*timeStep;
}


bool PhysicsAlgorithm::SimluateInverseComputeProjectileDamping(Point3F start, Point3F target, Point3F parentVelocity, float velocity, float gravity, float damping, float timeStep, float rotatorStepDegree, Rotation3F minRotator, Rotation3F maxRotator, Rotation3F& ResultRotator)
{
	return false;
}

MEDUSA_END;


