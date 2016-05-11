// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
//SIREN_BODY_INCLUDE_BEGIN
#include "FileStorage.h"
//SIREN_BODY_INCLUDE_END

#include "DirectoryEntry.h"
#include "FileEntry.h"
#include "Core/IO/Path.h"
#include "Core/IO/Directory.h"
#include "Core/IO/File.h"
#include "Core/IO/Stream/FileCodeWriteStream.h"
#include "Core/IO/Stream/BlockCodeReadStream.h"
#include "Core/IO/Stream/BlockCodeWriteStream.h"
#include "Core/IO/Stream/HashStream.h"

MEDUSA_BEGIN;

FileStorage::FileStorage()
{
	//SIREN_BODY_CONSTRUCT_BEGIN
//SIREN_BODY_CONSTRUCT_END
}


FileStorage::~FileStorage()
{
	//SIREN_BODY_DESTRUCT_BEGIN
//SIREN_BODY_DESTRUCT_END

	Uninitialize();
}

bool FileStorage::OnLoaded()
{
	mRootDir.Initialize(this, nullptr);
	SAFE_DELETE_DICTIONARY_VALUE(mOtherCoderChains);

	for (const auto& coderRule : mCodeRules)
	{
		CoderList coders = coderRule.Value;
		if (!mOtherCoderChains.ContainsKey(coders))
		{
			CoderChain* coderChain = new CoderChain();
			coderChain->Initialize(coders, Key());
			mOtherCoderChains.Add(coders, coderChain);
		}
	}

	return true;
}

bool FileStorage::Initialize()
{
	mRootDir.Initialize(this, nullptr);

	return true;
}

bool FileStorage::Uninitialize()
{
	mRootDir.Uninitialize();
	mCoderChain.Uninitialize();

	SAFE_DELETE_DICTIONARY_VALUE(mOtherCoderChains);
	return true;
}

bool FileStorage::RequireKey() const
{
	bool requireKey = CoderChain::RequireKey(Coders());
	RETURN_TRUE_IF_TRUE(requireKey);
	for (const auto& coderRule : mCodeRules)
	{
		if (CoderChain::RequireKey(coderRule.Value))
		{
			return true;
		}
	}

	return false;
}

void FileStorage::SetKey(const MemoryData& val)
{
	mCoderChain.SetKey(val);

	for (auto& coderChain : mOtherCoderChains)
	{
		coderChain.Value->SetKey(val);
	}
}

bool FileStorage::ValidateKey(const MemoryData& val) const
{
	return true;
}

bool FileStorage::Validate() const
{
	if (RequireKey())
	{
		return ValidateKey(Key());
	}

	return true;
}

bool FileStorage::Save()
{
	return true;
}

void FileStorage::SetCoders(uint64 val)
{
	mCoderChain.SetCoders(val);
}

bool FileStorage::AddCoderRule(const StringRef& fileExtension, CoderList coders)
{
	if (mRootDir.HasFileRecursively())
	{
		Log::FormatError("Only support add coder rule when package is empty.");
		return false;
	}

	if (!mCodeRules.TryAdd(fileExtension, coders))
	{
		CoderList oldCoders = mCodeRules.Get(fileExtension);
		Log::FormatError("Duplicate coder rule for {}:{}. Original is {}", fileExtension, coders, oldCoders);
		return false;
	}

	if (!mOtherCoderChains.ContainsKey(coders))
	{
		CoderChain* coderChain = new CoderChain();
		coderChain->Initialize(coders, Key());
		mOtherCoderChains.Add(coders, coderChain);
	}
	return true;

}

const CoderList* FileStorage::GetCoderRule(const StringRef& fileExtension)const
{
	return mCodeRules.TryGet(fileExtension);
}

CoderList FileStorage::GetFileCoders(const FileEntry& file) const
{
	StringRef ext = Path::GetExtension(file.Name());
	const CoderList* coders = GetCoderRule(ext);
	if (coders != nullptr)
	{
		return *coders;
	}
	return Coders();
}

