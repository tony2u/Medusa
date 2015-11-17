// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Siren/SirenHeader.h"

//SIREN_HEADER_INCLUDE_BEGIN
#include "Core/IO/Storage/FilePermission.h"
#include "Core/IO/Storage/EntryOperation.h"
//SIREN_HEADER_INCLUDE_END
#include "Core/IO/Stream/StreamDefines.h"
#include "Core/IO/FileDefines.h"

MEDUSA_BEGIN;

class FileEntry
{
	friend class FileStorage;
	friend class DirectoryEntry;
public:
	struct Schema;
	FileEntry();
	~FileEntry();

	FileEntry(uint id, const StringRef& name);

	bool Initialize(FileStorage* storage, DirectoryEntry* parent);
	bool IsReadonly()const { return !MEDUSA_HAS_FLAG(mPermission, FilePermission::Write); }
	//SIREN_HEADER_COPY_BEGIN
public:
	FileEntry(const FileEntry& other)
	{
		mName = other.mName;
		mPermission = other.mPermission;
		mFirstBlockId = other.mFirstBlockId;
		mOriginalSize = other.mOriginalSize;
		mSize = other.mSize;
		mSignature = other.mSignature;
		mOperations = other.mOperations;
		mCoderOffsets = other.mCoderOffsets;
	}
	FileEntry& operator=(const FileEntry& other)
	{
		mName = other.mName;
		mPermission = other.mPermission;
		mFirstBlockId = other.mFirstBlockId;
		mOriginalSize = other.mOriginalSize;
		mSize = other.mSize;
		mSignature = other.mSignature;
		mOperations = other.mOperations;
		mCoderOffsets = other.mCoderOffsets;
		return *this;
	}
	//SIREN_HEADER_COPY_END
public:
	bool operator<(const FileEntry& other)const { return mName<other.mName; }
	bool operator==(const FileEntry& other)const { return mName ==other.mName; }
	//SIREN_HEADER_METHOD_BEGIN
public:
	SIREN_METHOD(HeapString, Name);
	SIREN_METHOD(FilePermission, Permission);
	SIREN_METHOD(uint, FirstBlockId);
	SIREN_METHOD(uint, OriginalSize);
	SIREN_METHOD(uint, Size);
	SIREN_METHOD(HeapString, Signature);
	SIREN_METHOD(EntryOperation, Operations);
	SIREN_METHOD_LIST(uint, CoderOffsets);
//SIREN_HEADER_METHOD_END
public:
	MemoryByteData ReadAllData(DataReadingMode mode = DataReadingMode::AlwaysCopy)const;
	const IStream* Read(FileDataType dataType = FileDataType::Binary)const;
public:
	StringRef Path() const { return mPath; }
	void SetPath(StringRef val) { mPath = val; }
	DirectoryEntry* Parent() const { return mParent; }
	void SetParent(DirectoryEntry* val) { mParent = val; }
	FileStorage* Storage() const { return mStorage; }
	void SetStorage(FileStorage* val) { mStorage = val; }

	uint ExtractedSize()const;
	void Print(const StringRef& indent)const;
	bool Extract(const StringRef& outDir)const;
	bool IsValid()const { return !MEDUSA_HAS_FLAG(mOperations, EntryOperation::Delete); }

	static HeapString ConvertToString(EntryOperation val);
	static HeapString ConvertToString(FilePermission val);


	//SIREN_HEADER_FIELD_BEGIN
protected:
	HeapString mName;
	FilePermission mPermission;
	uint mFirstBlockId;
	uint mOriginalSize;
	uint mSize;
	HeapString mSignature;
	EntryOperation mOperations;
	List<uint> mCoderOffsets;
//SIREN_HEADER_FIELD_END

	FileStorage* mStorage = nullptr;
	DirectoryEntry* mParent = nullptr;
	HeapString mPath;

};

//SIREN_HEADER_SCHEMA_BEGIN
struct FileEntry::Schema
{
	SIREN_PROPERTY(0, 0, Optional, FileEntry, HeapString, mName);
	SIREN_PROPERTY(1, 1, Optional, FileEntry, FilePermission, mPermission);
	SIREN_PROPERTY(2, 2, Optional, FileEntry, uint, mFirstBlockId);
	SIREN_PROPERTY(3, 3, Optional, FileEntry, uint, mOriginalSize);
	SIREN_PROPERTY(4, 4, Optional, FileEntry, uint, mSize);
	SIREN_PROPERTY(5, 5, Optional, FileEntry, HeapString, mSignature);
	SIREN_PROPERTY(6, 6, Optional, FileEntry, EntryOperation, mOperations);
	SIREN_PROPERTY_LIST(7, 7, Optional, FileEntry, uint, mCoderOffsets);
	SIREN_PROPERTIES_8(void,FileEntry);
};//SIREN_HEADER_SCHEMA_END

MEDUSA_END;