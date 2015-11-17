// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#ifdef MEDUSA_AL
#include "Audio/AudioTypes.h"
#include "Audio/Device/IAudioDevice.h"
MEDUSA_BEGIN;

class OpenALDevice:public IAudioDevice
{
public :
    OpenALDevice();
    ~OpenALDevice();

	bool Initialize(const Dictionary<AudioContextAttribute, uint,SafeEnumHashCoder<AudioContextAttribute>>& attributes, const StringRef& deviceName = StringRef::Empty);
	virtual bool Initialize()override;
	virtual bool Uninitialize()override;

	virtual AudioErrorCode GetError()const override;
	virtual AudioFormat GetAudioFormat(uint channelCount, uint bitsPerSample)const override;
	virtual uint GetUnusedSource()override;
	virtual uint RecycleSource(uint source)override;

#pragma region Values

public:
	virtual void SetDistanceModel(AudioDistanceModel model)override;
	virtual void SetDopplerFactor(float val)override;
	virtual void SetSpeedOfSound(float val)override;
protected:
	virtual bool TryGetInteger(AudioIntegerName name,int& outVal)const override;
	virtual bool TryGetIntegerArray(AudioIntegerArrayName name,int* params)const override;
	virtual bool TryGetBoolean(AudioBooleanName name,bool& outVal)const override;
	virtual bool TryGetBooleanArray(AudioBooleanArrayName name,bool* params)const override;
	virtual bool TryGetFloat(AudioFloatName name,float& outVal)const override;
	virtual bool TryGetFloatArray(AudioFloatArrayName name,float* params)const override;
	virtual bool TryGetString(AudioStringName name,StringRef& outVal)const override;

#pragma endregion Values

#pragma region Buffer
	public:
	virtual bool IsBuffer(uint bufferObject)const override;
	virtual void GenBuffers(uint count,uint* outBuffers)const override;
	virtual void DeleteBuffers(uint count,uint* buffers)const override;
	virtual void LoadBufferData(uint bufferObject,AudioFormat format,const void* data,uintp size,uintp freq)const override;

	virtual uint GetBufferProperty(uint bufferObject,AudioBufferProperty bufferProperty)const override;


#pragma endregion Buffer
#pragma region Source
public:
	virtual bool IsSource(uint sourceObject)const override;

	virtual void GenSources(uint count,uint* outSources)const override;
	virtual void DeleteSources(uint count,uint* sources)const override;

	virtual bool GetSourceBooleanProperty(uint sourceObject,AudioSourceBooleanProperty sourceProperty)const override;
	virtual uint GetSourceIntegerProperty(uint sourceObject,AudioSourceIntegerProperty sourceProperty)const override;
	virtual float GetSourceFloatProperty(uint sourceObject,AudioSourceFloatProperty sourceProperty)const override;
	virtual Point3F GetSourceFloatArrayProperty(uint sourceObject,AudioSourceFloatArrayProperty sourceProperty)const override;

	virtual void SetSourceBooleanProperty(uint sourceObject,AudioSourceBooleanProperty sourceProperty,bool val)const override;
	virtual void SetSourceIntegerProperty(uint sourceObject,AudioSourceIntegerProperty sourceProperty,uint val)const override;
	virtual void SetSourceFloatProperty(uint sourceObject,AudioSourceFloatProperty sourceProperty,float val)const override;
	virtual void SetSourceFloatArrayProperty(uint sourceObject,AudioSourceFloatArrayProperty sourceProperty,const Point3F& val)const override;

	virtual void PlaySources(uint count,uint* sourceObjects)const override;
	virtual void PauseSources(uint count,uint* sourceObjects)const override;
	virtual void RewindSources(uint count,uint* sourceObjects)const override;
	virtual void StopSources(uint count,uint* sourceObjects)const override;

	virtual void QueueSourceBuffers(uint sourceObject,uint count,uint* bufferObjects)const override;
	virtual void UnqueueSourceBuffers(uint sourceObject,uint count,uint* bufferObjects)const override;

#pragma endregion Source
#pragma region AudioListener
public:
	virtual float GetListenerVolume()const override;
	virtual Point3F GetListenerPosition()const override;
	virtual Point3F GetListenerVelocity()const override;
	virtual AudioListenerOrientation GetListenerOrientation()const override;

	virtual void SetListenerVolume(float val) override;
	virtual void SetListenerPosition(const Point3F& val) override;
	virtual void SetListenerVelocity(const Point3F& val) override;
	virtual void SetListenerOrientation(const AudioListenerOrientation& val) override;

#pragma endregion AudioListener
#pragma region Extensions
public:
	virtual bool IsExtensionSupported(const StringRef& extension)const override;
	virtual void* GetProcAddress(const StringRef& funcName)const override;
	virtual uint GetEnumValue(const StringRef& enumName)const override;
	virtual bool IsCaptureSupport()const override;

#pragma endregion Extensions

#pragma region Context
public:
	virtual AudioContextErrorCode GetContextError()const override;

	virtual void ProcessContext()const override;
	virtual void SuspendContext()const override;

	virtual bool IsContextExtensionSupported(const StringRef& extension)const override;
	virtual void* GetContextProcAddress(const StringRef& funcName)const override;
	virtual uint GetContextEnumValue(const StringRef& enumName)const override;
protected:
	virtual bool TryGetContextInteger(AudioContextIntegerName name,int& outVal)const override;
	virtual bool TryGetContextIntegerArray(AudioContextIntegerArrayName name,int* params,size_t size)const override;
	virtual bool TryGetContextString(AudioContextStringName name,StringRef& outVal)const override;

#pragma endregion Context

#pragma region Capture
public:
	virtual bool OpenCapureDevice(const StringRef& deviceName,uint frequency,AudioFormat format,uint bufferSize) override;
	virtual bool CloseCaptureDevice() override;
	virtual bool StartCapture()const override;
	virtual bool StopCapture()const override;
	virtual bool GetCapureSamples(uint samplesCount,void* outBuffer) override;
	virtual bool IsCaptureOpen()const override {return mCaptureDevice!=nullptr;}
#pragma endregion Capture
protected:
	ALCdevice* mDevice;
	ALCcontext* mContext;

	ALCdevice* mCaptureDevice;

};

MEDUSA_END;

#endif