const CoderChain* FileStorage::GetFileCoderChain(const FileEntry& file) const
{
	CoderList coders = GetFileCoders(file);
	if (coders==0)
	{
		return nullptr;
	}
	if (coders == mCoderChain.Coders())
	{
		return &mCoderChain;
	}

	return mOtherCoderChains.GetOptional(coders, nullptr);
}

#pragma region Dir


const DirectoryEntry* FileStorage::FindDirectory(const StringRef& path, const DirectoryEntry* parent /*= nullptr*/)const
{
	if (parent == nullptr)
	{
		parent = &mRootDir;
	}
	List<HeapString> paths;
	RETURN_NULL_IF_FALSE(Path::Split(path, paths));
	for (const auto& str : paths)
	{
		parent = parent->FindDirectory(str);
		RETURN_NULL_IF_NULL(parent);
	}

	return parent;
}

DirectoryEntry* FileStorage::FindDirectory(const StringRef& path, DirectoryEntry* parent /*= nullptr*/)
{
	if (parent == nullptr)
	{
		parent = &mRootDir;
	}
	List<HeapString> paths;
	RETURN_NULL_IF_FALSE(Path::Split(path, paths));
	for (const auto& str : paths)
	{
		parent = parent->FindDirectory(str);
		RETURN_NULL_IF_NULL(parent);
	}

	return parent;
}

bool FileStorage::ExistsDirectory(const StringRef& path, const DirectoryEntry* parent /*= nullptr*/) const
{
	if (parent == nullptr)
	{
		parent = &mRootDir;
	}

	return parent->ExistsDirectory(path);
}

DirectoryEntry* FileStorage::FindOrCreateDirectoryEntry(const StringRef& path, DirectoryEntry* parent /*= nullptr*/)
{
	if (Path::IsPath(path))
	{
		if (parent == nullptr)
		{
			parent = &mRootDir;
		}

		List<HeapString> paths;
		RETURN_NULL_IF_FALSE(Path::Split(path, paths));

		DirectoryEntry* dir = nullptr;
		for (const auto& str : paths)
		{
			dir = parent->FindOrCreateDirectoryEntry(str);
			parent = dir;
		}

		return dir;
	}
	else
	{
		if (parent == nullptr)
		{
			parent = &mRootDir;
		}

		DirectoryEntry* dir = parent->FindOrCreateDirectoryEntry(path);

		return dir;
	}
}

DirectoryEntry* FileStorage::FindOrCreateDirectory(const StringRef& path, DirectoryEntry* parent /*= nullptr*/)
{
	if (Path::IsPath(path))
	{
		if (parent == nullptr)
		{
			parent = &mRootDir;
		}

		List<HeapString> paths;
		RETURN_NULL_IF_FALSE(Path::Split(path, paths));

		DirectoryEntry* dir = nullptr;
		for (const auto& str : paths)
		{
			dir = parent->FindOrCreateDirectory(str);
			parent = dir;
		}

		return dir;
	}
	else
	{
		if (parent == nullptr)
		{
			parent = &mRootDir;
		}

		DirectoryEntry* dir = parent->FindOrCreateDirectory(path);

		return dir;
	}
}
bool FileStorage::RemoveDirectory(const StringRef& path, DirectoryEntry* parent /*= nullptr*/)
{
	return RemoveDirectory(const_cast<DirectoryEntry*>(FindDirectory(path, parent)));
}


bool FileStorage::RemoveDirectory(DirectoryEntry* dir)
{
	RETURN_FALSE_IF_NULL(dir);
#ifdef MEDUSA_SAFE_CHECK
	if (dir->Storage() != this)
	{
		Log::AssertFailed("Invalid operate dir on different storage.");
		return false;
	}
	if (dir == &mRootDir)
	{
		Log::AssertFailed("Cannot remove root dir.");
		return false;
	}
#endif
	RETURN_FALSE_IF_FALSE(RemoveAllFiles(*dir));
	RETURN_FALSE_IF_FALSE(RemoveAllDirectories(*dir));

	RETURN_FALSE_IF_FALSE(OnRemoveDirectory(*dir));

	auto* parent = dir->Parent();
	parent->RemoveDirectory(dir);
	return true;
}

