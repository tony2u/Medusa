// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
//SIREN_BODY_INCLUDE_BEGIN
#include "DirectoryEntry.h"
//SIREN_BODY_INCLUDE_END

#include "FileEntry.h"
#include "FileStorage.h"
#include "Core/IO/Path.h"
#include "Core/String/StringParser.h"
#include "Core/IO/FileId.h"
#include "Core/IO/Directory.h"

MEDUSA_BEGIN;

DirectoryEntry::DirectoryEntry()
{
	//SIREN_BODY_CONSTRUCT_BEGIN
	mOperations = (EntryOperation)0;
//SIREN_BODY_CONSTRUCT_END
}

DirectoryEntry::DirectoryEntry(StringRef name, EntryOperation operation/*=EntryOperation::None*/)
	:mName(name), mOperations(operation)
{

}

DirectoryEntry::~DirectoryEntry()
{
	//SIREN_BODY_DESTRUCT_BEGIN
	SAFE_DELETE_COLLECTION(mDirs);
	SAFE_DELETE_COLLECTION(mFiles);
//SIREN_BODY_DESTRUCT_END
}

bool DirectoryEntry::Initialize(FileStorage* storage, DirectoryEntry* parent /*= nullptr*/)
{
	mStorage = storage;
	mParent = parent;
	mPath = mParent != nullptr ? Path::CombineNoChecks(mParent->Path(), mName) : mName;


	uintp index = 0;
	for (DirectoryEntry* dir : mDirs)
	{
		RETURN_FALSE_IF_FALSE(dir->Initialize(storage, this));
		mDirDict.Add(dir->Name(), dir);
	}

	index = 0;
	for (FileEntry* file : mFiles)
	{
		RETURN_FALSE_IF_FALSE(file->Initialize(storage, this));
		mFileDict.Add(file->Name(), file);
	}

	return true;
}



bool DirectoryEntry::Uninitialize()
{
	for (DirectoryEntry* dir : mDirs)
	{
		dir->Uninitialize();
	}

	SAFE_DELETE_COLLECTION(mDirs);
	SAFE_DELETE_COLLECTION(mFiles);
	mDirDict.Clear();
	mFileDict.Clear();

	return true;
}

bool DirectoryEntry::HasFileRecursively() const
{
	RETURN_TRUE_IF(HasFile());

	for (DirectoryEntry* dir : mDirs)
	{
		RETURN_TRUE_IF(dir->HasFileRecursively())
	}
	return false;
}

const DirectoryEntry* DirectoryEntry::FindDirectory(const StringRef& name) const
{
	return mDirDict.TryGetValueWithFailed(name, nullptr);
}

DirectoryEntry* DirectoryEntry::FindDirectory(const StringRef& name)
{
	return mDirDict.TryGetValueWithFailed(name, nullptr);
}

bool DirectoryEntry::ExistsDirectory(const StringRef& name) const
{
	return FindDirectory(name) != nullptr;
}


void DirectoryEntry::Print(const StringRef& indent, bool isRoot /*= false*/) const
{
	if (isRoot)
	{
		for (auto* file : mFiles)
		{
			file->Print(StringRef::Empty);
		}

		for (auto* dir : mDirs)
		{
			dir->Print(StringRef::Empty);
		}
	}
	else
	{
		auto opStr = FileEntry::ConvertToString(mOperations);
		Log::FormatInfo("{}{}\t{}", indent, mName, opStr);
		HeapString newIndent = indent;
		newIndent += "\t";

		for (auto* file : mFiles)
		{
			file->Print(newIndent);
		}

		for (auto* dir : mDirs)
		{
			dir->Print(newIndent);
		}
	}
	
}

bool DirectoryEntry::Extract(const StringRef& outDir, bool isRecursively /*= true*/) const
{
	RETURN_FALSE_IF_FALSE(IsValid());
	//create self dir
	HeapString selfDir = Path::Combine(outDir, mPath);
	if (!Directory::CreateDirRecursively(selfDir))
	{
		Log::FormatError("Cannot create dir:{}", selfDir);
		return false;
	}



	for (auto* file : mFiles)
	{
		RETURN_FALSE_IF_FALSE(file->Extract(outDir));
	}

	if (isRecursively)
	{
		for (auto* dir : mDirs)
		{
			RETURN_FALSE_IF_FALSE(dir->Extract(outDir));
		}
	}

	return true;
}

