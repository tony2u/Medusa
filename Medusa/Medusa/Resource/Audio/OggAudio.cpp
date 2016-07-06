// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#if  defined(MEDUSA_OGG)&&defined(MEDUSA_AL)

#include "OggAudio.h"
#include "Core/IO/File.h"
#include "Core/IO/FileSystem.h"

#include "Lib/Common/ogg/ogg.h"
#include "Lib/Common/vorbis/vorbisfile.h"
#include "Core/System/BitConverter.h"

MEDUSA_BEGIN;

size_t ogg_read_func(void *ptr, size_t size, size_t nmemb, void *datasource)
{
	MemoryStream* oggStream = (MemoryStream*)datasource;
	uintp readSize = Math::Min(oggStream->LeftLength(), (uintp)nmemb*size);
	MemoryData outData = MemoryData::FromStatic((byte*)ptr, readSize);
	oggStream->ReadDataTo(outData);

	return readSize;
}

int ogg_seek_func(void *datasource, ogg_int64_t offset, int whence)
{
	MemoryStream* oggStream = (MemoryStream*)datasource;
	oggStream->Seek((intp)offset, (SeekOrigin)whence);

	return 0;
}
int ogg_close_func(void *datasource)
{
	return 0;
}

long ogg_tell_func(void *datasource)
{
	MemoryStream* oggStream = (MemoryStream*)datasource;
	return (long)oggStream->Position();
}

OggAudio* OggAudio::CreateFromFile(const FileIdRef& fileId)
{
	MemoryData data = FileSystem::Instance().ReadAllData(fileId);
	return CreateFromMemory(fileId, data);
}

OggAudio* OggAudio::CreateFromMemory(const FileIdRef& fileId, MemoryData data)
{

	ov_callbacks callbacks;
	callbacks.read_func = ogg_read_func;
	callbacks.seek_func = ogg_seek_func;
	callbacks.close_func = ogg_close_func;
	callbacks.tell_func = ogg_tell_func;

	OggVorbis_File vf;
	MemoryStream oggStream = MemoryStream::OpenRead(data);
	if (ov_open_callbacks(&oggStream, &vf, nullptr, 0, callbacks))
	{
		Log::FormatError("{} does not appear to be an Ogg bitstream.", fileId.Name);
		return nullptr;
	}

	vorbis_info* vi = ov_info(&vf, -1);
	uintp sampleCount = (uintp)ov_pcm_total(&vf, -1);
	bool seekable = ov_seekable(&vf)!=0;

	uint bigEndian = !BitConverter::IsLittle();
	int currentSection = 0;

	uintp pcmSize = sampleCount*vi->channels*sizeof(short);
	MemoryStream pcmSteam(pcmSize);

	while (true)
	{
		long readSize = ov_read(&vf, (char*)pcmSteam.MutablePtr(), (int)pcmSteam.LeftLength(), bigEndian, 2, 1, &currentSection);
		if (readSize == 0)
		{
			//end of file
            break;
		}
		else if (readSize > 0)
		{
			pcmSteam.Seek(readSize, SeekOrigin::Current);
		}
		else
		{
			if (readSize == OV_EBADLINK)
			{
				Log::FormatError("{} Corrupt bitstream section!", fileId.Name);
				return nullptr;

			}
		}
	}

	auto audioData = pcmSteam.CurrentBuffer();

	OggAudio* audio = new OggAudio(audioData, fileId);
	audio->SetSampleCount(sampleCount);
	audio->SetChannelCount(vi->channels);
	audio->SetSampleRate(vi->rate);
	audio->SetBitsPerSample(16);
	audio->SetSeekable(seekable);
	return audio;
}


MEDUSA_END;
#endif
