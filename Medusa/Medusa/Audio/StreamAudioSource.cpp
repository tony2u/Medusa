// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "StreamAudioSource.h"
#include "Audio/Device/AudioDevice.h"
#include "Resource/Audio/PcmAudio.h"
MEDUSA_BEGIN;

StreamAudioSource::StreamAudioSource(const StringRef& name/*=StringRef::Empty*/):IAudioSource(name)
{
	mThread.SetCallback(Bind(&StreamAudioSource::OnStreamThread,this));
	mIsStreaming=false;
	mSamplesProcessedCount=0;
}


bool StreamAudioSource::Initialize(uint channelCount,uintp samplerRate,uint bufferCount/*=3*/)
{
	mBufferCount=bufferCount;
	SAFE_RELEASE_COLLECTION(mBuffers);
	FOR_EACH_SIZE(i,mBufferCount)
	{
		IAudio* buffer=new PcmAudio();
		buffer->SetChannelCount(channelCount);
		buffer->SetSampleRate(samplerRate);
		mBuffers.Add(buffer);
	}
	return true;
}


StreamAudioSource::~StreamAudioSource()
{
	Stop();
	SAFE_RELEASE_COLLECTION(mBuffers);
}

void StreamAudioSource::Play()
{
	if (mIsStreaming)
	{
		IAudioSource::Play();
		return;
	}

	OnSeek(0);
	mIsStreaming=true;
	mThread.Start();
}

void StreamAudioSource::Pause()
{
	IAudioSource::Pause();
}


void StreamAudioSource::Resume()
{
	IAudioSource::Resume();
}

void StreamAudioSource::Stop()
{
	mIsStreaming=false;
	mThread.Join();

	FireEndEvent();
}

void StreamAudioSource::Rewind()
{
	SetSecondOffset(0);
}


void StreamAudioSource::OnStreamThread(Thread& thread)
{
	IAudioSource::Play();

	bool isEnd=FillQueue();

	while(mIsStreaming)
	{
		AudioSourceState state=IAudioSource::GetState();
		if (state==AudioSourceState::Stopped)
		{
			// The stream has been interrupted!
			if (!isEnd)
			{
				//just continue
				IAudioSource::Play();
			}
			else
			{
				//end streaming
				mIsStreaming=false;
			}
		}

		int processedCount=(int)AudioDevice::Instance().GetSourceIntegerProperty(mSource,AudioSourceIntegerProperty::BufferProcessedCount);
		while(processedCount--)
		{
			uint buffer=AudioDevice::Instance().UnqueueSourceBuffer(mSource);

			size_t index=(size_t)-1;
			size_t bufferCount=mBuffers.Count();
			FOR_EACH_SIZE(i,bufferCount)
			{
				IAudio* audioBuffer=mBuffers[i];
				if (audioBuffer->Buffer()==buffer)
				{
					index=i;
					break;
				}
			}

			if (index==mEndBufferIndex)
			{
				// This was the last buffer: reset the sample count
				mSamplesProcessedCount=0;
				mEndBufferIndex=0;
			}
			else
			{
				uint bufferSize=AudioDevice::Instance().GetBufferProperty(buffer,AudioBufferProperty::DataSize);
				uint bitsPerSample=AudioDevice::Instance().GetBufferProperty(buffer,AudioBufferProperty::BitsPerSample);
				mSamplesProcessedCount+=bufferSize/(bitsPerSample/8);
			}

			if (!isEnd)
			{
				// Fill it and push it back into the playing queue
				if (FillAndQueueBuffer(index))
				{
					isEnd=true;	//just to allow fill one buffer in next loop
				}
			}
		}

		if(state!=AudioSourceState::Stopped)
		{
			Thread::Sleep(10);
		}
	}

	IAudioSource::Stop();
	ClearQueue();

	// Unqueue any buffer left in the queue
	//delete buffers
	AudioDevice::Instance().SetSourceBuffer(mSource,0);
	SAFE_RELEASE_COLLECTION(mBuffers);

}

bool StreamAudioSource::FillAndQueueBuffer(size_t i)
{
	bool isEnd=false;
	MemoryByteData outData;
	
	if (!OnFetchData(outData))
	{
		//reach the data end

		//mark the end buffer index
		mEndBufferIndex=i;

		if (mIsLooping)
		{
			//return to the beginning
			OnSeek(0);

			// If we previously had no data, try to fill the buffer once again
			if (!outData.IsValid())
			{
				return FillAndQueueBuffer(i);	
			}
		}
		else
		{
			isEnd=true;
		}
	}

	if (outData.IsValid())
	{
		IAudio* buffer=mBuffers[i];
		buffer->Upload(outData);
		AudioDevice::Instance().QueueSourceBuffer(mSource,buffer->Buffer());
	}

	return isEnd;
}

bool StreamAudioSource::FillQueue()
{
	FOR_EACH_SIZE(i,mBufferCount)
	{
		if (FillAndQueueBuffer(i))
		{
			return true;
		}
	}
	return false;
}


void StreamAudioSource::ClearQueue()
{
	uint bufferProcessedCount=AudioDevice::Instance().GetSourceIntegerProperty(mSource,AudioSourceIntegerProperty::BufferProcessedCount);
	uint* tempBuffer=new uint[bufferProcessedCount];
	AudioDevice::Instance().UnqueueSourceBuffers(mSource,bufferProcessedCount,tempBuffer);
	SAFE_DELETE_ARRAY(tempBuffer);
}


AudioSourceState StreamAudioSource::GetState() const
{
	AudioSourceState state=IAudioSource::GetState();
	if (state==AudioSourceState::Stopped&&mIsStreaming)
	{
		return AudioSourceState::Playing;
	}
	return state;
}


uint StreamAudioSource::GetSampleOffset() const
{
	uint sampleOffset=IAudioSource::GetSampleOffset();
	return sampleOffset+(uint)mSamplesProcessedCount;
}

uint StreamAudioSource::GetSecondOffset() const
{
	uint secondOffset=IAudioSource::GetSecondOffset();
	return secondOffset+(uint)mSamplesProcessedCount/mSampleRate/mChannelCount;
}

uint StreamAudioSource::GetByteOffset() const
{
	uint byteOffset=IAudioSource::GetByteOffset();
	return byteOffset+(uint)mSamplesProcessedCount*sizeof(short);
}

void StreamAudioSource::SetSecondOffset(uint val)
{
	Stop();

	OnSeek(val);

	//restart
	mSamplesProcessedCount=val*mSampleRate*mChannelCount;
	mIsStreaming=true;
	mThread.Start();
}

void StreamAudioSource::SetSampleOffset(uint val)
{
	Stop();

	OnSeek(val/mSampleRate/mChannelCount);

	//restart
	mSamplesProcessedCount=val;
	mIsStreaming=true;
	mThread.Start();
}

void StreamAudioSource::SetByteOffset(uint val)
{
	Stop();

	uint seconds=val/sizeof(short)/mChannelCount/mSampleRate;
	OnSeek(seconds);

	//restart
	mSamplesProcessedCount=val/sizeof(short)/mChannelCount;
	mIsStreaming=true;
	mThread.Start();
}

MEDUSA_END;