bool FileStorage::RemoveAllDirectories(const StringRef& path, DirectoryEntry* parent /*= nullptr*/)
{
	parent = FindDirectory(path, parent);
	RETURN_FALSE_IF_NULL(parent);
	return RemoveAllDirectories(*parent);
}


bool FileStorage::RemoveAllDirectories(DirectoryEntry& parent)
{
#ifdef MEDUSA_SAFE_CHECK
	if (parent.Storage() != this)
	{
		Log::AssertFailed("Invalid operate on different storage.");
		return false;
	}
#endif
	auto dirsCopy = parent.Dirs();
	for (auto subDir : dirsCopy)
	{
		RETURN_FALSE_IF_FALSE(RemoveDirectory(subDir));
	}
	return true;
}

bool FileStorage::RemoveAll(DirectoryEntry& parent)
{
	bool ret = RemoveAllFiles(parent);
	ret &= RemoveAllDirectories(parent);
	return ret;
}

bool FileStorage::RemoveAll(const StringRef& path, DirectoryEntry* parent /*= nullptr*/)
{
	parent = FindDirectory(path, parent);
	RETURN_FALSE_IF_NULL(parent);
	return RemoveAll(*parent);
}

#pragma endregion Dir
#pragma region File

const FileEntry* FileStorage::FindFile(const StringRef& path, const DirectoryEntry* parent/* = nullptr*/) const
{
	if (parent == nullptr)
	{
		parent = &mRootDir;
	}

	if (Path::IsPath(path))
	{
		List<HeapString> paths;
		RETURN_NULL_IF_FALSE(Path::Split(path, paths));

		const DirectoryEntry* dir = parent;
		for (uint i = 0; i < paths.Count() - 1; ++i)
		{
			dir = dir->FindDirectory(paths[i]);
			RETURN_NULL_IF_NULL(dir);
		}

		return dir->FindFile(paths.Last());
	}
	else
	{
		return parent->FindFile(path);
	}
}

FileEntry* FileStorage::FindFile(const StringRef& path, DirectoryEntry* parent /*= nullptr*/)
{
	if (parent == nullptr)
	{
		parent = &mRootDir;
	}

	if (Path::IsPath(path))
	{
		List<HeapString> paths;
		RETURN_NULL_IF_FALSE(Path::Split(path, paths));

		DirectoryEntry* dir = parent;
		for (uint i = 0; i < paths.Count() - 1; ++i)
		{
			dir = dir->FindDirectory(paths[i]);
			RETURN_NULL_IF_NULL(dir);
		}

		return dir->FindFile(paths.Last());
	}
	else
	{
		return parent->FindFile(path);
	}
}


MemoryData FileStorage::ReadAllData(const FileEntry& fileEntry, DataReadingMode mode /*= DataReadingMode::AlwaysCopy*/) const
{
	const IStream* stream = ReadFileHelper(fileEntry, FileDataType::Binary);
	if (stream == nullptr)
	{
		return MemoryData::Empty;
	}
	MemoryData data = stream->ReadToEnd(mode);
	SAFE_RELEASE(stream);
	return data;
}

MemoryData FileStorage::ReadAllData(const StringRef& path, DirectoryEntry* parent /*= nullptr*/, DataReadingMode mode /*= DataReadingMode::AlwaysCopy*/) const
{
	const FileEntry* fileEntry = FindFile(path, parent);
	if (fileEntry == nullptr)
	{
		return MemoryData::Empty;
	}

	return ReadAllData(*fileEntry, mode);
}

