// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Audio/IAudioSource.h"
#include "Core/Collection/List.h"
#include "Core/Threading/Thread.h"
#include "Core/Memory/MemoryData.h"

MEDUSA_BEGIN;

class StreamAudioSource:public IAudioSource
{
public:
	StreamAudioSource(const StringRef& name=StringRef::Empty);
	virtual ~StreamAudioSource();
public:
	bool Initialize(uint channelCount,uintp samplerRate,uint bufferCount=3);
public:
	virtual AudioSourceState GetState()const;

	virtual uint GetSecondOffset()const;
	virtual uint GetSampleOffset()const;
	virtual uint GetByteOffset()const;

	virtual void SetSecondOffset(uint val);
	virtual void SetSampleOffset(uint val);
	virtual void SetByteOffset(uint val);

	virtual void Play();
	virtual void Pause();
	virtual void Resume();

	virtual void Stop();
	virtual void Rewind();
protected:
	virtual bool IsStream()const{return true;}

	virtual void OnSeek(uint secondOffset) = 0;
	virtual bool OnFetchData(MemoryByteData& outData) = 0;
private:
	void OnStreamThread(Thread& thread);
	bool FillQueue();
	void ClearQueue();
	bool FillAndQueueBuffer(size_t i);

protected:
	uint mChannelCount;
	uint mSampleRate;

	List<IAudio*> mBuffers;
	size_t mEndBufferIndex;
	size_t mSamplesProcessedCount;

	Thread mThread;
	bool mIsStreaming;
	size_t mBufferCount;

};


MEDUSA_END;