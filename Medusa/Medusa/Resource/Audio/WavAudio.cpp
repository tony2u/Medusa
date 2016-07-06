// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#ifdef MEDUSA_AL
#include "WavAudio.h"
#include "Core/IO/File.h"
#include "Core/IO/FileSystem.h"

MEDUSA_BEGIN;

struct WAVHeader
{
	char  riff[4];//'RIFF'
	unsigned int riffSize;
	char  wave[4];//'WAVE'
	char  fmt[4];//'fmt '
	unsigned int fmtSize;
	unsigned short format;
	unsigned short channels;
	unsigned int samplesPerSec;
	unsigned int bytesPerSec;
	unsigned short blockAlign;
	unsigned short bitsPerSample;
	char  data[4];//'data'
	unsigned int dataSize=0;
};


WavAudio* WavAudio::CreateFromFile(const FileIdRef& fileId)
{
	MemoryData data = FileSystem::Instance().ReadAllData(fileId);
	return CreateFromMemory(fileId, data);
}

WavAudio* WavAudio::CreateFromMemory(const FileIdRef& fileId, MemoryData data)
{
	// Initialize the memory data
	MemoryStream stream = MemoryStream::OpenRead(data);

	WAVHeader header;
	RETURN_NULL_IF_FALSE(stream.ReadTo(header));

#ifdef MEDUSA_SAFE_CHECK
	if (memcmp("RIFF", header.riff, 4) || memcmp("WAVE", header.wave, 4) || memcmp("fmt ", header.fmt, 4) || memcmp("data", header.data, 4))
	{
		Log::FormatError("Invalid wav file:{}", fileId.Name);
		return nullptr;
	}
#endif

	auto audioData = stream.ReadData(header.dataSize, DataReadingMode::DirectMove);
	WavAudio* audio = new WavAudio(audioData, fileId);

	uint frameCount = 8 * header.dataSize / header.bitsPerSample;
	audio->SetSampleCount(frameCount);
	audio->SetChannelCount(header.channels);
	audio->SetSampleRate(header.samplesPerSec);
	audio->SetBitsPerSample(header.bitsPerSample);

	return audio;
}


MEDUSA_END;
#endif