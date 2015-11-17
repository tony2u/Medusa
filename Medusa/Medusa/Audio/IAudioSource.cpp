// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "Audio/Device/AudioDevice.h"
#include "IAudioSource.h"
#include "Core/Command/EventArg/IEventArg.h"

MEDUSA_BEGIN;

IAudioSource::IAudioSource(const StringRef& name/*=StringRef::Empty*/) :ISharableSingleThreadWithName(name)
{
	mIsEnd=false;

	mSource=0;
	mIsLooping=false;
	mIsRelative=false;

	mPitch=1.f;
	mVolume=1.f;
	mMinVolume=0.f;
	mMaxVolume=1.f;
	mMaxDistance=Math::FloatMaxValue;
	mRolloffFactor=1.f;
	mConeOuterAngle=360.f;
	mConeInnerAngle=360.f;
	mConeOuterVolume=0.f;
	mReferenceDistance=1.f;

	mPosition=Point3F::Zero;
	mVelocity=Point3F::Zero;
	mDirection=Point3F::Zero;


}


IAudioSource::~IAudioSource()
{
	if (mSource!=0)
	{
		AudioDevice::Instance().StopSource(mSource);
		AudioDevice::Instance().RecycleSource(mSource);
		mSource=0;
	}
}


AudioSourceType IAudioSource::GetType() const
{
	if (mSource==0)
	{
		return AudioSourceType::Static;
	}

	return AudioSourceType(AudioDevice::Instance().GetSourceIntegerProperty(mSource,AudioSourceIntegerProperty::SourceType));
}

AudioSourceState IAudioSource::GetState() const
{
	if (mSource==0)
	{
		return AudioSourceState::Initial;
	}
	return AudioDevice::Instance().GetSourceState(mSource);
}

uint IAudioSource::GetSecondOffset() const
{
	RETURN_ZERO_IF_ZERO(mSource);
	return AudioDevice::Instance().GetSourceIntegerProperty(mSource,AudioSourceIntegerProperty::SecondOffset);
}

uint IAudioSource::GetSampleOffset() const
{
	RETURN_ZERO_IF_ZERO(mSource);
	return AudioDevice::Instance().GetSourceIntegerProperty(mSource,AudioSourceIntegerProperty::SampleOffset);
}

uint IAudioSource::GetByteOffset() const
{
	RETURN_ZERO_IF_ZERO(mSource);
	return AudioDevice::Instance().GetSourceIntegerProperty(mSource,AudioSourceIntegerProperty::ByteOffset);
}

void IAudioSource::SetSecondOffset(uint val) 
{
	RETURN_IF_ZERO(mSource);
	AudioDevice::Instance().SetSourceIntegerProperty(mSource,AudioSourceIntegerProperty::SecondOffset,val);
}

void IAudioSource::SetSampleOffset(uint val) 
{
	RETURN_IF_ZERO(mSource);

	AudioDevice::Instance().SetSourceIntegerProperty(mSource,AudioSourceIntegerProperty::SampleOffset,val);
}

void IAudioSource::SetByteOffset(uint val) 
{
	RETURN_IF_ZERO(mSource);

	AudioDevice::Instance().SetSourceIntegerProperty(mSource,AudioSourceIntegerProperty::ByteOffset,val);
}

bool IAudioSource::IsEnd() const
{
	if (mSource==0)
	{
		return true;
	}

	AudioSourceState state=GetState();
	return state==AudioSourceState::Initial||state==AudioSourceState::Stopped;
}

