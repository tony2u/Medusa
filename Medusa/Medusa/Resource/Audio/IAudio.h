// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#ifdef MEDUSA_AL
#include "Resource/IResource.h"
#include "Audio/AudioTypes.h"
MEDUSA_BEGIN;

/// Here is a complete list of all the supported audio formats:
/// ogg, wav

class IAudio :public IResource
{
public:
	IAudio(const FileIdRef& fileId = FileIdRef::Empty);
	IAudio(const MemoryData& data,const FileIdRef& fileId = FileIdRef::Empty);
	IAudio(MemoryData&& data, const FileIdRef& fileId = FileIdRef::Empty);

	virtual ~IAudio();
	virtual ResourceType Type()const { return ResourceType::Audio; }
	static ResourceType ClassGetResourceType() { return ResourceType::Audio; }
	virtual AudioFileType AudioType()const = 0;

	uint Buffer() const { return mBuffer; }

	const MemoryData& Data() const { return mData; }
	void SetData(const MemoryData& val) { mData = val; }
	void SetData(MemoryData&& val) { mData = std::move(val); }


	uintp SampleCount() const { return mSampleCount; }
	void SetSampleCount(uintp val) { mSampleCount = val; }

	uint ChannelCount() const { return mChannelCount; }
	void SetChannelCount(uint val) { mChannelCount = val; }

	uint BitsPerSample() const { return mBitsPerSample; }
	void SetBitsPerSample(uint val) { mBitsPerSample = val; }

	uintp SampleRate() const { return mSampleRate; }
	void SetSampleRate(uintp val) { mSampleRate = val; }

	bool Seekable() const { return mSeekable; }
	void SetSeekable(bool val) { mSeekable = val; }

	uint GetDuration()const;

	bool IsUploaded() const { return mIsUploaded; }
	bool Upload();
	bool Upload(const MemoryData& data);
protected:
	void GenerateBuffer();
private:
	uint mBuffer = 0;
	bool mIsUploaded = false;
	MemoryData mData;
	
	uintp mSampleCount = 0;	//total sample count
	uint mChannelCount = 0;	//how many channel per frame
	uintp mSampleRate = 0;	//how many sample per second
	uint mBitsPerSample = 0;
	bool mSeekable = true;
	
};



MEDUSA_END;
#endif