bool DirectoryEntry::RemoveDirectory(DirectoryEntry* dir)
{
	RETURN_FALSE_IF_FALSE(IsValid());
	if (mDirDict.RemoveKey(dir->Name()))
	{
		mDirs.Remove(dir);
		delete dir;
		return true;
	}
	return false;
}

bool DirectoryEntry::RemoveFile(FileEntry* file)
{
	RETURN_FALSE_IF_FALSE(IsValid());
	if (mFileDict.RemoveKey(file->Name()))
	{
		mFiles.Remove(file);
		if (mStorage != nullptr)
		{
			mStorage->OnFileRemoved(*file);
		}
		delete file;
		return true;
	}
	return false;
}

bool DirectoryEntry::RemoveFile(const StringRef& name)
{
	RETURN_FALSE_IF_FALSE(IsValid());
	auto fileEntry = FindFile(name);
	RETURN_FALSE_IF_NULL(fileEntry);

	return mStorage->RemoveFile(fileEntry);
}

bool DirectoryEntry::RemoveAll()
{
	RETURN_FALSE_IF_FALSE(IsValid());
	bool ret = RemoveAllFiles();
	ret &= RemoveAllDirectories();
	return ret;
}

FileEntry* DirectoryEntry::CreateFileEntry(const StringRef& name)
{
	RETURN_NULL_IF_FALSE(IsValid());

	FileEntry* file = new FileEntry(0, name);
	file->Initialize(mStorage, this);
	mFiles.Add(file);
	mFileDict.Add(name, file);

	if (mStorage != nullptr)
	{
		mStorage->OnFileAdded(*file);
	}

	return file;
}

FileEntry* DirectoryEntry::FindOrCreateFileEntry(const StringRef& name)
{
	RETURN_NULL_IF_FALSE(IsValid());
	FileEntry* file = mFileDict.TryGetValueWithFailed(name, nullptr);
	RETURN_SELF_IF_NOT_NULL(file);

	file = new FileEntry(0, name);
	file->Initialize(mStorage, this);
	mFiles.Add(file);
	mFileDict.Add(name, file);
	
	if (mStorage!=nullptr)
	{
		mStorage->OnFileAdded(*file);
	}

	return file;
}

DirectoryEntry* DirectoryEntry::FindOrCreateDirectoryEntry(const StringRef& name)
{
	RETURN_NULL_IF_FALSE(IsValid());
	DirectoryEntry* dirEntry = mDirDict.TryGetValueWithFailed(name, nullptr);
	RETURN_SELF_IF_NOT_NULL(dirEntry);

	dirEntry = new DirectoryEntry(name);
	dirEntry->Initialize(mStorage, this);
	AddDirectoryEntry(dirEntry);
	return dirEntry;

}

DirectoryEntry* DirectoryEntry::FindOrCreateDirectory(const StringRef& name)
{
	RETURN_NULL_IF_FALSE(IsValid());
	DirectoryEntry* dirEntry = mDirDict.TryGetValueWithFailed(name, nullptr);
	RETURN_SELF_IF_NOT_NULL(dirEntry);

	if (mStorage->OnCreateDirectory(Path::Combine(Path(), name)))
	{
		dirEntry = new DirectoryEntry(name);
		dirEntry->Initialize(mStorage, this);
		AddDirectoryEntry(dirEntry);
	}
	
	return dirEntry;
}

bool DirectoryEntry::AddDirectoryEntry(DirectoryEntry* dir)
{
	mDirs.Add(dir);
	mDirDict.Add(dir->Name(), dir);
	return true;
}