FileEntry* FileStorage::SaveFile(const MemoryData& data, const StringRef& path /*= StringRef::Empty*/, DirectoryEntry* parent /*= nullptr*/, DataReadingMode mode /*= DataReadingMode::AlwaysCopy*/)
{
	FileEntry* fileEntry = FindOrCreateFileEntry(path, parent);

	IStream* stream = WriteFileHelper(*fileEntry, FileOpenMode::DestoryWriteOrCreate, FileDataType::Binary);
	if (stream == nullptr)
	{
		RemoveFile(fileEntry);	//remove new created file entry
		return nullptr;
	}

	stream->WriteData(data, mode);
	SAFE_RELEASE(stream);
	return fileEntry;
}

FileEntry* FileStorage::SaveFile(const IStream& sourceStream, const StringRef& path /*= StringRef::Empty*/, DirectoryEntry* parent /*= nullptr*/)
{
	FileEntry* fileEntry = FindOrCreateFileEntry(path, parent);
	IStream* stream = WriteFileHelper(*fileEntry, FileOpenMode::DestoryWriteOrCreate, FileDataType::Binary);
	if (stream == nullptr)
	{
		RemoveFile(fileEntry);	//remove back file
		return nullptr;
	}

	sourceStream.CopyTo(*stream);
	SAFE_RELEASE(stream);

	return fileEntry;
}

bool FileStorage::SaveFile(FileEntry& fileEntry, const IStream& sourceStream)
{
	IStream* stream = WriteFileHelper(fileEntry, FileOpenMode::DestoryWriteOrCreate, FileDataType::Binary);
	RETURN_FALSE_IF_NULL(stream);
	sourceStream.CopyTo(*stream);
	SAFE_RELEASE(stream);

	return true;
}

bool FileStorage::SearchFilesToAdd(const StringRef& searchPath, DirectoryEntry* destDir /*= nullptr*/, bool recursively /*= true*/, bool isReadonly /*= false*/, bool overwrite /*= true*/, bool deleteOriginalFile /*= false*/)
{
	SearchDirectoriesToAdd(searchPath, destDir, recursively);
	if (destDir == nullptr)
	{
		destDir = &mRootDir;
	}
	List<HeapString> fileList;
	Directory::SearchFiles(searchPath, fileList, recursively);
	HeapString searchDir = Path::GetDirectory(searchPath);

	for (const auto& file : fileList)
	{
		auto fs = File::OpenBinaryReader(file);
		if (!fs)
		{
			Log::FormatError("Cannot read file:{}", file);
			return false;
		}


		StringRef destFile;
		if (searchDir.IsEmpty())
		{
			destFile = file;
		}
		else
		{
			destFile = file.ToString().SubString(searchDir.Length() + 1);	//+1 to skip '/'
		}
		bool overwriteFile = false;
		if (overwrite)
		{
			if (RemoveFile(destFile))
			{
				overwriteFile = true;
			}
		}
		else
		{
			if (ExistsFile(destFile))
			{
				Log::FormatInfo("NOT overwrite file:{}", destFile);
				continue;
			}
		}

		auto* fileEntry = SaveFile(*fs, destFile, destDir);
		fileEntry->SetPermission(isReadonly ? FilePermission::Read : FilePermission::All);
		Log::FormatInfo("Add file:{} to {}", destFile, file);

		if (overwriteFile)
		{
			Log::FormatInfo("Overwrite file:{}", destFile);
		}
	}

	if (deleteOriginalFile)
	{
		for (const auto& file : fileList)
		{
			File::Delete(file);
		}
	}

	return true;
}

bool FileStorage::SearchFilesToRemove(const StringRef& searchPath, bool isRecursively /*= true*/)
{
	if (Path::IsDirectory(searchPath))
	{
		return RemoveDirectory(searchPath);
	}
	else
	{
		if (Path::HasSearchPattern(searchPath))
		{
			List<HeapString> outFiles;
			FileInfo fileInfo(searchPath);
			auto dir = fileInfo.Directory();
			auto* dirEntry = FindDirectory(dir);
			RETURN_FALSE_IF_NULL(dirEntry);
			return dirEntry->SearchFilesToRemove(fileInfo.FullName(), isRecursively);
		}
		else
		{
			return RemoveFile(searchPath);
		}
	}
}

