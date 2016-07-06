// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#ifdef MEDUSA_AL


#ifdef MEDUSA_AL
#include "OpenALDevice.h"
#include "Core/Log/Log.h"

#ifdef MEDUSA_AUDIO_STATE_CACHE_ENABLED
#define AUDIO_ASSIGN_IF_SUCCESS(x,y) if(AssertSuccess()){x=y;}
#define AUDIO_RETURN_IF_EQUAL(x,y) RETURN_IF_EQUAL(x,y)
#else
#define AUDIO_ASSIGN_IF_SUCCESS(x,y) AssertSuccess();
#define AUDIO_RETURN_IF_EQUAL(x,y) 
#endif


MEDUSA_BEGIN;

OpenALDevice::OpenALDevice() :mDevice(nullptr), mCaptureDevice(nullptr)
{

}

OpenALDevice::~OpenALDevice()
{
}



bool OpenALDevice::Initialize()
{
	Dictionary<AudioContextAttribute, uint, SafeEnumHashCoder> attributes;
	StringRef outDeviceName = StringRef::Empty;
	TryGetContextString(AudioContextStringName::DefaultDeviceName, outDeviceName);
	return Initialize(attributes, outDeviceName);
}

bool OpenALDevice::Initialize(const Dictionary<AudioContextAttribute, uint, SafeEnumHashCoder>& attributes, const StringRef& deviceName/*=StringRef::Empty*/)
{
	mDevice = alcOpenDevice(nullptr);
	if (mDevice == nullptr)
	{
		AssertSuccess();
		Log::AssertNotNull(mDevice, "alcOpenDevice result");
		return false;
	}
	if (attributes.IsEmpty())
	{
		mContext = alcCreateContext(mDevice, nullptr);
	}
	else
	{
		List<int> data;
		for(auto i: attributes)
		{
			AudioContextAttribute attr = i.Key;
			data.Add((int)attr);
			data.Add(i.Value);
		}
		data.Add(0);	//terminated with 0
		mContext = alcCreateContext(mDevice, data.Items());
	}

	Log::AssertNotNull(mContext, "alcCreateContext result");
	alcMakeContextCurrent(mContext);

#ifdef MEDUSA_AUDIO_STATE_CACHE_ENABLED
	//init values
	TryGetInteger(AudioIntegerName::DistanceModel, (int&)mDistanceModel);
	//float values
	TryGetFloat(AudioFloatName::DopplerFactor, mDopplerFactor);
	TryGetFloat(AudioFloatName::SpeedOfSound, mSpeedOfSound);
	//string values
	TryGetString(AudioStringName::Vendor, mVendor);
	TryGetString(AudioStringName::Renderer, mRenderer);
	TryGetString(AudioStringName::Version, mVersion);
	TryGetString(AudioStringName::Extensions, mExtensions);
	//listener
	alGetListenerf(AL_GAIN, &mListenerVolume);
	alGetListenerfv(AL_POSITION, mListenerPosition.Buffer);
	alGetListenerfv(AL_VELOCITY, mListenerVelocity.Buffer);
	alGetListenerfv(AL_ORIENTATION, mListenerOrientaion.Forward.Buffer);

	//context string values
	TryGetContextString(AudioContextStringName::DefaultDeviceName, mDefaultDeviceName);
	TryGetContextString(AudioContextStringName::DefaultCaptureDeviceName, mDefaultCaptureDeviceName);
	TryGetContextString(AudioContextStringName::AllDeviceNames, mAllDeviceNames);
	TryGetContextString(AudioContextStringName::AllCaptureDeviceNames, mAllCaptureDeviceNames);
	TryGetContextString(AudioContextStringName::Extensions, mContextExtensions);

	//context int values
	TryGetContextInteger(AudioContextIntegerName::MajorVersion, mContextMajorVersion);
	TryGetContextInteger(AudioContextIntegerName::MinorVersion, mContextMinorVersion);
	TryGetContextInteger(AudioContextIntegerName::AttributeSize, mContextAttributeSize);
	TryGetContextInteger(AudioContextIntegerName::MonoSourceCount, mContextMonoSourceCount);
	TryGetContextInteger(AudioContextIntegerName::StereoSourceCount, mContextStereoSourceCount);

	//int array
	mContextAttributes.ReserveSize(mContextAttributeSize);
	TryGetContextIntegerArray(AudioContextIntegerArrayName::Attributes, mContextAttributes.MutableItems(), mContextAttributeSize*sizeof(int));
	mContextAttributes.ForceSetCount(mContextAttributeSize);
#endif

	mMaxSourceCount = GetContextInteger(AudioContextIntegerName::MonoSourceCount);
	if (mMaxSourceCount == 0)
	{
		mMaxSourceCount = MEDUSA_AUDIO_DEFAULT_MAX_SOURCE_COUNT;
	}
	return true;
}

