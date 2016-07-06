// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
//SIREN_BODY_INCLUDE_BEGIN
#include "FileEntry.h"
//SIREN_BODY_INCLUDE_END
#include "FileStorage.h"
#include "Core/IO/Path.h"
#include "Core/IO/Stream/FileStream.h"
#include "Core/IO/Directory.h"

MEDUSA_BEGIN;

FileEntry::FileEntry()
{
	//SIREN_BODY_CONSTRUCT_BEGIN
	mPermission = (FilePermission)384;
	mFirstBlockId = 0xFFFFFFFF;
	mOriginalSize = 0;
	mSize = 0;
	mOperations = (EntryOperation)0;
//SIREN_BODY_CONSTRUCT_END
}


FileEntry::FileEntry(uint id, const StringRef& name)
{
	mName = name;
	mPath = name;

	mFirstBlockId = Math::UIntMaxValue;
	mOriginalSize = 0;
	mSize = 0;
	mPermission = (FilePermission)384;
	mOperations = (EntryOperation)0;
}

MemoryData FileEntry::ReadAllData(DataReadingMode mode /*= DataReadingMode::AlwaysCopy*/) const
{
	return mStorage->ReadAllData(*this, mode);
}

Share<const IStream> FileEntry::Read(FileDataType dataType /*= FileDataType::Binary*/) const
{
	return mStorage->ReadFileHelper(*this, dataType);
}

uint FileEntry::ExtractedSize() const
{
	if (mOriginalSize != 0)
	{
		return mOriginalSize;
	}
	return mSize;
}

void FileEntry::Print(const StringRef& indent) const
{
	auto opStr = ConvertToString(mOperations);
	auto perStr = ConvertToString(mPermission);

	Log::FormatInfo("{}{}:{}\t{}\t{}\t{}", indent, mName, mSize,perStr,opStr,mSignature);
}

bool FileEntry::Extract(const StringRef& outDir) const
{
	auto path = Path::Combine(outDir, mPath);
	Directory::CreateDirectoryForFile(path);
	FileStream dest(path, FileOpenMode::DestoryWriteOrCreate, FileDataType::Binary);
	if (!dest.IsOpen())
	{
		Log::FormatError("Cannot create {}", path);
		return false;
	}

	auto readStream = Read(FileDataType::Binary);
	auto writeSize = readStream->CopyTo(dest);
	auto extractSize = ExtractedSize();
	if (writeSize!= extractSize)
	{
		Log::FormatError("Cannot Extract {}", path);
		return false;
	}
	return true;
}

HeapString FileEntry::ConvertToString(FilePermission val)
{
	HeapString str;
	if (MEDUSA_FLAG_HAS(val,FilePermission::Read))
	{
		str += "R";
	}
	if (MEDUSA_FLAG_HAS(val, FilePermission::Write))
	{
		str += "W";
	}
	return str;
}

HeapString FileEntry::ConvertToString(EntryOperation val)
{
	HeapString str;
	if (MEDUSA_FLAG_HAS(val, EntryOperation::Add))
	{
		str += "A";
	}
	if (MEDUSA_FLAG_HAS(val, EntryOperation::Delete))
	{
		str += "D";
	}
	if (MEDUSA_FLAG_HAS(val, EntryOperation::Update))
	{
		str += "U";
	}
	return str;
}

FileEntry::~FileEntry()
{
	//SIREN_BODY_DESTRUCT_BEGIN
//SIREN_BODY_DESTRUCT_END
}

bool FileEntry::Initialize(FileStorage* storage, DirectoryEntry* parent)
{
	mStorage = storage;
	mParent = parent;
	mPath = mParent != nullptr ? Path::CombineNoChecks(mParent->Path(), mName) : mName;

	return true;
}



//SIREN_BODY_METADATA_BEGIN
SIREN_METADATA(FileEntry, 9);
SIREN_FIELD_METADATA_STRUCT(0, FileEntry, Name, 4);
SIREN_FIELD_METADATA(1, FileEntry, Permission, 10, (FilePermission)384, true);
SIREN_FIELD_METADATA(2, FileEntry, FirstBlockId, 12, 0xFFFFFFFF, true);
SIREN_FIELD_METADATA(3, FileEntry, OriginalSize, 12, 0, true);
SIREN_FIELD_METADATA(4, FileEntry, Size, 4, 0, true);
SIREN_FIELD_METADATA_STRUCT(5, FileEntry, Signature, 9);
SIREN_FIELD_METADATA(6, FileEntry, Operations, 10, (EntryOperation)0, true);
SIREN_FIELD_METADATA_STRUCT(7, FileEntry, CoderOffsets, 12);
//SIREN_BODY_METADATA_END

MEDUSA_END;