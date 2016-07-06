// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#ifdef MEDUSA_AL

#include "IAudioDevice.h"
#include "Core/Log/Log.h"

MEDUSA_BEGIN;

IAudioDevice::IAudioDevice(void)
{
}


IAudioDevice::~IAudioDevice(void)
{

}


bool IAudioDevice::Uninitialize()
{
	DeleteSources((uint)mSources.Count(), mSources.MutableItems());
	mSources.Clear();
	return true;
}

bool IAudioDevice::IsSuccess() const
{
#ifdef MEDUSA_RENDER_ASSERT_ENABLED
	return GetError() == AudioErrorCode::Success;
#else
	return true;
#endif
}


bool IAudioDevice::AssertSuccess() const
{
#ifdef MEDUSA_AUDIO_ASSERT_ENABLED
	AudioErrorCode errorCode = GetError();
	switch (errorCode)
	{
		case AudioErrorCode::Success:
			return true;
			break;
		case AudioErrorCode::InvalidEnum:
			Log::AssertFailed("AL:Invalid Enum.");
			break;
		case AudioErrorCode::InvalidName:
			Log::AssertFailed("AL:Invalid Name.");
			break;
		case AudioErrorCode::InvalidValue:
			Log::AssertFailed("AL:Invalid Value.");
			break;
		case AudioErrorCode::InvalidOperation:
			Log::AssertFailed("AL:Invalid Operation.");
			break;
		case AudioErrorCode::OutOfMemory:
			Log::AssertFailed("AL:Out of memory");
			break;
	}
	return false;
#else
	return true;
#endif // _DEBUG
}

bool IAudioDevice::AssertContextSuccess() const
{
#ifdef MEDUSA_AUDIO_ASSERT_ENABLED
	AudioContextErrorCode errorCode = GetContextError();
	switch (errorCode)
	{
		case AudioContextErrorCode::Success:
			return true;
			break;
		case AudioContextErrorCode::InvalidEnum:
			Log::AssertFailed("AL:Invalid Enum.");
			break;
		case AudioContextErrorCode::InvalidDevice:
			Log::AssertFailed("AL:Invalid Device.");
			break;
		case AudioContextErrorCode::InvalidValue:
			Log::AssertFailed("AL:Invalid Value.");
			break;
		case AudioContextErrorCode::InvalidContext:
			Log::AssertFailed("AL:Invalid Context.");
			break;
		case AudioContextErrorCode::OutOfMemory:
			Log::AssertFailed("AL:Out of memory");
			break;
	}
	return false;
#else
	return true;
#endif // _DEBUG
}

bool IAudioDevice::IsContextSuccess() const
{
#ifdef MEDUSA_AUDIO_ASSERT_ENABLED
	return GetContextError() == AudioContextErrorCode::Success;
#else
	return true;
#endif
}


#pragma region Values

int IAudioDevice::GetInteger(AudioIntegerName name) const
{
#ifdef MEDUSA_AUDIO_STATE_CACHE_ENABLED

	switch (name)
	{
		case AudioIntegerName::DistanceModel:
			return (int)mDistanceModel;
		default:
			Log::AssertFailedFormat("Invalid AudioIntegerName:{}", name);
			break;
	}

	return 0;
#else
	int outVal = 0;
	TryGetInteger(name, outVal);
	return outVal;
#endif
}


void IAudioDevice::GetIntegerArray(AudioIntegerArrayName name, int* params) const
{
#ifdef MEDUSA_AUDIO_STATE_CACHE_ENABLED

	switch (name)
	{
		case AudioIntegerArrayName::None:
			break;
		default:
			Log::AssertFailedFormat("Invalid AudioIntegerName:{}", name);
			break;
	}

#else
	TryGetIntegerArray(name, params);
#endif
}

bool IAudioDevice::GetBoolean(AudioBooleanName name) const
{
#ifdef MEDUSA_AUDIO_STATE_CACHE_ENABLED

	return false;
#else
	bool outVal;
	TryGetBoolean(name, outVal);
	return outVal;
#endif

}