bool OpenALDevice::Uninitialize()
{
	alcMakeContextCurrent(nullptr);
	if (mContext)
		alcDestroyContext(mContext);

	if (mDevice)
		alcCloseDevice(mDevice);

	if (mCaptureDevice)
	{
		alcCaptureCloseDevice(mCaptureDevice);
	}

	return true;
}


uint OpenALDevice::GetUnusedSource()
{
	//find in current sources
	size_t currentSourceCount = mSources.Count();
	if (currentSourceCount > 0)
	{
		FOR_EACH_SIZE(i, currentSourceCount)
		{
			uint source = mSources[i];
			AudioSourceState state = GetSourceState(source);
			if (state == AudioSourceState::Initial || state == AudioSourceState::Stopped)
			{
				return source;
			}
		}
	}

	//can we create a new source?
	if (mSources.Count() < mMaxSourceCount)
	{
		uint source = GenSource();
		mSources.Add(source);
		return source;
	}

	//find first non-looping source to stop it
	FOR_EACH_SIZE(i, currentSourceCount)
	{
		uint source = mSources[i];
		bool isLooping = GetSourceBooleanProperty(source, AudioSourceBooleanProperty::IsLooping);
		if (!isLooping)
		{
			Log::FormatInfo("Audio:Stop non-looping source to get a new one");
			StopSource(source);
			return source;
		}
	}

	//all source is looping
	uint source = mSources[0];
	StopSource(source);
	Log::FormatInfo("Audio:Stop looping source to get a new one");
	return source;

}


uint OpenALDevice::RecycleSource(uint source)
{
	if (mSources.Count() < mMaxSourceCount)
	{
		return source;
	}
	return 0;
}

AudioFormat OpenALDevice::GetAudioFormat(uint channelCount, uint bitsPerSample)const
{
	switch (channelCount)
	{
	case 1:return bitsPerSample == 8 ? AudioFormat::Mono8 : AudioFormat::Mono16;
	case 2:return bitsPerSample == 8 ? AudioFormat::Stereo8 : AudioFormat::Stereo16;
	case 4:return AudioFormat(alGetEnumValue("AL_FORMAT_QUAD16"));
	case 6:return AudioFormat(alGetEnumValue("AL_FORMAT_51CHN16"));
	case 7:return AudioFormat(alGetEnumValue("AL_FORMAT_61CHN16"));
	case 8:return AudioFormat(alGetEnumValue("AL_FORMAT_71CHN16"));
	default:
		Log::FormatError("Invalid channel count:{}", channelCount);
		break;
	}

	return AudioFormat::Stereo16;
}

AudioErrorCode OpenALDevice::GetError() const
{
	return AudioErrorCode(alGetError());
}

#pragma region Values

bool OpenALDevice::TryGetInteger(AudioIntegerName name, int& outVal) const
{
	alGetIntegerv((uint)name, &outVal);
	return IsSuccess();
}

bool OpenALDevice::TryGetIntegerArray(AudioIntegerArrayName name, int* params) const
{
	alGetIntegerv((uint)name, params);
	return IsSuccess();
}


bool OpenALDevice::TryGetBoolean(AudioBooleanName name, bool& outVal) const
{
	alGetBooleanv((uint)name, (ALboolean*)&outVal);
	return IsSuccess();

}

bool OpenALDevice::TryGetBooleanArray(AudioBooleanArrayName name, bool* params) const
{
	alGetBooleanv((uint)name, (ALboolean*)params);
	return IsSuccess();
}

bool OpenALDevice::TryGetFloat(AudioFloatName name, float& outVal) const
{
	alGetFloatv((uint)name, &outVal);
	return IsSuccess();
}


bool OpenALDevice::TryGetFloatArray(AudioFloatArrayName name, float* params) const
{
	alGetFloatv((uint)name, params);
	return IsSuccess();
}

