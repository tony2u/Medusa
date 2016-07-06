// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "IPackage.h"
#include "Core/IO/FileSystem.h"
#include "Core/IO/Stream/IStream.h"
#include "Core/IO/Package/PackageFactory.h"
#include "Core/IO/File.h"

MEDUSA_BEGIN;


IPackage::IPackage(const StringRef& path, PackagePriority priority /*= PackagePriority::Downloaded*/, uint version /*= 0*/)
	:mPath(path),
	mPriority(priority),
	mVersion(version)
{

}

int IPackage::Compare(const IPackage& other) const
{
	int r = (int)mPriority - (int)other.mPriority;
	if (r == 0)
	{
		r = mVersion - other.mVersion;
	}
	return r;
}

bool IPackage::operator<(const IPackage& other) const
{
	if (mPriority < other.mPriority)
	{
		return true;
	}
	else if (mPriority > other.mPriority)
	{
		return false;
	}
	else
	{
		return mVersion < other.mVersion;
	}
}

IPackage::~IPackage()
{
}

void IPackage::EnableEncryptFileNames(bool val)
{
	auto newVal= MEDUSA_FLAG_RETURN_ENABLE(Flags(), PackageFlags::EncryptFileNames, val);
	SetFlags(newVal);
}



void IPackage::SetReadonly(bool val)
{
	auto newVal = MEDUSA_FLAG_RETURN_ENABLE(Flags(), PackageFlags::Readonly, val);
	SetFlags(newVal);
	
}

void IPackage::EnableWriteSaltData(bool val)
{
	auto newVal = MEDUSA_FLAG_RETURN_ENABLE(Flags(), PackageFlags::WriteSaltData, val);
	SetFlags(newVal);
}


void IPackage::EnableWholeFileCoding(bool val)
{
	auto newVal = MEDUSA_FLAG_RETURN_ENABLE(Flags(), PackageFlags::WholeFileCoding, val);
	SetFlags(newVal);
}



bool IPackage::Merge(const IPackage& other)
{
	Dictionary<StringRef, const DirectoryEntry*> otherDirs;
	other.RootDir().EnumerateDirs([&otherDirs](DirectoryEntry* dirEntry) { otherDirs.Add(dirEntry->Path(), dirEntry); }, true, false);

	Dictionary<StringRef, const FileEntry*> otherFiles;
	other.RootDir().EnumerateFiles([&otherFiles](FileEntry* fileEntry) { otherFiles.Add(fileEntry->Path(), fileEntry); }, true, false);

	for (const auto& dir : otherDirs)
	{
		const DirectoryEntry* dirEntry = dir.Value;
		if (dirEntry->IsValid())
		{
			FindOrCreateDirectory(dirEntry->Path());
		}
		else
		{
			RemoveDirectory(dirEntry->Path());
		}
	}

	//remove file first to reuse space
	for (const auto& file : otherFiles)
	{
		const FileEntry* fileEntry = file.Value;
		if (!fileEntry->IsValid())
		{
			//remove file
			RemoveFile(fileEntry->Path());
		}
	}

	for (const auto& file : otherFiles)
	{
		const FileEntry* fileEntry = file.Value;
		if (fileEntry->IsValid())
		{
			FileEntry* currentFile = FindFile(fileEntry->Path());
			if (currentFile != nullptr)
			{
				if (currentFile->Signature() != fileEntry->Signature())
				{
					OnCopyFile(*fileEntry, *currentFile);
				}
			}
			else
			{
				FileEntry* newFile = CreateFileEntry(fileEntry->Path());
				OnCopyFile(*fileEntry, *newFile);
			}
		}
	}

	return true;
}

