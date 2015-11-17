// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "AudioFactory.h"
#include "Audio/Device/AudioDevice.h"
#include "Resource/Audio/IAudio.h"
#include "Core/IO/FileSystem.h"

#include "OggAudio.h"
#include "WavAudio.h"
#include "Core/IO/FileInfo.h"

MEDUSA_BEGIN;

AudioFactory::AudioFactory(void)
{

}

AudioFactory::~AudioFactory(void)
{
}

bool AudioFactory::Initialize()
{
	AudioDevice::Instance().Initialize();
	return true;
}


bool AudioFactory::Uninitialize()
{
	AudioDevice::Instance().Uninitialize();
	Clear();
	return true;
}


IAudio* AudioFactory::CreateFromRaw(const FileIdRef& fileId, AudioFileType audioFileType, const MemoryByteData& data, uint sampleCount, uint channelCount, uint samplerRate, uint bitsPerSample, ResourceShareType shareType /*= ResourceShareType::Share*/)
{
	IAudio* buffer = Find(fileId);
	RETURN_SELF_IF_NOT_NULL(buffer);

	switch (audioFileType)
	{
	case AudioFileType::ogg:
		buffer = new OggAudio(data, fileId);
		break;
	case AudioFileType::wav:
		buffer = new WavAudio(data, fileId);
		break;
	default:
        return nullptr;
	}

	buffer->SetSampleCount(sampleCount);
	buffer->SetChannelCount(sampleCount);
	buffer->SetSampleRate(samplerRate);
	buffer->SetBitsPerSample(bitsPerSample);
	Add(buffer, shareType);

	return buffer;
}

IAudio* AudioFactory::CreateFromFile(const FileIdRef& fileId, ResourceShareType shareType /*= ResourceShareType::Share*/)
{
	IAudio* buffer = Find(fileId);
	RETURN_SELF_IF_NOT_NULL(buffer);

	switch (FileInfo::ExtractType(fileId.Name))
	{
	case FileType::ogg:
		buffer = OggAudio::CreateFromFile(fileId);
		break;
	case FileType::wav:
		buffer = WavAudio::CreateFromFile(fileId);
		break;
	default:
		return nullptr;
		break;
	}

	RETURN_NULL_IF_NULL(buffer);
	Add(buffer, shareType);
	return buffer;
}

IAudio* AudioFactory::CreateFromMemory(const FileIdRef& fileId, const MemoryByteData& data, ResourceShareType shareType /*= ResourceShareType::Share*/)
{
	IAudio* buffer = Find(fileId);
	RETURN_SELF_IF_NOT_NULL(buffer);

	switch (FileInfo::ExtractType(fileId.Name))
	{
	case FileType::ogg:
		buffer = OggAudio::CreateFromMemory(fileId, data);
		break;
	case FileType::wav:
		buffer = WavAudio::CreateFromMemory(fileId, data);
		break;
	default:
		return nullptr;
		break;
	}

	RETURN_NULL_IF_NULL(buffer);
	Add(buffer, shareType);
	return buffer;
}


MEDUSA_END;