void IAudioDevice::GetBooleanArray(AudioBooleanArrayName name, bool* params) const
{
#ifdef MEDUSA_AUDIO_STATE_CACHE_ENABLED


#else
	TryGetBooleanArray(name, params);
#endif

}

float IAudioDevice::GetFloat(AudioFloatName name) const
{
#ifdef MEDUSA_AUDIO_STATE_CACHE_ENABLED
	switch (name)
	{
		case AudioFloatName::DopplerFactor:return mDopplerFactor;
		case AudioFloatName::SpeedOfSound:return mSpeedOfSound;
		default:
			Log::AssertFailedFormat("Invalid AudioFloatName:{}", (int)name);
			break;
	}

	return 0.f;
#else
	float outVal = 0.f;
	TryGetFloat(name, outVal);
	return outVal;
#endif


}

void IAudioDevice::GetFloatArray(AudioFloatArrayName name, float* params) const
{
#ifdef MEDUSA_AUDIO_STATE_CACHE_ENABLED

	AssertSuccess();
#else
	TryGetFloatArray(name, params);
#endif
}


StringRef IAudioDevice::GetString(AudioStringName name)const
{
#ifdef MEDUSA_AUDIO_STATE_CACHE_ENABLED
	switch (name)
	{
		case AudioStringName::Vendor:return mVendor;
		case AudioStringName::Renderer:return mRenderer;
		case AudioStringName::Version:return mVersion;
		case AudioStringName::Extensions:return mExtensions;
		default:
			Log::AssertFailedFormat("Invalid AudioStringName:{}", name);
			break;
	}

	return StringRef::Empty;
#else
	StringRef outVal;
	TryGetString(name, outVal);
	return outVal;
#endif


}


#pragma endregion Values



uint IAudioDevice::GenBuffer() const
{
	uint result;
	GenBuffers(1, &result);
	AssertSuccess();
	return result;
}

void IAudioDevice::DeleteBuffer(uint bufferObject) const
{
	DeleteBuffers(1, &bufferObject);
}

uint IAudioDevice::GenSource() const
{
	uint result;
	GenSources(1, &result);
	AssertSuccess();
	return result;
}

void IAudioDevice::DeleteSource(uint bufferObject) const
{
	uint result;
	DeleteSources(1, &result);
	AssertSuccess();
}

void IAudioDevice::PlaySource(uint sourceObject) const
{
	PlaySources(1, &sourceObject);
}

void IAudioDevice::PauseSource(uint sourceObject) const
{
	PauseSources(1, &sourceObject);
}

void IAudioDevice::RewindSource(uint sourceObject) const
{
	RewindSources(1, &sourceObject);
}


void IAudioDevice::StopSource(uint sourceObject) const
{
	StopSources(1, &sourceObject);
}

void IAudioDevice::QueueSourceBuffer(uint sourceObject, uint bufferObject) const
{
	QueueSourceBuffers(sourceObject, 1, &bufferObject);

}

uint IAudioDevice::UnqueueSourceBuffer(uint sourceObject) const
{
	uint bufferObject;
	UnqueueSourceBuffers(sourceObject, 1, &bufferObject);
	return bufferObject;
}


void IAudioDevice::SetSourceBuffer(uint sourceObject, uint bufferObject) const
{
	SetSourceIntegerProperty(sourceObject, AudioSourceIntegerProperty::Buffer, bufferObject);
}

AudioSourceState IAudioDevice::GetSourceState(uint sourceObject) const
{
	return AudioSourceState(GetSourceIntegerProperty(sourceObject, AudioSourceIntegerProperty::SourceState));
}


int IAudioDevice::GetContextInteger(AudioContextIntegerName name) const
{
#ifdef MEDUSA_AUDIO_STATE_CACHE_ENABLED

	switch (name)
	{
		case AudioContextIntegerName::MajorVersion:return (int)mContextMajorVersion;
		case AudioContextIntegerName::MinorVersion:return (int)mContextMinorVersion;
		case AudioContextIntegerName::AttributeSize:return (int)mContextAttributeSize;
		case AudioContextIntegerName::MonoSourceCount:return (int)mContextMonoSourceCount;
		case AudioContextIntegerName::StereoSourceCount:return (int)mContextStereoSourceCount;
		case AudioContextIntegerName::CaptureSampleCount:
		{
			int outVal = 0;
			TryGetContextInteger(name, outVal);
			return outVal;
		}
		default:
			Log::AssertFailedFormat("Invalid AudioContextIntegerName:{}", name);
			break;
	}

	return 0;
#else
	int outVal = 0;
	TryGetContextInteger(name, outVal);
	return outVal;
#endif
}

