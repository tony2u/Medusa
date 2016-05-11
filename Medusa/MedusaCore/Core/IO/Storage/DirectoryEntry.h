// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Siren/SirenHeader.h"

//SIREN_HEADER_INCLUDE_BEGIN
#include "Core/IO/Storage/EntryOperation.h"
#include "Core/IO/Storage/DirectoryEntry.h"
#include "Core/IO/Storage/FileEntry.h"
//SIREN_HEADER_INCLUDE_END

MEDUSA_BEGIN;

class DirectoryEntry
{
	friend class FileStorage;
public:
	struct Schema;
	DirectoryEntry();
	~DirectoryEntry();
	DirectoryEntry(StringRef name, EntryOperation operation = EntryOperation::None);

	bool Initialize(FileStorage* storage, DirectoryEntry* parent = nullptr);
	bool Uninitialize();
	//SIREN_HEADER_COPY_BEGIN
public:
	DirectoryEntry(const DirectoryEntry& other)
	{
		mName = other.mName;
		mDirs = other.mDirs;
		mFiles = other.mFiles;
		mOperations = other.mOperations;
	}
	DirectoryEntry& operator=(const DirectoryEntry& other)
	{
		mName = other.mName;
		mDirs = other.mDirs;
		mFiles = other.mFiles;
		mOperations = other.mOperations;
		return *this;
	}
	//SIREN_HEADER_COPY_END
	//SIREN_HEADER_COMPARE_BEGIN
public:
	SIREN_COMMON(DirectoryEntry);
	//SIREN_HEADER_COMPARE_END
	//SIREN_HEADER_METHOD_BEGIN
public:
	SIREN_METHOD(HeapString, Name);
	SIREN_METHOD(EntryOperation, Operations);
	SIREN_METHOD_LIST(DirectoryEntry*, Dirs);
	SIREN_METHOD_LIST(FileEntry*, Files);
//SIREN_HEADER_METHOD_END
public:
	StringRef Path() const { return mPath; }
	void SetPath(StringRef val) { mPath = val; }

	DirectoryEntry* Parent() const { return mParent; }
	void SetParent(DirectoryEntry* val) { mParent = val; }

	FileStorage* Storage() const { return mStorage; }
	void SetStorage(FileStorage* val) { mStorage = val; }
	bool IsValid()const { return !MEDUSA_FLAG_HAS(mOperations, EntryOperation::Delete); }
	bool HasFile()const { return !mFiles.IsEmpty(); }
	bool HasFileRecursively()const;

public:
	const DirectoryEntry* FindDirectory(const StringRef& name)const;
	DirectoryEntry* FindDirectory(const StringRef& name);

	bool ExistsDirectory(const StringRef& name)const;
public:
	const FileEntry* FindFile(const StringRef& name)const;
	FileEntry* FindFile(const StringRef& name);

	bool ExistsFile(const StringRef& name)const;
	bool RemoveAllFiles();
	bool RemoveFile(const StringRef& name);

	FileEntry* SaveFile(const StringRef& path, const MemoryData& data);

	bool SearchFilesToRemove(const StringRef& searchPath, bool isRecursively = true);
	bool SearchFilesToExtract(const StringRef& searchPath, bool isRecursively = true, const StringRef& outDir = StringRef::Empty)const;

	bool EnumerateFiles(Delegate<void(FileEntry*)> onFile, bool isRecursively = true, bool filterValid = true)const;
	bool GetFiles(List<FileEntry*>& outFiles, bool isRecursively = true,bool filterValid=true)const;

	bool EnumerateDirs(Delegate<void(DirectoryEntry*)> onDir, bool isRecursively = true, bool filterValid = true)const;
	bool GetDirs(List<DirectoryEntry*>& outDirs, bool isRecursively = true, bool filterValid = true)const;


public:
	void Print(const StringRef& indent,bool isRoot=false)const;
	bool Extract(const StringRef& outDir,bool isRecursively=true)const;
private:
	bool RemoveDirectory(DirectoryEntry* dir);
	bool RemoveFile(FileEntry* file);

	bool RemoveAllDirectories();
	bool RemoveAll();

	FileEntry* CreateFileEntry(const StringRef& name);
	FileEntry* FindOrCreateFileEntry(const StringRef& name);
	DirectoryEntry* FindOrCreateDirectoryEntry(const StringRef& name);
	DirectoryEntry* FindOrCreateDirectory(const StringRef& name);

	bool AddDirectoryEntry(DirectoryEntry* dir);

	//SIREN_HEADER_FIELD_BEGIN
protected:
	HeapString mName;
	EntryOperation mOperations;
	List<DirectoryEntry*> mDirs;
	List<FileEntry*> mFiles;
//SIREN_HEADER_FIELD_END

	FileStorage* mStorage = nullptr;
	DirectoryEntry* mParent = nullptr;

	HeapString mPath;

	Dictionary<HeapString, DirectoryEntry*> mDirDict;
	Dictionary<HeapString, FileEntry*> mFileDict;

};

//SIREN_HEADER_SCHEMA_BEGIN
struct DirectoryEntry::Schema
{
	SIREN_FIELD(0, 0, Optional, DirectoryEntry, HeapString, mName);
	SIREN_FIELD(1, 1, Optional, DirectoryEntry, EntryOperation, mOperations);
	SIREN_FIELD_LIST(2, 2, Optional, DirectoryEntry, DirectoryEntry*, mDirs);
	SIREN_FIELD_LIST(3, 3, Optional, DirectoryEntry, FileEntry*, mFiles);
	SIREN_FIELDS_4(void,DirectoryEntry);
};
//SIREN_HEADER_SCHEMA_END

MEDUSA_END;