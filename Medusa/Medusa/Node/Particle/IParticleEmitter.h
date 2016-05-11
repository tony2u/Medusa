// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "Core/Collection/List.h"
#include "Core/Pattern/VaryValue.h"
#include "Geometry/Color4.h"
#include "Core/Pattern/VaryValue.h"
#include "Node/INode.h"
#include "Geometry/Point3.h"

MEDUSA_BEGIN;


class IParticleEmitter:public INode
{
public:
	IParticleEmitter(StringRef name=StringRef::Empty);
	virtual ~IParticleEmitter(void);
	virtual bool Initialize();
protected:
	List<IParticle*> mParticles;

	VaryValue<Color4F> mStartColor;	
	int mStartCount;	//if ==0, use calcualted max count


	bool mKillOnDeactivate;
	bool mKillOnCompleted;

	
	VaryValue<float> mDelay;	//wait after active
	
	VaryValue<float> mDuration;
	uint mLoopCount;	//count to become inactive, if =0, will run forever

	//UV


	//Burst
	float mBurstList;	//Burst means to emit enough items in given time

	
	float mRate;

	
	VaryValue<float> mAcceleration;

	//Attractor Modules //attract items to line or positions

	//Attractor Line
	Point3F mBeginPoint;
	Point3F mEndPoint;
	float mRange;	
	float mStrength;	

	//Attractor Particle
};


/************************************************************************/
/* 
AnimTrail TypeData
Beam TypeData
Mesh TypeData
PhysX Mesh TypeData(PhysX)
PhysX Sprite TypeData
Ribbon TypeData
*/
/************************************************************************/

MEDUSA_END;
