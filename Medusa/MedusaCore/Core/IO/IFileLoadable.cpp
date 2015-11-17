// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "Core/IO/IFileLoadable.h"
#include "Core/IO/File.h"
#include "Core/Log/Log.h"
#include "Core/IO/FileSystem.h"

MEDUSA_BEGIN;


bool IFileLoadable::LoadFromFileSystem(const FileIdRef& fileId, uint format/*=(uint)-1*/)
{
	MemoryByteData data = FileSystem::Instance().ReadAllData(fileId);
	if (format == (uint)-1)
	{
		format = OnCheckFormat(fileId.Name);
	}
	RETURN_FALSE_IF_EMPTY(data);
	return LoadFromData(fileId.Name, data, format);
}

bool IFileLoadable::LoadFromData(StringRef path, const MemoryByteData& data, uint format/*=(uint)-1*/)
{
	Unload();
	if (data.IsNull())
	{
		return false;
	}

	return true;
}

void IFileLoadable::Unload()
{

}


MEDUSA_END;