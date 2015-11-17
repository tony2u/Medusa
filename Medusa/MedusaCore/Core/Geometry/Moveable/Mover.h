// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Geometry/Point2.h"


MEDUSA_BEGIN;

class Mover
{
public:
	Mover();
	~Mover(void);

	void Update(float dt);
	void ApplyForce(const Point2F& force);
	void ApplyGravity(const Point2F& gravity);

	Point2F CalculateFriction(float frictionMag, const Point2F& gravity);	
	Point2F CalculateDrag(float dragMag);	
	Point2F CalculateAttract(const Mover& other, float g, float minDistanceSquared = 1.f);
	Point2F CalculateSpring(const Point2F& startPos, float k);	
	Point2F CalcualteTurnForce(const Point2F& targetVelocity);	
public:
	float Mass() const { return mMass; }
	void SetMass(float val) { mMass = val; }

	const Point2F& Position() const { return mPosition; }
	void SetPosition(const Point2F& val) { mPosition = val; }
	float X()const { return mPosition.X; }
	float Y()const { return mPosition.Y; }
	void SetX(float val) { mPosition.X = val; }
	void SetY(float val) { mPosition.Y = val; }

	const Point2F& Velocity() const { return mVelocity; }
	void SetVelocity(const Point2F& val) { mVelocity = val; }

	const Point2F& Accelerate() const { return mAccelerate; }
	void SetAccelerate(const Point2F& val) { mAccelerate = val; }

	float Rotation() const { return mRotation; }
	void SetRotation(float val) { mRotation = val; }
protected:
	Point2F mPosition;
	Point2F mVelocity;
	Point2F mAccelerate;
	float mMass;

	float mRotation;
	float mRotationVelocity;
	float mRotationAccelerate;

};


MEDUSA_END;
