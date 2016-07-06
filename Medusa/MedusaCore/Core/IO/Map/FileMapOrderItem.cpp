// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "FileMapOrderItem.h"
#include "Core/Log/Log.h"
#include "FileMapNameItem.h"
#include "FileMapOrderItem.h"
#include "FileMapTagItem.h"
#include "Core/IO/Storage/FileEntry.h"
#include "Core/IO/Storage/DirectoryEntry.h"


MEDUSA_BEGIN;


FileMapOrderItem::FileMapOrderItem(uint order/*=0*/)
	:mOrder(order),
	mParent(nullptr)
{
}

FileIdRef FileMapOrderItem::GetFileId() const
{
	if (mParent != nullptr)
	{
		return FileIdRef(mParent->Name(), mOrder);
	}
	else
	{
		return FileIdRef::Empty;
	}
}

FileMapOrderItem::~FileMapOrderItem()
{
	mFiles.Clear();
}


int FileMapOrderItem::DiffScore() const
{
	return mParent->Parent()->DiffScore();
}

void FileMapOrderItem::AddFileEntry(FileEntry& fileEntry, const StringRef& name/* = StringRef::Empty*/, void* region /*= nullptr*/)
{
	auto package = (IPackage*)fileEntry.Parent()->Storage();
	auto* fileEntryRef = mFiles.TryGet(package);
	if (fileEntryRef==nullptr)
	{
		if (region==nullptr)
		{
			mFiles.Add(package, FileEntryRef(&fileEntry, StringRef::Empty, region));	//ignore region name when have no region
		}
		else
		{
			mFiles.Add(package, FileEntryRef(&fileEntry, name, region));
		}
		UpdateFirstValidFileEntry();
	}
	else
	{
		if (fileEntryRef->RegionName==name)	//only apply region
		{
			fileEntryRef->Region = region;
		}
		else
		{
			Log::AssertFailedFormat("Duplicate add file entry:{} with name:{}", fileEntry.Name(),name);
		}
	}
}

bool FileMapOrderItem::RemoveFileEntry(const FileEntry& fileEntry)
{
	if (mFiles.RemoveKey((IPackage*)fileEntry.Parent()->Storage()))
	{
		UpdateFirstValidFileEntry();
	}

	return false;
}


bool FileMapOrderItem::RemoveFileEntryRegion(const FileEntry& fileEntry)
{
	auto* fileEntryRef= mFiles.TryGet((IPackage*)fileEntry.Parent()->Storage());
	if (fileEntryRef!=nullptr)
	{
		fileEntryRef->Region = nullptr;
		return true;
	}
	return false;
}

void FileMapOrderItem::UpdateFirstValidFileEntry()
{
	//re search first valid
	mFirstValidFileEntry = nullptr;
	for (auto& file : mFiles)
	{
		if (file.second.Entry->IsValid())
		{
			mFirstValidFileEntry = &file.second;
		}
	}
}

MEDUSA_END;