bool OpenALDevice::TryGetString(AudioStringName name, StringRef& outVal) const
{
	const char* str = alGetString((uint)name);
	outVal.ForceSetBuffer((const char*)str);
	outVal.ForceUpdateLength();

	return IsSuccess();
}

#pragma endregion Values

#pragma region Buffer
bool OpenALDevice::IsBuffer(uint bufferObject) const
{
	bool isBuffer = alIsBuffer(bufferObject) == AL_TRUE;
	AssertSuccess();
	return isBuffer;
}

void OpenALDevice::GenBuffers(uint count, uint* outBuffers) const
{
	alGenBuffers(count, outBuffers);
	AssertSuccess();
}

void OpenALDevice::DeleteBuffers(uint count, uint* buffers) const
{
	alDeleteBuffers(count, buffers);
	AssertSuccess();
}

void OpenALDevice::LoadBufferData(uint bufferObject, AudioFormat format, const void* data, uintp size, uintp freq) const
{
	alBufferData(bufferObject, (uint)format, data, (ALsizei)size, (ALsizei)freq);
	AssertSuccess();
}

uint OpenALDevice::GetBufferProperty(uint bufferObject, AudioBufferProperty bufferProperty) const
{
	int outResult = 0;
	alGetBufferi(bufferObject, (uint)bufferProperty, &outResult);
	AssertSuccess();
	return (uint)outResult;
}


#pragma endregion Buffer

#pragma region Source

bool OpenALDevice::IsSource(uint sourceObject) const
{
	bool val = alIsSource(sourceObject) == AL_TRUE;
	AssertSuccess();
	return val;
}

void OpenALDevice::GenSources(uint count, uint* outSources) const
{
	alGenSources(count, outSources);
	AssertSuccess();
}

void OpenALDevice::DeleteSources(uint count, uint* sources) const
{
	alDeleteSources(count, sources);
	AssertSuccess();
}

bool OpenALDevice::GetSourceBooleanProperty(uint sourceObject, AudioSourceBooleanProperty sourceProperty) const
{
	uint outVal = 0;
	alGetSourcei(sourceObject, (uint)sourceProperty, (int*)&outVal);
	AssertSuccess();
	return outVal == AL_TRUE;
}

uint OpenALDevice::GetSourceIntegerProperty(uint sourceObject, AudioSourceIntegerProperty sourceProperty) const
{
	uint outVal = 0;
	alGetSourcei(sourceObject, (uint)sourceProperty, (int*)&outVal);
	AssertSuccess();
	return outVal;
}

float OpenALDevice::GetSourceFloatProperty(uint sourceObject, AudioSourceFloatProperty sourceProperty) const
{
	float outVal = 0.f;
	alGetSourcef(sourceObject, (uint)sourceProperty, &outVal);
	AssertSuccess();
	return outVal;
}

Point3F OpenALDevice::GetSourceFloatArrayProperty(uint sourceObject, AudioSourceFloatArrayProperty sourceProperty) const
{
	Point3F outVal;
	alGetSourcefv(sourceObject, (uint)sourceProperty, outVal.Buffer);
	AssertSuccess();
	return outVal;
}

void OpenALDevice::SetSourceBooleanProperty(uint sourceObject, AudioSourceBooleanProperty sourceProperty, bool val) const
{
	uint t = val ? AL_TRUE : AL_FALSE;
	alSourcei(sourceObject, (uint)sourceProperty, t);
	AssertSuccess();
}

void OpenALDevice::SetSourceIntegerProperty(uint sourceObject, AudioSourceIntegerProperty sourceProperty, uint val) const
{
	alSourcei(sourceObject, (uint)sourceProperty, val);
	AssertSuccess();
}

void OpenALDevice::SetSourceFloatProperty(uint sourceObject, AudioSourceFloatProperty sourceProperty, float val) const
{
	alSourcef(sourceObject, (uint)sourceProperty, val);
	AssertSuccess();
}

void OpenALDevice::SetSourceFloatArrayProperty(uint sourceObject, AudioSourceFloatArrayProperty sourceProperty, const Point3F& val) const
{
	alSourcefv(sourceObject, (uint)sourceProperty, val.Buffer);
	AssertSuccess();
}

