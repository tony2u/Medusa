// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Siren/SirenHeader.h"

//SIREN_HEADER_INCLUDE_BEGIN
#include "Core/IO/Storage/DirectoryEntry.h"
//SIREN_HEADER_INCLUDE_END
#include "Core/Memory/MemoryData.h"
#include "Core/Pattern/Singleton.h"
#include "Core/String/HeapString.h"
#include "Core/Log/Log.h"
#include "Core/Siren/Code/SirenCoderType.h"
#include "Core/Coder/CoderChain.h"
#include "Core/IO/Storage/FileAttribute.h"

MEDUSA_BEGIN;

class FileStorage
{
	friend class DirectoryEntry;
	friend class FileEntry;
public:
	struct Schema;
	FileStorage();
	~FileStorage();
	const static uint32 DefaultBlockSize = 1024;	//1K

	//SIREN_HEADER_COPY_BEGIN
public:
	FileStorage(const FileStorage& other)
	{
		mRootDir = other.mRootDir;
	}
	FileStorage& operator=(const FileStorage& other)
	{
		mRootDir = other.mRootDir;
		return *this;
	}
	//SIREN_HEADER_COPY_END
	//SIREN_HEADER_COMPARE_BEGIN
public:
	SIREN_COMMON(FileStorage);
	//SIREN_HEADER_COMPARE_END
	//SIREN_HEADER_METHOD_BEGIN
public:
	SIREN_METHOD(DirectoryEntry, RootDir);
	SIREN_METHOD_DICTIONARY(HeapString, uint64, CodeRules);
//SIREN_HEADER_METHOD_END
public:
	virtual uint BlockSize()const = 0;
	virtual void SetBlockSize(uint val) = 0;
	virtual uint64 Coders() const = 0;
	virtual void SetCoders(uint64 val);
	virtual HasherType Hasher() const = 0;
	virtual void SetHasher(HasherType val) = 0;
public:
	virtual bool Initialize();
	virtual bool Uninitialize();
	virtual bool IsReadOnly()const { return false; }
	virtual bool IsWholeFileCoding()const { return false; }

	bool HasCoders()const { return Coders() != 0; }

	bool RequireKey()const;
	const MemoryData& Key() const { return mCoderChain.Key(); }
	virtual void SetKey(const MemoryData& val);
	virtual bool ValidateKey(const MemoryData& val)const;
	virtual bool Validate()const;

	virtual bool Save();

	bool AddCoderRule(const StringRef& fileExtension, CoderList coders);
	const CoderList* GetCoderRule(const StringRef& fileExtension)const;
	CoderList GetFileCoders(const FileEntry& file)const;
	const CoderChain* GetFileCoderChain(const FileEntry& file)const;


protected:
	virtual bool OnLoaded();
#pragma region Dir
public:
	const DirectoryEntry* FindDirectory(const StringRef& path, const DirectoryEntry* parent = nullptr)const;
	DirectoryEntry* FindDirectory(const StringRef& path, DirectoryEntry* parent = nullptr);

	bool ExistsDirectory(const StringRef& path, const DirectoryEntry* parent = nullptr)const;

	
	bool RemoveDirectory(const StringRef& path, DirectoryEntry* parent = nullptr);
	bool RemoveDirectory(DirectoryEntry* dir);

	bool RemoveAllDirectories(const StringRef& path, DirectoryEntry* parent = nullptr);
	bool RemoveAllDirectories(DirectoryEntry& parent);

	bool RemoveAll(const StringRef& path, DirectoryEntry* parent = nullptr);
	bool RemoveAll(DirectoryEntry& parent);

	DirectoryEntry* FindOrCreateDirectoryEntry(const StringRef& path, DirectoryEntry* parent = nullptr);
	DirectoryEntry* FindOrCreateDirectory(const StringRef& path, DirectoryEntry* parent = nullptr);

#pragma endregion Dir
#pragma region File
public:
	const FileEntry* FindFile(const StringRef& path, const DirectoryEntry* parent = nullptr)const;
	FileEntry* FindFile(const StringRef& path, DirectoryEntry* parent = nullptr);

	bool ExistsFile(const StringRef& path)const;