void IAudioDevice::GetContextIntegerArray(AudioContextIntegerArrayName name, int* params, size_t size) const
{
#ifdef MEDUSA_AUDIO_STATE_CACHE_ENABLED

	switch (name)
	{
		case AudioContextIntegerArrayName::Attributes:
			Memory::SafeCopy(params, size, mContextAttributes.Items(), mContextAttributeSize);
			break;
		default:
			Log::AssertFailedFormat("Invalid AudioContextIntegerArrayName:{}", name);
			break;
	}
#else
	int outVal = 0;
	TryGetContextIntegerArray(name, params, size);
	return outVal;
#endif
}

StringRef IAudioDevice::GetContextString(AudioContextStringName name) const
{
#ifdef MEDUSA_AUDIO_STATE_CACHE_ENABLED
	switch (name)
	{
		case AudioContextStringName::DefaultDeviceName:return mDefaultDeviceName;
		case AudioContextStringName::DefaultCaptureDeviceName:return mDefaultCaptureDeviceName;
		case AudioContextStringName::AllDeviceNames:return mAllDeviceNames;
		case AudioContextStringName::AllCaptureDeviceNames:return mAllCaptureDeviceNames;
		case AudioContextStringName::Extensions:return mContextExtensions;
		default:
			Log::AssertFailedFormat("Invalid AudioContextStringName:{}", name);
			break;
	}

	return StringRef::Empty;
#else
	StringRef outVal;
	TryGetContextString(name, outVal);
	return outVal;
#endif
}



List<StringRef> IAudioDevice::GetAllDevices()
{
	List<StringRef> result;
	StringRef allDevices = GetContextString(AudioContextStringName::AllDeviceNames);
	const char* str = allDevices.c_str();
	if (str)
	{
		while (*str != '\0')
		{
			result.Add(str);
			str += StdString::GetLength(str);
		}
	}

	return result;
}

StringRef IAudioDevice::GetDefaultDevice()
{
	return GetContextString(AudioContextStringName::DefaultDeviceName);
}

List<StringRef> IAudioDevice::GetAllCaptureDevices()
{
	List<StringRef> result;
	StringRef allDevices = GetContextString(AudioContextStringName::AllCaptureDeviceNames);
	const char* str = allDevices.c_str();
	if (str)
	{
		while (*str != '\0')
		{
			result.Add(str);
			str += StdString::GetLength(str);
		}
	}

	return result;
}

StringRef IAudioDevice::GetDefaultCaptureDevice()
{
	return GetContextString(AudioContextStringName::DefaultCaptureDeviceName);
}

void IAudioDevice::PrintAll()
{
	List<StringRef> allDevices = GetAllDevices();
	StringRef defaultDevice = GetDefaultDevice();

	List<StringRef> allCaptureDevices = GetAllCaptureDevices();
	StringRef defaultCaptureDevice = GetDefaultCaptureDevice();

	HeapString str("\nAllDevices:");
	for(auto i: allDevices)
	{
		str += i;
		str += "\t";
	}


	str += "\nDefaultDevice:";
	str += defaultDevice;

	str += "\nAllCaptureDevice:";
	for(auto i: allCaptureDevices)
	{
		str += i;
		str += "\t";
	}

	str += "\nDefaultCaptureDevice:";
	str += defaultCaptureDevice;

	str.AppendFormat("\nVendor:{}\n", mVendor.c_str());
	str.AppendFormat("Renderer:{}\n", mRenderer.c_str());
	str.AppendFormat("Version:{}\n", mVersion.c_str());
	str.AppendFormat("Extensions:{}\n", mExtensions.c_str());
	str.AppendFormat("ContextExtensions:{}\n", mContextExtensions.c_str());



	Log::Info(str);
}


MEDUSA_END;
#endif