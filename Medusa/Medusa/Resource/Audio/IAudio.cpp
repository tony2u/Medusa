// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "Audio/Device/AudioDevice.h"
#include "IAudio.h"
MEDUSA_BEGIN;


IAudio::IAudio(const FileIdRef& fileId/*=FileId::Empty*/)
	:IResource(fileId)
{
}

IAudio::IAudio(const MemoryByteData& data, const FileIdRef& fileId /*= FileIdRef::Empty*/)
	: IResource(fileId),mData(data)
{

}

IAudio::IAudio(MemoryByteData&& data, const FileIdRef& fileId /*= FileIdRef::Empty*/)
	: IResource(fileId), mData(data)
{

}

IAudio::~IAudio()
{
	if (mBuffer != 0)
	{
		AudioDevice::Instance().DeleteBuffer(mBuffer);
		mBuffer = 0;
	}
}


void IAudio::GenerateBuffer()
{
	if (mBuffer == 0)
	{
		mBuffer = AudioDevice::Instance().GenBuffer();
	}
}

uint IAudio::GetDuration() const
{
	if (mSampleRate == 0 || mChannelCount == 0)
	{
		return 0;
	}
	return (uint)(mSampleCount / mSampleRate / mChannelCount);
}


bool IAudio::Upload()
{
	RETURN_TRUE_IF_TRUE(mIsUploaded);
	GenerateBuffer();
	AudioFormat format = AudioDevice::Instance().GetAudioFormat(mChannelCount, mBitsPerSample);
	AudioDevice::Instance().LoadBufferData(mBuffer, format, mData.Data(), (uint)mData.ByteSize(), mSampleRate);
	mIsUploaded = true;
	return true;
}

bool IAudio::Upload(const MemoryByteData& data)
{
	AudioFormat format = AudioDevice::Instance().GetAudioFormat(mChannelCount, mBitsPerSample);
	GenerateBuffer();
	AudioDevice::Instance().LoadBufferData(mBuffer, format, data.Data(), (uint)data.ByteSize(), mSampleRate);
	return true;
}

MEDUSA_END;