void IAudioSource::Play()
{
	if (mSource==0)
	{
		mSource=AudioDevice::Instance().GetUnusedSource();

		/*mIsLooping=AudioDevice::Instance().GetSourceBooleanProperty(mSource,AudioSourceBooleanProperty::IsLooping);
		mIsRelative=AudioDevice::Instance().GetSourceBooleanProperty(mSource,AudioSourceBooleanProperty::IsRelative);
		mPitch=AudioDevice::Instance().GetSourceFloatProperty(mSource,AudioSourceFloatProperty::Pitch);
		mVolume=AudioDevice::Instance().GetSourceFloatProperty(mSource,AudioSourceFloatProperty::Gain);
		mMinVolume=AudioDevice::Instance().GetSourceFloatProperty(mSource,AudioSourceFloatProperty::MinGain);
		mMaxVolume=AudioDevice::Instance().GetSourceFloatProperty(mSource,AudioSourceFloatProperty::MaxGain);
		mMaxDistance=AudioDevice::Instance().GetSourceFloatProperty(mSource,AudioSourceFloatProperty::MaxDistance);
		mRolloffFactor=AudioDevice::Instance().GetSourceFloatProperty(mSource,AudioSourceFloatProperty::RolloffFactor);
		mConeOuterAngle=AudioDevice::Instance().GetSourceFloatProperty(mSource,AudioSourceFloatProperty::ConneOuterAngle);
		mConeInnerAngle=AudioDevice::Instance().GetSourceFloatProperty(mSource,AudioSourceFloatProperty::ConeInnerAngle);
		mConeOuterVolume=AudioDevice::Instance().GetSourceFloatProperty(mSource,AudioSourceFloatProperty::ConeOuterGain);
		mReferenceDistance=AudioDevice::Instance().GetSourceFloatProperty(mSource,AudioSourceFloatProperty::ReferenceDistance);
		mPosition=AudioDevice::Instance().GetSourceFloatArrayProperty(mSource,AudioSourceFloatArrayProperty::Position);
		mVelocity=AudioDevice::Instance().GetSourceFloatArrayProperty(mSource,AudioSourceFloatArrayProperty::Velocity);
		mDirection=AudioDevice::Instance().GetSourceFloatArrayProperty(mSource,AudioSourceFloatArrayProperty::Direction);*/

		//set properties
		if (!IsStream())
		{
			AudioDevice::Instance().SetSourceBooleanProperty(mSource,AudioSourceBooleanProperty::IsLooping,mIsLooping);
		}

		AudioDevice::Instance().SetSourceBooleanProperty(mSource,AudioSourceBooleanProperty::IsRelative,mIsRelative);
		AudioDevice::Instance().SetSourceFloatProperty(mSource,AudioSourceFloatProperty::Pitch,mPitch);
		AudioDevice::Instance().SetSourceFloatProperty(mSource,AudioSourceFloatProperty::Gain,mVolume);
		AudioDevice::Instance().SetSourceFloatProperty(mSource,AudioSourceFloatProperty::MinGain,mMinVolume);
		AudioDevice::Instance().SetSourceFloatProperty(mSource,AudioSourceFloatProperty::MaxGain,mMaxVolume);
		AudioDevice::Instance().SetSourceFloatProperty(mSource,AudioSourceFloatProperty::MaxDistance,mMaxDistance);
		AudioDevice::Instance().SetSourceFloatProperty(mSource,AudioSourceFloatProperty::RolloffFactor,mRolloffFactor);
		AudioDevice::Instance().SetSourceFloatProperty(mSource,AudioSourceFloatProperty::ConneOuterAngle,mConeOuterAngle);
		AudioDevice::Instance().SetSourceFloatProperty(mSource,AudioSourceFloatProperty::ConeInnerAngle,mConeInnerAngle);
		AudioDevice::Instance().SetSourceFloatProperty(mSource,AudioSourceFloatProperty::ConeOuterGain,mConeOuterVolume);
		AudioDevice::Instance().SetSourceFloatProperty(mSource,AudioSourceFloatProperty::ReferenceDistance,mReferenceDistance);
		AudioDevice::Instance().SetSourceFloatArrayProperty(mSource,AudioSourceFloatArrayProperty::Position,mPosition);
		AudioDevice::Instance().SetSourceFloatArrayProperty(mSource,AudioSourceFloatArrayProperty::Velocity,mVelocity);
		AudioDevice::Instance().SetSourceFloatArrayProperty(mSource,AudioSourceFloatArrayProperty::Direction,mDirection);


		OnSetup();
	}

	AudioDevice::Instance().PlaySource(mSource);

	mIsEnd=false;
}

void IAudioSource::Pause()
{
	RETURN_IF_ZERO(mSource);
	AudioDevice::Instance().PauseSource(mSource);
}


void IAudioSource::Resume()
{
	RETURN_IF_ZERO(mSource);
	if (GetState()==AudioSourceState::Paused)
	{
		AudioDevice::Instance().PlaySource(mSource);
	}
}

void IAudioSource::Stop()
{
	RETURN_IF_ZERO(mSource);
	AudioDevice::Instance().StopSource(mSource);
	mSource=AudioDevice::Instance().RecycleSource(mSource);
	FireEndEvent();
}

void IAudioSource::Rewind()
{
	RETURN_IF_ZERO(mSource);
	AudioDevice::Instance().RewindSource(mSource);
}

void IAudioSource::FireEndEvent()
{
	if (!mIsEnd)
	{
		IEventArg e=IEventArg::Empty;
		OnEnd(*this,e);
		mIsEnd=true;
	}
}




MEDUSA_END;
