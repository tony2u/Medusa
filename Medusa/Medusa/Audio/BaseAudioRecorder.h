// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "Core/Collection/List.h"
#include "Core/Threading/Thread.h"
#include "Core/Threading/ScopedLock.h"
#include "Core/String/HeapString.h"

MEDUSA_BEGIN;
class  BaseAudioRecorder
{
public:
	BaseAudioRecorder(uint sampleRate=44100);
	virtual ~BaseAudioRecorder();
	bool Start();
	void Stop();
	uint SampleRate() const { return mSampleRate; }
	void SetSampleRate(uint val) { mSampleRate = val; }

	uint ProcessingIntervalMilliseconds() const { return mProcessingIntervalMilliseconds; }
	void SetProcessingIntervalMilliseconds(uint val) { mProcessingIntervalMilliseconds = val; }
protected :
	virtual bool OnStart(){return true;}
	virtual bool OnProcessSamples(const MemoryShortData& sampleData) = 0;
	virtual void OnStop(){}
private :
	void OnRecord(Thread& thread);
	void ProcessSamples();
protected:

	Thread             mThread;            
	List<short> mTempSamples;            
	uint       mSampleRate;         
	uint           mProcessingIntervalMilliseconds;
	bool               mIsCapturing;       
	HeapString mDeviceName;         
};

MEDUSA_END;