void OpenALDevice::PlaySources(uint count, uint* sourceObjects) const
{
	alSourcePlayv(count, sourceObjects);
	AssertSuccess();
}

void OpenALDevice::PauseSources(uint count, uint* sourceObjects) const
{
	alSourcePausev(count, sourceObjects);
	AssertSuccess();
}

void OpenALDevice::RewindSources(uint count, uint* sourceObjects) const
{
	alSourceRewindv(count, sourceObjects);
	AssertSuccess();
}


void OpenALDevice::StopSources(uint count, uint* sourceObjects) const
{
	alSourceStopv(count, sourceObjects);
	AssertSuccess();
}

void OpenALDevice::QueueSourceBuffers(uint sourceObject, uint count, uint* bufferObjects) const
{
	alSourceQueueBuffers(sourceObject, count, bufferObjects);
	AssertSuccess();
}

void OpenALDevice::UnqueueSourceBuffers(uint sourceObject, uint count, uint* bufferObjects) const
{
	alSourceUnqueueBuffers(sourceObject, count, bufferObjects);
	AssertSuccess();
}


#pragma endregion Source

#pragma region AudioListener
float OpenALDevice::GetListenerVolume() const
{
#ifdef MEDUSA_AUDIO_ASSERT_ENABLED
	return mListenerVolume;
#else
	float outVal;
	alGetListenerf(AL_GAIN, &outVal);
	AssertSuccess();
	return outVal;
#endif
}

Point3F OpenALDevice::GetListenerPosition() const
{
#ifdef MEDUSA_AUDIO_ASSERT_ENABLED
	return mListenerPosition;
#else
	Point3F outVal;
	alGetListenerfv(AL_POSITION, outVal.Buffer);
	AssertSuccess();
	return outVal;
#endif
}

Point3F OpenALDevice::GetListenerVelocity() const
{
#ifdef MEDUSA_AUDIO_ASSERT_ENABLED
	return mListenerVelocity;
#else
	Point3F outVal;
	alGetListenerfv(AL_VELOCITY, outVal.Buffer);
	AssertSuccess();
	return outVal;
#endif
}

AudioListenerOrientation OpenALDevice::GetListenerOrientation() const
{
#ifdef MEDUSA_AUDIO_ASSERT_ENABLED
	return mListenerOrientaion;
#else
	AudioListenerOrientation outVal;
	alGetListenerfv(AL_ORIENTATION, outVal.Forward.Buffer);
	AssertSuccess();
	return outVal;
#endif
}

void OpenALDevice::SetListenerVolume(float val)
{
	AUDIO_RETURN_IF_EQUAL(mListenerVolume, val);
	alListenerf(AL_GAIN, val);
	AUDIO_ASSIGN_IF_SUCCESS(mListenerVolume, val);
}

void OpenALDevice::SetListenerPosition(const Point3F& val)
{
	AUDIO_RETURN_IF_EQUAL(mListenerPosition, val);
	alListener3f(AL_POSITION, mListenerPosition.X, mListenerPosition.Y, mListenerPosition.Z);
	AUDIO_ASSIGN_IF_SUCCESS(mListenerPosition, val);
}

void OpenALDevice::SetListenerVelocity(const Point3F& val)
{
	AUDIO_RETURN_IF_EQUAL(mListenerVelocity, val);
	alListener3f(AL_VELOCITY, mListenerVelocity.X, mListenerVelocity.Y, mListenerVelocity.Z);
	AUDIO_ASSIGN_IF_SUCCESS(mListenerVelocity, val);
}

void OpenALDevice::SetListenerOrientation(const AudioListenerOrientation& val)
{
	AUDIO_RETURN_IF_EQUAL(mListenerOrientaion, val);
	alListenerfv(AL_ORIENTATION, val.Forward.Buffer);	// first offset
	AUDIO_ASSIGN_IF_SUCCESS(mListenerOrientaion, val);
}

void OpenALDevice::SetDistanceModel(AudioDistanceModel val)
{
	AUDIO_RETURN_IF_EQUAL(mDistanceModel, val);
	alDistanceModel((uint)val);
	AUDIO_ASSIGN_IF_SUCCESS(mDistanceModel, val);

}

void OpenALDevice::SetDopplerFactor(float val)
{
	AUDIO_RETURN_IF_EQUAL(mDopplerFactor, val);
	alDopplerFactor(val);
	AUDIO_ASSIGN_IF_SUCCESS(mDopplerFactor, val);
}

