// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#ifdef MEDUSA_AL
#include "Audio/StaticAudioSource.h"
#include "Resource/Audio/IAudio.h"
#include "Audio/Device/AudioDevice.h"

MEDUSA_BEGIN;

StaticAudioSource::StaticAudioSource(const StringRef& name/*=StringRef::Empty*/):IAudioSource(name)
{

}

StaticAudioSource::~StaticAudioSource()
{
	mBuffers.Clear();
}


Share<IAudio> StaticAudioSource::GetBuffer() const
{
	if (!mBuffers.IsEmpty())
	{
		return mBuffers[0];
	}
	return nullptr;
}

void StaticAudioSource::SetBuffer(const Share<IAudio>& val)
{
	if (mBuffers.IsEmpty())
	{
		AddBuffer(val);
	}
	else
	{
		mBuffers[0] = val;
	}
}

void StaticAudioSource::OnSetup()
{
	uint bufferProcessedCount=AudioDevice::Instance().GetSourceIntegerProperty(mSource,AudioSourceIntegerProperty::BufferProcessedCount);
	uint bufferQueuedCount=AudioDevice::Instance().GetSourceIntegerProperty(mSource,AudioSourceIntegerProperty::BufferQueuedCount);
	uint totalCount=bufferProcessedCount+bufferQueuedCount;
	if (totalCount>0)
	{
		uint* tempBuffer=new uint[totalCount];
		AudioDevice::Instance().UnqueueSourceBuffers(mSource,totalCount,tempBuffer);
		SAFE_DELETE_ARRAY(tempBuffer);
	}

	if (!mBuffers.IsEmpty()&&mBuffers.Count()>1)
	{
		for(auto buffer:mBuffers)
		{
			AudioDevice::Instance().QueueSourceBuffer(mSource,buffer->Buffer());
		}
	}
	else
	{
		auto buffer=GetBuffer();
		if (buffer!=nullptr)
		{
			AudioDevice::Instance().SetSourceIntegerProperty(mSource,AudioSourceIntegerProperty::Buffer,buffer->Buffer());
		}
		else
		{
			AudioDevice::Instance().SetSourceIntegerProperty(mSource,AudioSourceIntegerProperty::Buffer,0);
		}
	}

}

void StaticAudioSource::AddBuffer(const Share<IAudio>& val )
{
	mBuffers.Add(val);
}

MEDUSA_END;
#endif