IPackage* IPackage::CreateDiff(const IPackage& other, const StringRef& diffPath)
{

	/*
	Dirs:
	Added:		not in other
	Deleted:	in other but not in this
	Files:
	Added:		not in other
	Deleted:	in other but not in this
	Modified:	in both but modified
	*/

	File::Delete(diffPath);

	IPackage* resultPackage = PackageFactory::Create(Type(), diffPath);
	resultPackage->SetCoders(this->Coders());
	resultPackage->SetHasher(this->Hasher());
	resultPackage->SetKey(this->Key());
	resultPackage->Initialize();

	Dictionary<StringRef, const DirectoryEntry*> currentDirs;
	mRootDir.EnumerateDirs([&currentDirs](DirectoryEntry* dirEntry) {currentDirs.Add(dirEntry->Path(), dirEntry); });

	Dictionary<StringRef, const DirectoryEntry*> otherDirs;
	other.RootDir().EnumerateDirs([&otherDirs](DirectoryEntry* dirEntry) {otherDirs.Add(dirEntry->Path(), dirEntry); });

	List<const DirectoryEntry*> addedDirs;
	List<const DirectoryEntry*> deletedDirs;

	List<DirectoryEntry*> newAddedDirs;
	List<DirectoryEntry*> newDeletedDirs;

	for (const auto& dir : currentDirs)
	{
		if (!otherDirs.RemoveKey(dir.Key))
		{
			//new add
			addedDirs.Add(dir.Value);
		}
	}

	for (const auto& dir : otherDirs)
	{
		if (!currentDirs.RemoveKey(dir.Key))
		{
			//deleted
			deletedDirs.Add(dir.Value);
		}
	}

	for (const auto* dir : addedDirs)
	{
		DirectoryEntry* newDir = resultPackage->FindOrCreateDirectory(dir->Path());
		newAddedDirs.Add(newDir);
	}

	for (const auto* dir : deletedDirs)
	{
		DirectoryEntry* newDir = resultPackage->FindOrCreateDirectory(dir->Path());
		newDeletedDirs.Add(newDir);
	}


	//////////////////////////////////////////////////////////////////////////
	Dictionary<StringRef, const FileEntry*> currentFiles;
	mRootDir.EnumerateFiles([&currentFiles](FileEntry* fileEntry) { currentFiles.Add(fileEntry->Path(), fileEntry); });

	Dictionary<StringRef, const FileEntry*> otherFiles;
	other.RootDir().EnumerateFiles([&otherFiles](FileEntry* fileEntry) { otherFiles.Add(fileEntry->Path(), fileEntry); });


	List<const FileEntry*> addedFiles;
	List<const FileEntry*> deletedFiles;
	List<const FileEntry*> updatedFiles;

	for (const auto& file : currentFiles)
	{
		const auto* otherFile = otherFiles.RemoveKeyOptional(file.Key, nullptr);
		if (otherFile == nullptr)
		{
			//new add
			addedFiles.Add(file.Value);
		}
		else
		{
#ifdef MEDUSA_SAFE_CHECK
			if (file.Value->Signature().IsEmpty())
			{
				Log::AssertFailedFormat("File:{} has no signature", file.Value->Path());
			}
			if (otherFile->Signature().IsEmpty())
			{
				Log::AssertFailedFormat("File:{} has no signature", otherFile->Path());
			}
#endif

			//check if modified
			if (file.Value->Signature() != otherFile->Signature())
			{
				updatedFiles.Add(file.Value);
			}
			else
			{
				//not modified
			}

		}
	}

	for (const auto& file : otherFiles)
	{
		if (!currentFiles.RemoveKey(file.Key))
		{
			//deleted
			deletedFiles.Add(file.Value);
		}
	}

	for (const auto* file : addedFiles)
	{
		FileEntry* newFile = resultPackage->CreateFileEntry(file->Path());
		newFile->SetOperations(EntryOperation::Add);
		OnCopyFile(*file, *newFile);
	}

	for (const auto* file : updatedFiles)
	{
		FileEntry* newFile = resultPackage->CreateFileEntry(file->Path());
		newFile->SetOperations(EntryOperation::Update);
		OnCopyFile(*file, *newFile);
	}

	for (const auto* file : deletedFiles)
	{
		FileEntry* newFile = resultPackage->CreateFileEntry(file->Path());
		newFile->SetOperations(EntryOperation::Delete);
	}

	//set dir operations
	for (auto* dir : newAddedDirs)
	{
		dir->SetOperations(EntryOperation::Add);
	}

	for (auto* dir : newDeletedDirs)
	{
		dir->SetOperations(EntryOperation::Delete);
	}


	resultPackage->Save();
	return resultPackage;
}

bool IPackage::IsDataCompatiable(const IPackage& other) const
{
	return Type() == other.Type()
		&& BlockSize() == other.BlockSize()
		&& Coders() == other.Coders()
		&& Key().IsContentEqual(other.Key());
}

void IPackage::OnFileAdded(FileEntry& file)
{
	if (mParent != nullptr)
	{
		mParent->MapFile(file, true);
	}
}

void IPackage::OnFileRemoved(FileEntry& file)
{
	if (mParent != nullptr)
	{
		mParent->UnmapFile(file, true);
	}
}

bool IPackage::OnCopyFile(const FileEntry& from, FileEntry& to)
{
	IPackage* toPackage = (IPackage*)to.Parent()->Storage();
	Share<const IStream> readStream = from.Read();
	bool result = toPackage->SaveFile(to, *readStream);
	to.SetSignature(from.Signature());
	to.SetPermission(from.Permission());

	return result;
}



MEDUSA_END;