bool FileStorage::SearchDirectoriesToAdd(const StringRef& searchPath, DirectoryEntry* destDir /*= nullptr*/, bool recursively /*= true*/)
{
	if (destDir == nullptr)
	{
		destDir = &mRootDir;
	}
	List<HeapString> dirList;
	Directory::SearchDirectories(searchPath, dirList, recursively);
	HeapString searchDir = Path::GetDirectory(searchPath);

	for (auto& dir : dirList)
	{
		StringRef subDir;
		if (searchDir.IsEmpty())
		{
			subDir = dir;
		}
		else
		{
			subDir = dir.ToString().SubString(searchDir.Length() + 1);	//+1 to skip '/'
		}

		auto* dirEntry = FindOrCreateDirectoryEntry(subDir, destDir);
		if (dirEntry == nullptr)
		{
			Log::FormatError("Cannot create dir:{}", subDir);
			return false;
		}
		Log::FormatInfo("Add Dir:{}", dir);

	}
	return true;
}

bool FileStorage::SearchFilesToExtract(const StringRef& searchPath, bool isRecursively /*= true*/, const StringRef& outDir /*= StringRef::Empty*/)
{
	if (Path::IsDirectory(searchPath))
	{
		return ExtractDirectory(searchPath, nullptr, isRecursively, outDir);
	}
	else
	{
		if (Path::HasSearchPattern(searchPath))
		{
			List<HeapString> outFiles;
			FileInfo fileInfo(searchPath);
			auto dir = fileInfo.Directory();
			auto* dirEntry = FindDirectory(dir);
			RETURN_FALSE_IF_NULL(dirEntry);
			return dirEntry->SearchFilesToExtract(fileInfo.FullName(), isRecursively, outDir);
		}
		else
		{
			return ExtractFile(searchPath, nullptr, outDir);
		}
	}
}

bool FileStorage::ExtractFile(const StringRef& path, DirectoryEntry* parent /*= nullptr*/, const StringRef& outDir /*= StringRef::Empty*/) const
{
	auto* fileEntry = FindFile(path, parent);
	RETURN_FALSE_IF_NULL(fileEntry);
	return fileEntry->Extract(outDir);
}


bool FileStorage::ExtractDirectory(const StringRef& path, DirectoryEntry* parent /*= nullptr*/, bool isRecursively /*= true*/, const StringRef& outDir /*= StringRef::Empty*/) const
{
	auto* dirEntry = FindDirectory(path, parent);
	return dirEntry->Extract(outDir, isRecursively);
}

bool FileStorage::ExtractAll(const StringRef& outDir /*= StringRef::Empty*/) const
{
	return mRootDir.Extract(outDir);
}


bool FileStorage::ExistsFile(const StringRef& path) const
{
	return FindFile(path) != nullptr;
}

bool FileStorage::RemoveFile(const StringRef& path, DirectoryEntry* parent /*= nullptr*/)
{
	return RemoveFile(FindFile(path, parent));
}

bool FileStorage::RemoveFile(FileEntry* file)
{
	RETURN_FALSE_IF_NULL(file);
	RETURN_FALSE_IF_NULL(file->Parent());

#ifdef MEDUSA_SAFE_CHECK
	if (file->Storage() != this)
	{
		Log::AssertFailed("Invalid operate file on different storage.");
		return false;
	}
#endif

	RETURN_FALSE_IF_FALSE(OnRemoveFile(*file));

	auto* parent = file->Parent();
	return parent->RemoveFile(file);
}


bool FileStorage::RemoveAllFiles(const StringRef& path)
{
	auto* parent = FindDirectory(path);
	RETURN_FALSE_IF_NULL(parent);
	return RemoveAllFiles(*parent);
}

