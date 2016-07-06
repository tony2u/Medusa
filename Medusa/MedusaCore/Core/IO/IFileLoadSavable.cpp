// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "Core/IO/IFileLoadSavable.h"
#include "Core/IO/File.h"
#include "Core/Log/Log.h"
#include "Core/IO/FileSystem.h"
#include "Core/System/System.h"
MEDUSA_BEGIN;


bool IFileLoadSavable::LoadFromFileSystem(const FileIdRef& fileId, uint format/*=(uint)-1*/)
{
	if (format == (uint)-1)
	{
		format = OnCheckFormat(fileId.Name);
	}

	MemoryData data = FileSystem::Instance().ReadAllData(fileId);
	if (data.IsEmpty())
	{
		Log::FormatError("Cannot load:{}", fileId.ToString());
		return false;
	}
	return LoadFromData(fileId, data, format);
}

bool IFileLoadSavable::LoadFromData(const FileIdRef& fileId, const MemoryData& data, uint format/*=(uint)-1*/)
{
	Unload();
	if (data.IsNull())
	{
		return false;
	}

	return true;
}

void IFileLoadSavable::Unload()
{

}

bool IFileLoadSavable::Save(const StringRef& path, uint format /*= (uint)-1*/)
{
	if (format == (uint)-1)
	{
		format = OnCheckFormat(path);
	}

	auto realPath = System::Instance().GetWritablePath(path);
	auto fs = File::OpenBinaryWriter(path);
	return OnSave(realPath, *fs.get(), format);
}


bool IFileLoadSavable::OnSave(const StringRef& path, IStream& stream, uint format /*= (uint)-1*/)
{
	return false;
}

MEDUSA_END;