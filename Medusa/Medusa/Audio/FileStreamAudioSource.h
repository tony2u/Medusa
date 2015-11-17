// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "Audio/StreamAudioSource.h"
#include "Core/Threading/Mutex.h"
#include "Core/IO/Stream/MemoryStream.h"

MEDUSA_BEGIN;


class FileStreamAudioSource : public StreamAudioSource
{
public:
	FileStreamAudioSource(const StringRef& name = StringRef::Empty);
	virtual ~FileStreamAudioSource();
	bool OpenFile(const FileIdRef& fileId);
	bool OpenMemory(const FileIdRef& fileId, const MemoryByteData& data);

protected:
	virtual void OnSeek(uint secondOffset);
	virtual bool OnFetchData(MemoryByteData& outData);
private:
	IAudio* mAudioFile = nullptr;
	MemoryStream mAudioStream;
	Mutex mMutex;
};


MEDUSA_END;