bool FileStorage::RemoveAllFiles(DirectoryEntry& parent)
{
#ifdef MEDUSA_SAFE_CHECK
	if (parent.Storage() != this)
	{
		Log::AssertFailed("Invalid operate on different storage.");
		return false;
	}
#endif
	auto filesCopy = parent.Files();
	for (auto file : filesCopy)
	{
		RETURN_FALSE_IF_FALSE(RemoveFile(file));
	}
	return true;
}


FileEntry* FileStorage::CreateFileEntry(const StringRef& path, DirectoryEntry* parent /*= nullptr*/)
{
	if (parent == nullptr)
	{
		parent = &mRootDir;
	}

	FileEntry* fileEntry = nullptr;
	if (Path::IsPath(path))
	{
		List<HeapString> paths;
		RETURN_NULL_IF_FALSE(Path::Split(path, paths));

		DirectoryEntry* dir = parent;
		for (uint i = 0; i < paths.Count() - 1; ++i)
		{
			dir = dir->FindOrCreateDirectoryEntry(paths[i]);
			RETURN_NULL_IF_NULL(dir);
		}

		fileEntry = dir->CreateFileEntry(paths.Last());
	}
	else
	{
		fileEntry = parent->CreateFileEntry(path);
	}

	return fileEntry;
}

FileEntry* FileStorage::FindOrCreateFileEntry(const StringRef& path, DirectoryEntry* parent /*= nullptr*/)
{
	if (parent == nullptr)
	{
		parent = &mRootDir;
	}

	FileEntry* fileEntry = nullptr;
	if (Path::IsPath(path))
	{
		List<HeapString> paths;
		RETURN_NULL_IF_FALSE(Path::Split(path, paths));

		DirectoryEntry* dir = parent;
		for (uint i = 0; i < paths.Count() - 1; ++i)
		{
			dir = dir->FindOrCreateDirectoryEntry(paths[i]);
			RETURN_NULL_IF_NULL(dir);
		}

		fileEntry = dir->FindOrCreateFileEntry(paths.Last());
	}
	else
	{
		fileEntry = parent->FindOrCreateFileEntry(path);
	}

	return fileEntry;
}

const IStream* FileStorage::ReadFile(const StringRef& path, DirectoryEntry* parent /*= nullptr*/, FileDataType dataType /*= FileDataType::Binary*/)const
{
	const FileEntry* fileEntry = FindFile(path, parent);
	RETURN_NULL_IF_NULL(fileEntry);

	return ReadFileHelper(*fileEntry, dataType);
}

IStream* FileStorage::WriteFile(const StringRef& path, DirectoryEntry* parent /*= nullptr*/, FileOpenMode openMode /*= FileOpenMode::DestoryWriteOrCreate*/, FileDataType dataType /*= FileDataType::Binary*/)
{
	RETURN_NULL_IF_TRUE(IsReadOnly());

	FileEntry* fileEntry = FindFile(path, parent);
	CoderList coders = GetFileCoders(*fileEntry);
	if (fileEntry == nullptr)
	{
		//not exists
		switch (openMode)
		{
		case FileOpenMode::ReadOnly:
		case FileOpenMode::ReadWrite:
			return nullptr;
		case FileOpenMode::DestoryWriteOrCreate:
			//create file to only write
			break;
		case FileOpenMode::DestoryReadWriteOrCreate:
		case FileOpenMode::AppendReadWriteClearEOFOrCreate:
		case FileOpenMode::AppendWriteKeepEOFOrCreate:
			if (coders != 0)
			{
				Log::AssertFailedFormat("Not support read & write file with coder:{}", coders);
				return nullptr;
			}
			////create file to read write
			break;
		default:
			break;
		}

		fileEntry = FindOrCreateFileEntry(path, parent);
		IStream* stream = WriteFileHelper(*fileEntry, openMode, dataType);
		if (stream == nullptr)
		{
			RemoveFile(fileEntry);	//remove back file
		}
		return stream;

	}
	else
	{
		//exists
		switch (openMode)
		{
		case FileOpenMode::ReadOnly:
			break;
		case FileOpenMode::ReadWrite:
			if (fileEntry->IsReadonly())
			{
				Log::AssertFailedFormat("Cannot read & write readonly file:{}", path);
				return nullptr;
			}

			if (coders != 0)
			{
				Log::AssertFailedFormat("Not support read & write file with coder:{}", coders);
				return nullptr;
			}
			break;
		case FileOpenMode::DestoryWriteOrCreate:
			//use new attribute

			break;
		case FileOpenMode::AppendWriteKeepEOFOrCreate:
			if (coders != 0)
			{
				Log::AssertFailedFormat("Cannot append & write readonly file:{}", path);
				return nullptr;
			}

			break;
		case FileOpenMode::DestoryReadWriteOrCreate:
			RETURN_NULL_IF_TRUE(IsReadOnly());
			if (coders != 0)
			{
				Log::AssertFailedFormat("Not support read & write file with coder:{}", coders);
				return nullptr;
			}
			break;
		case FileOpenMode::AppendReadWriteClearEOFOrCreate:
			if (fileEntry->IsReadonly())
			{
				Log::AssertFailedFormat("Cannot read & write readonly file:{}", path);
				return nullptr;
			}

			if (GetFileCoders(*fileEntry))
			{
				Log::AssertFailedFormat("Not support read & write file with coder:{}", coders);
				return nullptr;
			}
			break;
		default:
			break;
		}

		IStream* stream = WriteFileHelper(*fileEntry, openMode, dataType);
		RETURN_NULL_IF_NULL(stream);

		return stream;
	}
}

