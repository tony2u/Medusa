// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#ifdef MEDUSA_AL
#include "Core/Pattern/IInitializable.h"
#include "Core/Collection/Dictionary.h"
#include "Audio/AudioTypes.h"
#include "Core/String/StringRef.h"

MEDUSA_BEGIN;

class IAudioDevice:public IInitializable
{
public:
	IAudioDevice(void);
	virtual ~IAudioDevice(void);
public:
	virtual AudioErrorCode GetError()const=0;
	bool AssertSuccess()const;
	bool IsSuccess()const;


	bool Initialize(const Dictionary<AudioContextAttribute,uint>& attributes,const StringRef& deviceName=StringRef::Empty){return true;}
	virtual bool Initialize()override { return true; }
	virtual bool Uninitialize()override;

	uint MaxSourceCount()const{return mMaxSourceCount;}
	virtual uint GetUnusedSource()=0;
	virtual uint RecycleSource(uint source)=0;


	virtual AudioFormat GetAudioFormat(uint channelCount,uint bitsPerSample)const=0;

#pragma region Values
public:
	virtual void SetDistanceModel(AudioDistanceModel model)=0;
	virtual void SetDopplerFactor(float val)=0;
	virtual void SetSpeedOfSound(float val)=0;

	int GetInteger(AudioIntegerName name)const;
	void GetIntegerArray(AudioIntegerArrayName name,int* params)const;
	bool GetBoolean(AudioBooleanName name)const;
	void GetBooleanArray(AudioBooleanArrayName name,bool* params)const;
	float GetFloat(AudioFloatName name)const;
	void GetFloatArray(AudioFloatArrayName name,float* params)const;
	StringRef GetString(AudioStringName name)const;
protected:
	virtual bool TryGetInteger(AudioIntegerName name,int& outVal)const=0;
	virtual bool TryGetIntegerArray(AudioIntegerArrayName name,int* params)const=0;
	virtual bool TryGetBoolean(AudioBooleanName name,bool& outVal)const=0;
	virtual bool TryGetBooleanArray(AudioBooleanArrayName name,bool* params)const=0;
	virtual bool TryGetFloat(AudioFloatName name,float& outVal)const=0;
	virtual bool TryGetFloatArray(AudioFloatArrayName name,float* params)const=0;
	virtual bool TryGetString(AudioStringName name,StringRef& outVal)const=0;

#pragma endregion Values

#pragma region Buffer
public:
	virtual bool IsBuffer(uint bufferObject)const=0;

	uint GenBuffer()const;
	virtual void GenBuffers(uint count,uint* outBuffers)const=0;

	void DeleteBuffer(uint bufferObject)const;
	virtual void DeleteBuffers(uint count,uint* buffers)const=0;

	virtual void LoadBufferData(uint bufferObject,AudioFormat format,const void* data,uintp size,uintp freq)const=0;
	virtual uint GetBufferProperty(uint bufferObject,AudioBufferProperty bufferProperty)const=0;


#pragma endregion Buffer


#pragma region Source
	public:
	virtual bool IsSource(uint sourceObject)const=0;

	uint GenSource()const;
	virtual void GenSources(uint count,uint* outSources)const=0;

	void DeleteSource(uint sourceObject)const;
	virtual void DeleteSources(uint count,uint* sources)const=0;

	virtual bool GetSourceBooleanProperty(uint sourceObject,AudioSourceBooleanProperty sourceProperty)const=0;
	virtual uint GetSourceIntegerProperty(uint sourceObject,AudioSourceIntegerProperty sourceProperty)const=0;
	virtual float GetSourceFloatProperty(uint sourceObject,AudioSourceFloatProperty sourceProperty)const=0;
	virtual Point3F GetSourceFloatArrayProperty(uint sourceObject,AudioSourceFloatArrayProperty sourceProperty)const=0;

	virtual void SetSourceBooleanProperty(uint sourceObject,AudioSourceBooleanProperty sourceProperty,bool val)const=0;
	virtual void SetSourceIntegerProperty(uint sourceObject,AudioSourceIntegerProperty sourceProperty,uint val)const=0;
	virtual void SetSourceFloatProperty(uint sourceObject,AudioSourceFloatProperty sourceProperty,float val)const=0;
	virtual void SetSourceFloatArrayProperty(uint sourceObject,AudioSourceFloatArrayProperty sourceProperty,const Point3F& val)const=0;

	void PlaySource(uint sourceObject)const;
	virtual void PlaySources(uint count,uint* sourceObjects)const=0;

	void PauseSource(uint sourceObject)const;
	virtual void PauseSources(uint count,uint* sourceObjects)const=0;

