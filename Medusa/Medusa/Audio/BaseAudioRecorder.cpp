// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#ifdef MEDUSA_AL
#include "BaseAudioRecorder.h"
#include "Audio/Device/AudioDevice.h"
#include "Core/Log/Log.h"
MEDUSA_BEGIN;


BaseAudioRecorder::BaseAudioRecorder(uint sampleRate/* = 44100*/) :
	mSampleRate(sampleRate),
	mProcessingIntervalMilliseconds(100),
	mIsCapturing(false)
{

	mThread.SetCallback(Bind(&BaseAudioRecorder::OnRecord, this));
	mDeviceName = AudioDevice::Instance().GetDefaultCaptureDevice();
}


BaseAudioRecorder::~BaseAudioRecorder()
{
}


bool BaseAudioRecorder::Start()
{
	if (AudioDevice::Instance().IsCaptureSupport())
	{
		Log::Error("Capture is not support on current device!");
		return false;
	}

	if (AudioDevice::Instance().IsCaptureOpen())
	{
		Log::Error("Trying to start audio capture, but another capture is already running");
		return false;
	}

	//capture one second buffer 16 bits mono samples
	if (!AudioDevice::Instance().OpenCapureDevice(mDeviceName, mSampleRate, AudioFormat::Mono16, mSampleRate))
	{
		Log::FormatError("Failed to open the audio capture device with the name: {}", mDeviceName.c_str());
		return false;
	}

	mTempSamples.Clear();

	// Notify derived class
	if (OnStart())
	{
		AudioDevice::Instance().StartCapture();
		// Start the capture in a new thread, to avoid blocking the main thread
		mIsCapturing = true;
		mThread.Start();
		return true;
	}

	return false;
}


void BaseAudioRecorder::Stop()
{
	// Stop the capturing thread
	mIsCapturing = false;
	mThread.Join();

	// Notify derived class
	OnStop();
}

void BaseAudioRecorder::ProcessSamples()
{
	int samplesAvailable = AudioDevice::Instance().GetContextInteger(AudioContextIntegerName::CaptureSampleCount);
	if (samplesAvailable > 0)
	{
		// Get the recorded samples
		mTempSamples.ReserveSize(samplesAvailable);
		AudioDevice::Instance().GetCapureSamples(samplesAvailable, mTempSamples.MutableItems());
		mTempSamples.ForceSetCount(samplesAvailable);
		MemoryShortData sampleData = MemoryShortData::FromStatic(mTempSamples.Items(), mTempSamples.Count());
		// Forward them to the derived class
		if (!OnProcessSamples(sampleData))
		{
			// The user wants to stop the capture
			mIsCapturing = false;
		}
	}
}


void BaseAudioRecorder::OnRecord(Thread& thread)
{
	while (mIsCapturing)
	{
		ProcessSamples();
		// Don't bother the CPU while waiting for more captured data
		Thread::Sleep(mProcessingIntervalMilliseconds);
	}

	AudioDevice::Instance().StopCapture();

	// Get the samples left in the buffer
	ProcessSamples();

	AudioDevice::Instance().CloseCaptureDevice();

}

MEDUSA_END;
#endif