bool DirectoryEntry::SearchFilesToRemove(const StringRef& searchPath, bool isRecursively /*= true*/)
{
	RETURN_FALSE_IF_FALSE(IsValid());
	if (Path::HasSearchPattern(searchPath))
	{
		if (searchPath == "*.*")
		{
			return RemoveAll();
		}
		else if (searchPath.BeginWith("*."))
		{
			StringRef searchExt = searchPath.SubString(1);
			List<FileEntry*> resultFiles;
			for (auto* file : mFiles)
			{
				StringRef ext = Path::GetExtension(file->Name());
				if (ext == searchExt)
				{
					resultFiles.Add(file);
				}
			}

			for (auto* file:resultFiles)
			{
				mStorage->RemoveFile(file);
			}
			if (isRecursively)
			{
				for (auto* dir : mDirs)
				{
					RETURN_FALSE_IF_FALSE(dir->SearchFilesToRemove(searchPath, isRecursively));
				}
			}
			
			return !resultFiles.IsEmpty();
		}
		else if (searchPath.EndWith(".*"))
		{
			HeapString searchName= Path::GetFileNameWithoutExtension(searchPath);

			List<FileEntry*> resultFiles;
			for (auto* file : mFiles)
			{
				StringRef name = Path::GetFileNameWithoutExtension(file->Name());
				if (name == searchName)
				{
					resultFiles.Add(file);
				}
			}

			for (auto* file : resultFiles)
			{
				mStorage->RemoveFile(file);
			}

			if (isRecursively)
			{
				for (auto* dir : mDirs)
				{
					RETURN_FALSE_IF_FALSE(dir->SearchFilesToRemove(searchPath, isRecursively));
				}
			}

			return !resultFiles.IsEmpty();
		}
		//invalid search path
		return false;
	}
	else
	{
		return RemoveFile(searchPath);
	}
}

bool DirectoryEntry::SearchFilesToExtract(const StringRef& searchPath, bool isRecursively /*= true*/, const StringRef& outDir /*= StringRef::Empty*/) const
{
	RETURN_FALSE_IF_FALSE(IsValid());
	if (Path::HasSearchPattern(searchPath))
	{
		if (searchPath == "*.*")
		{
			return Extract(outDir, isRecursively);
		}
		else if (searchPath.BeginWith("*."))
		{
			bool isFound = false;
			StringRef searchExt = searchPath.SubString(1);
			for (auto* file : mFiles)
			{
				StringRef ext = Path::GetExtension(file->Name());
				if (ext == searchExt)
				{
					file->Extract(outDir);
					isFound = true;
				}
			}


			if (isRecursively)
			{
				for (auto* dir : mDirs)
				{
					RETURN_FALSE_IF_FALSE(dir->SearchFilesToExtract(searchPath,isRecursively,outDir));
				}
			}

			return isFound;
		}
		else if (searchPath.EndWith(".*"))
		{
			HeapString searchName = Path::GetFileNameWithoutExtension(searchPath);

			bool isFound = false;
			for (auto* file : mFiles)
			{
				StringRef name = Path::GetFileNameWithoutExtension(file->Name());
				if (name == searchName)
				{
					file->Extract(outDir);
					isFound = true;

				}
			}

			if (isRecursively)
			{
				for (auto* dir : mDirs)
				{
					RETURN_FALSE_IF_FALSE(dir->SearchFilesToExtract(searchPath, isRecursively, outDir));
				}
			}

			return isFound;
		}
		//invalid search path
		return false;
	}
	else
	{
		auto* fileEntry=FindFile(searchPath);
		RETURN_FALSE_IF_NULL(fileEntry);
		return fileEntry->Extract(outDir);
	}
}

bool DirectoryEntry::EnumerateFiles(Delegate<void(FileEntry*)> onFile, bool isRecursively /*= true*/, bool filterValid /*= true*/) const
{
	RETURN_FALSE_IF_FALSE(IsValid());
	RETURN_FALSE_IF_NULL(onFile);
	if (filterValid)
	{
		for (auto* file : mFiles)
		{
			if (file->IsValid())
			{
				onFile(file);
			}
		}
	}
	else
	{
		for (auto* file : mFiles)
		{
			onFile(file);
		}
	}
	

	if (isRecursively)
	{
		for (const auto* dir:mDirs)
		{
			dir->EnumerateFiles(onFile, isRecursively, filterValid);
		}
	}
	return true;
}

