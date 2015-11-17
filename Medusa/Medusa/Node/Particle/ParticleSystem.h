// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Node/INode.h"
#include "Core/Collection/Dictionary.h"
#include "Core/Pattern/Nullable.h"
#include "Core/Geometry/Cube.h"
#include "Core/Pattern/VaryValue.h"

MEDUSA_BEGIN;


class ParticleSystem :public INode
{
public:
	ParticleSystem(StringRef name=StringRef::Empty);
	virtual ~ParticleSystem(void);
	virtual bool Initialize();
protected:
	Dictionary<HeapString,IParticleEmitter*> mEmitters;

	
	Nullable<BoundingBox> mFixedBoundingBox;
	
	VaryValue<float> mDelay;	

	Nullable<BoundingBox> mOcclusionBox;	

	bool mBillingBoard;	//make Z toward camera
	float mPreWarm;		
	float mSecondsBeforeInactive;	
	Nullable<float> mFixedUpdateTime;

};

MEDUSA_END;
