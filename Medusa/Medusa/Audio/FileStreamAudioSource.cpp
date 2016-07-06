// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#ifdef MEDUSA_AL
#include "FileStreamAudioSource.h"
#include "Core/Threading/ScopedLock.h"
#include "Resource/Audio/AudioFactory.h"
MEDUSA_BEGIN;


FileStreamAudioSource::FileStreamAudioSource(const StringRef& name/*=StringRef::Empty*/)
	:StreamAudioSource(name)
{
	
}


FileStreamAudioSource::~FileStreamAudioSource()
{
}

bool FileStreamAudioSource::OpenFile(const FileIdRef& fileId)
{
	mAudioFile = AudioFactory::Instance().CreateFromFile(fileId);
	if (mAudioFile!=nullptr)
	{
		mAudioStream = MemoryStream::OpenRead(mAudioFile->Data());
		Initialize(mAudioFile->ChannelCount(), mAudioFile->SampleRate());
		return true;
	}

	return false;
}

bool FileStreamAudioSource::OpenMemory(const FileIdRef& fileId, const MemoryData& data)
{
	mAudioFile = AudioFactory::Instance().CreateFromMemory(fileId,data);
	if (mAudioFile != nullptr)
	{
		mAudioStream = MemoryStream::OpenRead(mAudioFile->Data());
		Initialize(mAudioFile->ChannelCount(), mAudioFile->SampleRate());
		return true;
	}

	return false;
}

void FileStreamAudioSource::OnSeek(uint secondOffset)
{
	ScopedLock lock(mMutex);
	mAudioStream.Seek(secondOffset);
}

bool FileStreamAudioSource::OnFetchData(MemoryData& outData)
{
	ScopedLock lock(mMutex);

	return mAudioStream.ReadDataTo(outData)>0;
}



MEDUSA_END;
#endif