const IStream* FileStorage::ReadFileHelper(const FileEntry& file, FileDataType dataType /*= FileDataType::Binary*/) const
{
	const IStream* resultStream = OnReadFile(file, dataType);
	RETURN_NULL_IF_NULL(resultStream);

	const CoderChain* coderChain = GetFileCoderChain(file);
	if (coderChain != nullptr)
	{
		if (IsWholeFileCoding())
		{
			MemoryStream* tempStream = new MemoryStream(file.OriginalSize(), false);
			coderChain->Decode(*resultStream, *tempStream);
			const auto data = tempStream->CurrentBuffer();
			SAFE_DELETE(tempStream);
			MemoryStream* outputStream = new MemoryStream(data);

			const IStream* tempStream2 = resultStream;
			resultStream = outputStream;
			tempStream2->Release();
		}
		else
		{
			const IStream* tempStream = resultStream;
			resultStream = new BlockCodeReadStream(*resultStream, BlockSize(), *coderChain, file);
			tempStream->Release();

		}
	}

	return resultStream;
}

IStream* FileStorage::WriteFileHelper(FileEntry& file, FileOpenMode openMode /*= FileOpenMode::ReadOnly*/, FileDataType dataType /*= FileDataType::Binary*/)
{
	IStream* resultStream = OnWriteFile(file, openMode, dataType);;

	const CoderChain* coderChain = GetFileCoderChain(file);
	if (coderChain != nullptr)
	{
		if (IsWholeFileCoding())
		{
			IStream* tempStream = resultStream;
			resultStream = new FileCodeWriteStream(*resultStream, *coderChain, file);
			tempStream->Release();
		}
		else
		{
			IStream* tempStream = resultStream;
			resultStream = new BlockCodeWriteStream(*resultStream, BlockSize(), *coderChain, file);
			tempStream->Release();
		}
	}

	if (Hasher() != HasherType::None)
	{
		IStream* tempStream = resultStream;
		resultStream = new HashStream(*resultStream, Hasher(), [&file](StringRef result) {file.SetSignature(result); });
		tempStream->Release();

	}

	return resultStream;
}


#pragma endregion File

//SIREN_BODY_METADATA_BEGIN
SIREN_METADATA(FileStorage, 11);
SIREN_FIELD_METADATA_STRUCT(0, FileStorage, RootDir, 7);
SIREN_FIELD_METADATA_STRUCT(1, FileStorage, CodeRules, 9);
//SIREN_BODY_METADATA_END

MEDUSA_END;