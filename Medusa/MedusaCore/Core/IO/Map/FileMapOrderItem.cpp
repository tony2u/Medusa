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
	if (mParent!=nullptr)
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

void FileMapOrderItem::AddFileEntry(FileEntry& fileEntry, void* region /*= nullptr*/)
{
	mFiles.Add((IPackage*)fileEntry.Parent()->Storage(), FileEntryRef(&fileEntry, region));
	UpdateFirstValidFileEntry();
}

bool FileMapOrderItem::RemoveFileEntry(const FileEntry& fileEntry)
{
	if (mFiles.RemoveKey((IPackage*)fileEntry.Parent()->Storage()))
	{
		UpdateFirstValidFileEntry();
	}

	return false;
}


void FileMapOrderItem::UpdateFirstValidFileEntry()
{
	//re search first valid
	mFirstValidFileEntry.Entry = nullptr;
	mFirstValidFileEntry.Region = nullptr;

	for (const auto& file : mFiles)
	{
		if (file.second.Entry->IsValid())
		{
			mFirstValidFileEntry = file.second;
		}
	}
}

MEDUSA_END;
