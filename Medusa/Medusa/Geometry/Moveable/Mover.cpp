// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "Mover.h"

MEDUSA_BEGIN;

Mover::Mover()
	:mPosition(Point2F::Zero),
	mVelocity(Point2F::Zero),
	mAccelerate(Point2F::Zero),
	mMass(1.f),
	mRotation(0.f),
	mRotationVelocity(0.f),
	mRotationAccelerate(0.f)
{

}

Mover::~Mover(void)
{

}

void Mover::Update(float dt)
{
	mVelocity += mAccelerate*dt;
	mPosition += mVelocity*dt;

	mRotationVelocity += mRotationAccelerate*dt;
	mRotation += mRotationVelocity;
}

void Mover::ApplyForce(const Point2F& force)
{
	mAccelerate += force / mMass;
}


void Mover::ApplyGravity(const Point2F& gravity)
{
	ApplyForce(mMass*gravity);
}


Point2F Mover::CalculateFriction(float frictionMag, const Point2F& gravity)
{
	//Friction=-frictionMag*N*v
	//v==mVelocity.Normalize()

	Point2F friction = -mVelocity;
	friction.Normalize();

	friction *= frictionMag;
	friction *= mMass*gravity;
	return friction;
}

Point2F Mover::CalculateDrag(float dragMag)
{
	//F drag=-v*v*dragMag
	Point2F drag = -mVelocity;
	drag.Normalize();

	drag *= dragMag;
	drag *= mVelocity.LengthSquared();
	return drag;
}

Point2F Mover::CalculateAttract(const Mover& other, float g, float minDistanceSquared/*=1.f*/)
{
	//F=G*m1*m2/(r*r)
	Point2F force = mPosition - other.mPosition;
	float distanceSquared =Math::Max(force.LengthSquared(),minDistanceSquared);

	force.Normalize();
	force *= g*mMass*other.mMass;
	force /= distanceSquared;
	return force;
}

Point2F Mover::CalculateSpring(const Point2F& startPos, float k)
{
	//F=-k*x
	//x=pos-startPos
	return (startPos - mPosition)*k;
}

Point2F Mover::CalcualteTurnForce(const Point2F& targetVelocity)
{
	return targetVelocity - mVelocity;
}

MEDUSA_END;