	bool RemoveFile(const StringRef& path, DirectoryEntry* parent = nullptr);
	bool RemoveFile(FileEntry* file);
	bool RemoveAllFiles(const StringRef& path);
	bool RemoveAllFiles(DirectoryEntry& parent);

	FileEntry* CreateFileEntry(const StringRef& path, DirectoryEntry* parent = nullptr);
	FileEntry* FindOrCreateFileEntry(const StringRef& path, DirectoryEntry* parent = nullptr);

	const IStream* ReadFile(const StringRef& path, DirectoryEntry* parent = nullptr, FileDataType dataType = FileDataType::Binary)const;
	IStream* WriteFile(const StringRef& path, DirectoryEntry* parent = nullptr, FileOpenMode openMode = FileOpenMode::DestoryWriteOrCreate, FileDataType dataType = FileDataType::Binary);

	MemoryData ReadAllData(const StringRef& path, DirectoryEntry* parent = nullptr, DataReadingMode mode = DataReadingMode::AlwaysCopy)const;
	MemoryData ReadAllData(const FileEntry& fileEntry, DataReadingMode mode = DataReadingMode::AlwaysCopy)const;


	FileEntry* SaveFile(const MemoryData& data, const StringRef& path = StringRef::Empty, DirectoryEntry* parent = nullptr, DataReadingMode mode = DataReadingMode::AlwaysCopy);
	FileEntry* SaveFile(const IStream& sourceStream, const StringRef& path = StringRef::Empty, DirectoryEntry* parent = nullptr);
	bool SaveFile(FileEntry& fileEntry,const IStream& sourceStream);

	bool SearchFilesToAdd(const StringRef& searchPath, DirectoryEntry* destDir = nullptr, bool recursively = true, bool isReadonly = false, bool overwrite = true, bool deleteOriginalFile = false);
	bool SearchFilesToRemove(const StringRef& searchPath, bool isRecursively = true);
	bool SearchDirectoriesToAdd(const StringRef& searchPath, DirectoryEntry* destDir = nullptr, bool recursively = true);
	bool SearchFilesToExtract(const StringRef& searchPath, bool isRecursively = true, const StringRef& outDir = StringRef::Empty);
public:
	bool ExtractFile(const StringRef& path, DirectoryEntry* parent = nullptr, const StringRef& outDir = StringRef::Empty)const;

	bool ExtractDirectory(const StringRef& path, DirectoryEntry* parent = nullptr, bool isRecursively = true, const StringRef& outDir = StringRef::Empty)const;
	bool ExtractAll(const StringRef& outDir = StringRef::Empty)const;
protected:
	const IStream* ReadFileHelper(const FileEntry& file, FileDataType dataType = FileDataType::Binary)const;
	IStream* WriteFileHelper(FileEntry& file, FileOpenMode openMode = FileOpenMode::ReadOnly, FileDataType dataType = FileDataType::Binary);

	virtual bool OnCreateDirectory(const StringRef& dir) { return true; }
	virtual bool OnRemoveDirectory(DirectoryEntry& dir) { return true; }
	virtual const IStream* OnReadFile(const FileEntry& file, FileDataType dataType = FileDataType::Binary)const { return nullptr; }
	virtual IStream* OnWriteFile(FileEntry& file, FileOpenMode openMode = FileOpenMode::ReadOnly, FileDataType dataType = FileDataType::Binary) { return nullptr; }
	virtual bool OnRemoveFile(FileEntry& file) { return true; }

	virtual void OnFileAdded(FileEntry& file) {}
	virtual void OnFileRemoved(FileEntry& file) {}

#pragma endregion File

	//SIREN_HEADER_FIELD_BEGIN
protected:
	DirectoryEntry mRootDir;
	Dictionary<HeapString, uint64> mCodeRules;
//SIREN_HEADER_FIELD_END

	CoderChain mCoderChain;
	Dictionary<uint64, CoderChain*> mOtherCoderChains;
};

//SIREN_HEADER_SCHEMA_BEGIN
struct FileStorage::Schema
{
	SIREN_FIELD(0, 0, Required, FileStorage, DirectoryEntry, mRootDir);
	SIREN_FIELD_DICTIONARY(1, 1, Optional, FileStorage, HeapString, uint64, mCodeRules);
	SIREN_FIELDS_2(void,FileStorage);
};
//SIREN_HEADER_SCHEMA_END

MEDUSA_END;