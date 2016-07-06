// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#ifdef MEDUSA_AL
#include "Audio/AudioTypes.h"
#include "Core/Pattern/ISharableWithName.h"
#include "Core/Pattern/Event.h"
#include "Core/Pattern/INonCopyable.h"
MEDUSA_BEGIN;

/************************************************************************/
/*
The number of sources you can create via alGenSources() has nothing to do with the number of sources allowed to simultaneously play.
I've successfully created up to 2048 sources on an iPad 4, just using a loop. That doesn't mean I can play 2048 sounds simultaneously.
So,my strategy is just simply create source and play it but keep watching it on each frame, if one source is end, delete it.
This strategy is ok but the weak point is that you cannot keep "my" source object more than limit. On the end, I decide to create AL source
in AL device, "my" source create the AL source only when it start to play
*/
/************************************************************************/

//TODO: add a call back on end
typedef Delegate<void(IAudioSource& sender,IEventArg& e)> AudioSourceDelegate;
typedef Event<void(IAudioSource& sender,IEventArg& e)> AudioSourceEvent;


class IAudioSource:public ISharableSingleThreadWithName
{
public:
	IAudioSource(const StringRef& name=StringRef::Empty);
	virtual ~IAudioSource();

public:
	bool IsLooping() const { return mIsLooping; }
	void SetIsLooping(bool val){mIsLooping=val;}

	bool IsRelative() const { return mIsRelative; }
	void SetIsRelative(bool val){mIsRelative=val;}

	float Pitch() const { return mPitch; }
	void SetPitch(float val){mPitch=val;}

	float Volume() const { return mVolume; }
	void SetVolume(float val){mVolume=val;}

	float MinVolume() const { return mMinVolume; }
	void SetMinVolume(float val){mMinVolume=val;}

	float MaxVolume() const { return mMaxVolume; }
	void SetMaxVolume(float val){mMaxVolume=val;}

	float MaxDistance() const { return mMaxDistance; }
	void SetMaxDistance(float val){mMaxDistance=val;}

	float RolloffFactor() const { return mRolloffFactor; }
	void SetRolloffFactor(float val){mRolloffFactor=val;}

	float ConeOuterAngle() const { return mConeOuterAngle; }
	void SetConeOuterAngle(float val){mConeOuterAngle=val;}

	float ConeInnerAngle() const { return mConeInnerAngle; }
	void SetConeInnerAngle(float val){mConeInnerAngle=val;}

	float ConeOuterVolume() const { return mConeOuterVolume; }
	void SetConeOuterVolume(float val){mConeOuterVolume=val;}

	float ReferenceDistance() const { return mReferenceDistance; }
	void SetReferenceDistance(float val){mReferenceDistance=val;}

	const Point3F& Position() const { return mPosition; }
	void SetPosition(const Point3F& val){mPosition=val;}

	const Vector3F& Velocity() const { return mVelocity; }
	void SetVelocity(const Vector3F& val){mVelocity=val;}

	const Vector3F& Direction() const { return mDirection; }
	void SetDirection(const Vector3F& val){mDirection=val;}

	AudioSourceType GetType()const;
	bool IsEnd()const;

	virtual AudioSourceState GetState()const;

	virtual uint GetSecondOffset()const;
	virtual uint GetSampleOffset()const;
	virtual uint GetByteOffset()const;

	virtual void SetSecondOffset(uint val);
	virtual void SetSampleOffset(uint val);
	virtual void SetByteOffset(uint val);
public:
	virtual void Play();
	virtual void Pause();
	virtual void Resume();

	virtual void Stop();
	virtual void Rewind();

	uint Source() const { return mSource; }

public:
	AudioSourceEvent OnEnd;
	void FireEndEvent();
protected:
	virtual void OnSetup(){}
	virtual bool IsStream()const{return false;}
protected:
    uint mSource;
	bool mIsLooping;
	bool mIsRelative;
	
	float mPitch;
	float mVolume;
	float mMinVolume;
	float mMaxVolume;
	float mMaxDistance;
	float mRolloffFactor;
	float mConeOuterAngle;
	float mConeInnerAngle;
	float mConeOuterVolume;
	float mReferenceDistance;
	
	Point3F mPosition;
	Vector3F mVelocity;
	Vector3F mDirection;

	bool mIsEnd;
};


MEDUSA_END;
#endif