void OpenALDevice::SetSpeedOfSound(float val)
{
	AUDIO_RETURN_IF_EQUAL(mSpeedOfSound, val);
	alSpeedOfSound(val);
	AUDIO_ASSIGN_IF_SUCCESS(mSpeedOfSound, val);
}


#pragma endregion AudioListener

#pragma region Extensions


bool OpenALDevice::IsExtensionSupported(const StringRef& extension) const
{
	return alIsExtensionPresent(extension.c_str()) != AL_FALSE;
}

void* OpenALDevice::GetProcAddress(const StringRef& funcName) const
{
	return alGetProcAddress(funcName.c_str());
}

uint OpenALDevice::GetEnumValue(const StringRef& enumName) const
{
	return alGetEnumValue(enumName.c_str());
}

bool OpenALDevice::IsCaptureSupport() const
{
	return IsExtensionSupported("ALC_EXT_CAPTURE") || IsExtensionSupported("ALC_EXT_capture");
}

#pragma endregion Extensions

#pragma region Context

AudioContextErrorCode OpenALDevice::GetContextError() const
{
	return AudioContextErrorCode(alcGetError(mDevice));
}


void OpenALDevice::ProcessContext() const
{
	alcProcessContext(mContext);
	AssertContextSuccess();
}

void OpenALDevice::SuspendContext() const
{
	alcSuspendContext(mContext);
	AssertContextSuccess();
}

bool OpenALDevice::IsContextExtensionSupported(const StringRef& extension) const
{
	return alcIsExtensionPresent(mDevice, extension.c_str()) != AL_FALSE;
}


void* OpenALDevice::GetContextProcAddress(const StringRef& funcName) const
{
	return alcGetProcAddress(mDevice, funcName.c_str());
}

uint OpenALDevice::GetContextEnumValue(const StringRef& enumName) const
{
	return alcGetEnumValue(mDevice, enumName.c_str());
}

bool OpenALDevice::TryGetContextInteger(AudioContextIntegerName name, int& outVal) const
{
	alcGetIntegerv(mDevice, (uint)name, sizeof(int), &outVal);
	return IsSuccess();
}

bool OpenALDevice::TryGetContextIntegerArray(AudioContextIntegerArrayName name, int* params, size_t size) const
{
	alcGetIntegerv(mDevice, (uint)name, (uint)size, params);
	return IsSuccess();
}

bool OpenALDevice::TryGetContextString(AudioContextStringName name, StringRef& outVal) const
{
	const char* str = alcGetString(mDevice, (uint)name);
	outVal.ForceSetBuffer((const char*)str);
	outVal.ForceUpdateLength();

	return IsSuccess();
}


#pragma endregion Context

#pragma region Capture


bool OpenALDevice::OpenCapureDevice(const StringRef& deviceName, uint frequency, AudioFormat format, uint bufferSize)
{
	RETURN_TRUE_IF_NOT_NULL(mCaptureDevice);

	mCaptureDevice = alcCaptureOpenDevice(deviceName.c_str(), frequency, (uint)format, bufferSize);
	AssertContextSuccess();
	return mCaptureDevice != nullptr;
}

bool OpenALDevice::CloseCaptureDevice()
{
	RETURN_TRUE_IF_NULL(mCaptureDevice);
	alcCaptureCloseDevice(mCaptureDevice);
	AssertContextSuccess();
	mCaptureDevice = nullptr;
	return true;
}

bool OpenALDevice::StartCapture() const
{
	RETURN_FALSE_IF_NULL(mCaptureDevice);
	alcCaptureStart(mCaptureDevice);
	AssertContextSuccess();
	return true;
}

bool OpenALDevice::StopCapture() const
{
	RETURN_FALSE_IF_NULL(mCaptureDevice);
	alcCaptureStop(mCaptureDevice);
	AssertContextSuccess();
	return true;
}

bool OpenALDevice::GetCapureSamples(uint samplesCount, void* outBuffer)
{
	RETURN_FALSE_IF_NULL(mCaptureDevice);
	alcCaptureSamples(mCaptureDevice, outBuffer, samplesCount);
	AssertContextSuccess();
	return true;
}

#pragma endregion Capture

MEDUSA_END;

#endif

#endif