bool DirectoryEntry::GetFiles(List<FileEntry*>& outFiles, bool isRecursively /*= true*/, bool filterValid /*= true*/) const
{
	RETURN_FALSE_IF_FALSE(IsValid());
	if (filterValid)
	{
		for (auto* file : mFiles)
		{
			if (file->IsValid())
			{
				outFiles.Add(file);
			}
		}
	}
	else
	{
		outFiles.AddRange(mFiles);
	}
	
	if (isRecursively)
	{
		for (const auto* dir : mDirs)
		{
			dir->GetFiles(outFiles, isRecursively, filterValid);
		}
	}
	return true;

}

bool DirectoryEntry::EnumerateDirs(Delegate<void(DirectoryEntry*)> onDir, bool isRecursively /*= true*/, bool filterValid /*= true*/) const
{
	RETURN_FALSE_IF_FALSE(IsValid());
	RETURN_FALSE_IF_NULL(onDir);
	if (filterValid)
	{
		for (auto* dir : mDirs)
		{
			if (dir->IsValid())
			{
				onDir(dir);
			}
		}
	}
	else
	{
		for (auto* dir : mDirs)
		{
			onDir(dir);
		}
	}
	

	if (isRecursively)
	{
		for (const auto* dir : mDirs)
		{
			dir->EnumerateDirs(onDir, isRecursively, filterValid);
		}
	}
	return true;
}

bool DirectoryEntry::GetDirs(List<DirectoryEntry*>& outDirs, bool isRecursively /*= true*/, bool filterValid /*= true*/) const
{
	RETURN_FALSE_IF_FALSE(IsValid());
	if (filterValid)
	{
		for (auto* dir : mDirs)
		{
			if (dir->IsValid())
			{
				outDirs.Add(dir);
			}
		}
	}
	else
	{
		outDirs.AddRange(mDirs);
	}
	if (isRecursively)
	{
		for (const auto* dir : mDirs)
		{
			dir->GetDirs(outDirs, isRecursively, filterValid);
		}
	}
	return true;
}

bool DirectoryEntry::RemoveAllFiles()
{
	RETURN_FALSE_IF_FALSE(IsValid());
	if (mStorage != nullptr)
	{
		return mStorage->RemoveAllFiles(*this);
	}

	SAFE_DELETE_COLLECTION(mFiles);
	mFileDict.Clear();
	return true;
}

FileEntry* DirectoryEntry::SaveFile(const StringRef& path, const MemoryByteData& data)
{
	RETURN_NULL_IF_FALSE(IsValid());
	RETURN_NULL_IF_NULL(mStorage);
	return mStorage->SaveFile(data, path, this);
}

bool DirectoryEntry::RemoveAllDirectories()
{
	RETURN_FALSE_IF_FALSE(IsValid());
	if (mStorage != nullptr)
	{
		return mStorage->RemoveAllDirectories(*this);
	}

	SAFE_DELETE_COLLECTION(mDirs);
	mDirDict.Clear();
	return true;
}



const FileEntry* DirectoryEntry::FindFile(const StringRef& name) const
{
	RETURN_NULL_IF_FALSE(IsValid());
	return mFileDict.TryGetValueWithFailed(name, nullptr);

}

FileEntry* DirectoryEntry::FindFile(const StringRef& name)
{
	RETURN_NULL_IF_FALSE(IsValid());
	return mFileDict.TryGetValueWithFailed(name, nullptr);
}

bool DirectoryEntry::ExistsFile(const StringRef& name) const
{
	RETURN_FALSE_IF_FALSE(IsValid());
	return FindFile(name) != nullptr;
}


//SIREN_BODY_METADATA_BEGIN
SIREN_METADATA(DirectoryEntry, 14);
SIREN_PROPERTY_METADATA_STRUCT(0, DirectoryEntry, Name, 4);
SIREN_PROPERTY_METADATA(1, DirectoryEntry, Operations, 10, (EntryOperation)0);
SIREN_PROPERTY_METADATA_STRUCT(2, DirectoryEntry, Dirs, 4);
SIREN_PROPERTY_METADATA_STRUCT(3, DirectoryEntry, Files, 5);
//SIREN_BODY_METADATA_END

MEDUSA_END;