	void RewindSource(uint sourceObject)const;
	virtual void RewindSources(uint count,uint* sourceObjects)const=0;

	void StopSource(uint sourceObject)const;
	virtual void StopSources(uint count,uint* sourceObjects)const=0;


	void QueueSourceBuffer(uint sourceObject,uint bufferObject)const;
	virtual void QueueSourceBuffers(uint sourceObject,uint count,uint* bufferObjects)const=0;

	uint UnqueueSourceBuffer(uint sourceObject)const;
	virtual void UnqueueSourceBuffers(uint sourceObject,uint count,uint* bufferObjects)const=0;

	void SetSourceBuffer(uint sourceObject,uint bufferObject)const;
	AudioSourceState GetSourceState(uint sourceObject)const;
#pragma endregion Source

#pragma region AudioListener
public:
	virtual float GetListenerVolume()const=0;
	virtual Point3F GetListenerPosition()const=0;
	virtual Point3F GetListenerVelocity()const=0;
	virtual AudioListenerOrientation GetListenerOrientation()const=0;

	virtual void SetListenerVolume(float val)=0;
	virtual void SetListenerPosition(const Point3F& val)=0;
	virtual void SetListenerVelocity(const Point3F& val)=0;
	virtual void SetListenerOrientation(const AudioListenerOrientation& val)=0;

#pragma endregion AudioListener

#pragma region Extensions
public:
	virtual bool IsExtensionSupported(const StringRef& extension)const=0;
	virtual void* GetProcAddress(const StringRef& funcName)const=0;
	virtual uint GetEnumValue(const StringRef& enumName)const=0;
	virtual bool IsCaptureSupport()const=0;
#pragma endregion Extensions

#pragma region Context
public:
	virtual AudioContextErrorCode GetContextError()const=0;
	bool AssertContextSuccess()const;
	bool IsContextSuccess()const;

	virtual void ProcessContext()const=0;
	virtual void SuspendContext()const=0;

	virtual bool IsContextExtensionSupported(const StringRef& extension)const=0;
	virtual void* GetContextProcAddress(const StringRef& funcName)const=0;
	virtual uint GetContextEnumValue(const StringRef& enumName)const=0;

	int GetContextInteger(AudioContextIntegerName name)const;
	void GetContextIntegerArray(AudioContextIntegerArrayName name,int* params,size_t size)const;
	StringRef GetContextString(AudioContextStringName name)const;
protected:
	virtual bool TryGetContextInteger(AudioContextIntegerName name,int& outVal)const=0;
	virtual bool TryGetContextIntegerArray(AudioContextIntegerArrayName name,int* params,size_t size)const=0;
	virtual bool TryGetContextString(AudioContextStringName name,StringRef& outVal)const=0;
#pragma endregion Context

#pragma region Capture
public:
	virtual bool OpenCapureDevice(const StringRef& deviceName,uint frequency,AudioFormat format,uint bufferSize)=0;
	virtual bool CloseCaptureDevice()=0;
	virtual bool StartCapture()const=0;
	virtual bool StopCapture()const=0;
	virtual bool GetCapureSamples(uint samplesCount,void* outBuffer)=0;
	virtual bool IsCaptureOpen()const=0;

#pragma endregion Capture

	List<StringRef> GetAllDevices();
	StringRef GetDefaultDevice();

	List<StringRef> GetAllCaptureDevices();
	StringRef GetDefaultCaptureDevice();

	void PrintAll();

protected:
	List<uint> mSources;
	uint mMaxSourceCount;

#ifdef MEDUSA_AUDIO_STATE_CACHE_ENABLED
protected:
	//int values
	AudioDistanceModel mDistanceModel;
	//float values
	float mDopplerFactor;
	float mSpeedOfSound;

	//string  values
	StringRef mVendor;
	StringRef mRenderer;
	StringRef mVersion;
	StringRef mExtensions;

	//AudioListener
	float mListenerVolume;
	Point3F mListenerPosition;
	Point3F mListenerVelocity;
	AudioListenerOrientation mListenerOrientaion;

	//context string values
	StringRef mDefaultDeviceName;
	StringRef mDefaultCaptureDeviceName;
	StringRef mAllDeviceNames;
	StringRef mAllCaptureDeviceNames;
	StringRef mContextExtensions;

	//context int values
	int mContextMajorVersion;
	int mContextMinorVersion;
	int mContextAttributeSize;
	int mContextMonoSourceCount;
	int mContextStereoSourceCount;
	List<int> mContextAttributes;
#endif


};

MEDUSA_END;

#endif
