// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "Directory.h"
#include "Core/IO/FileInfo.h"
#include "Core/IO/File.h"
#include "Core/IO/Path.h"

MEDUSA_BEGIN;
#ifdef WIN32   
#define ACCESS _access   
#define MKDIR(a) _mkdir((a))   
#else
#define ACCESS access   
#define MKDIR(a) mkdir((a),S_IRWXU | S_IRWXG | S_IRWXO)   
#endif 


bool Directory::CreateDir(const StringRef& dir)
{
	if (Exists(dir))
	{
		return  true;
	}


	if (!dir.IsEmpty())
	{
#ifdef WIN32
		return _mkdir(dir.c_str()) == 0;
#else
		umask(0);
		int r = mkdir(dir.c_str(), S_IRWXU | S_IRWXG | S_IRWXO);
		//int errorCode= errno; 

		return r == 0;
#endif


	}

	return true;
}

bool Directory::CreateDirRecursively(const StringRef& dir)
{
	RETURN_FALSE_IF_EMPTY(dir);

	int result;
#ifdef WIN32
	char* pszDir = _strdup(dir.c_str());
#else
	char* pszDir = strdup(dir.c_str());

#endif
	size_t length = strlen(pszDir);

	// create temp dir  
	FOR_EACH_SIZE(i, length)
	{
		if (Path::IsDirectorySeparator(pszDir[i]))
		{
			pszDir[i] = '\0';

			//if not exist, create  
			result = ACCESS(pszDir, 0);
			if (result != 0 && i != 0)
			{
				result = MKDIR(pszDir);
				if (result != 0)
				{
					SAFE_FREE(pszDir);
					return false;
				}
			}
			//to support linux,replace all \ with /
			pszDir[i] = Path::DirectorySeparatorChar;
		}
	}

	result = ACCESS(pszDir, 0);
	if (result == 0)
	{
		SAFE_FREE(pszDir);
		return true;
	}
	result = MKDIR(pszDir);
	SAFE_FREE(pszDir);
	return result == 0;

}

bool Directory::Exists(const StringRef& dir)
{
	FileMode outFileMode;
	if (File::GetFileMode(dir, outFileMode))
	{
		if (outFileMode == FileMode::Directory)
		{
			return true;
		}
	}

	return false;
}

bool Directory::CreateDirectoryForFile(const StringRef& filePath)
{
	if (File::Exists(filePath, 6))
	{
		return true;
	}

	FileInfo info(filePath);
	StringRef dir = info.Directory();
	return CreateDirRecursively(dir);
}


void Directory::Copy(const StringRef& fromDir, const StringRef& toDir, bool isRecursively/*=true*/)
{
#ifdef WIN32
	_finddata_t findData;
	HeapString curDir = Path::Combine(fromDir, "*");
	intp handle = _findfirst(curDir.c_str(), &findData);
	if (handle == -1)
	{
		return;
	}

	do
	{
		if (findData.attrib&_A_SUBDIR)
		{
			if ((strcmp(findData.name, ".") != 0) && (strcmp(findData.name, "..") != 0))
			{
				if (isRecursively)
				{
					CreateDir(Path::Combine(toDir, findData.name));
					Copy(Path::Combine(fromDir, findData.name), Path::Combine(toDir, findData.name), isRecursively);
				}
			}
		}
		else
		{
			File::Copy(Path::Combine(fromDir, findData.name), Path::Combine(toDir, findData.name));
		}

	} while (_findnext(handle, &findData) == 0);
	_findclose(handle);
#else
	DIR* dir = opendir(fromDir.c_str());
	if (dir == nullptr) {
		return;
	}
	dirent* ent = nullptr;
	struct stat statObj;
	HeapString tempDir;

	while ((ent = readdir(dir)) != nullptr)
	{
		tempDir = Path::Combine(fromDir, ent->d_name);
		lstat(tempDir.c_str(), &statObj);
		if (S_ISDIR(statObj.st_mode))
		{
			if ((strcmp(ent->d_name, ".") != 0) && (strcmp(ent->d_name, "..") != 0))
			{
				if (isRecursively)
				{
					CreateDir(Path::Combine(toDir, ent->d_name));
					Copy(Path::Combine(fromDir, ent->d_name), Path::Combine(toDir, ent->d_name), isRecursively);
				}
			}
		}
		else
		{
			File::Move(Path::Combine(fromDir, ent->d_name), Path::Combine(toDir, ent->d_name));
		}

	}
	closedir(dir);
#endif
}

void Directory::Move(const StringRef& fromDir, const StringRef& toDir, bool isRecursively/*=true*/)
{
#ifdef WIN32
	_finddata_t findData;
	HeapString curDir = Path::Combine(fromDir, "*");
	intp handle = _findfirst(curDir.c_str(), &findData);
	if (handle == -1)
	{
		return;
	}

	do
	{
		if (findData.attrib&_A_SUBDIR)
		{
			if ((strcmp(findData.name, ".") != 0) && (strcmp(findData.name, "..") != 0))
			{
				if (isRecursively)
				{
					CreateDir(Path::Combine(toDir, findData.name));
					Move(Path::Combine(fromDir, findData.name), Path::Combine(toDir, findData.name), isRecursively);
					RemoveDir(Path::Combine(fromDir, findData.name));
				}
			}
		}
		else
		{
			File::Move(Path::Combine(fromDir, findData.name), Path::Combine(toDir, findData.name));
		}

	} while (_findnext(handle, &findData) == 0);
	_findclose(handle);
#else
	DIR* dir = opendir(fromDir.c_str());
	if (dir == nullptr) {
		return;
	}
	dirent* ent = nullptr;
	struct stat statObj;
	HeapString tempDir;

	while ((ent = readdir(dir)) != nullptr)
	{
		tempDir = Path::Combine(fromDir, ent->d_name);
		lstat(tempDir.c_str(), &statObj);
		if (S_ISDIR(statObj.st_mode))
		{
			if ((strcmp(ent->d_name, ".") != 0) && (strcmp(ent->d_name, "..") != 0))
			{
				if (isRecursively)
				{
					CreateDir(Path::Combine(toDir, ent->d_name));
					Move(Path::Combine(fromDir, ent->d_name), Path::Combine(toDir, ent->d_name), isRecursively);
					RemoveDir(Path::Combine(fromDir, ent->d_name));
				}
			}
		}
		else
		{
			File::Move(Path::Combine(fromDir, ent->d_name), Path::Combine(toDir, ent->d_name));
		}

	}
	closedir(dir);
#endif
}

bool Directory::Rename(StringRef oldName, StringRef newName)
{
	return rename(oldName.c_str(), newName.c_str()) == 0;
}

void Directory::GetFiles(const StringRef& dir, List<HeapString>& outFiles, bool isRecursively/*=false*/, const StringRef& searchPattern/*=StringRef::Empty*/)
{
#ifdef MEDUSA_WINDOWS
	_finddata_t findData;
	HeapString curDir = dir;

	if (!searchPattern.IsEmpty())
	{
		curDir = Path::Combine(curDir, searchPattern);
	}
	else
	{
		curDir = Path::Combine(curDir, "*.*");
	}

	intp handle = _findfirst(curDir.c_str(), &findData);
	if (handle == -1)
	{
		return;
	}

	do
	{
		if (findData.attrib&_A_SUBDIR)
		{
			if (isRecursively && (strcmp(findData.name, ".") != 0) && (strcmp(findData.name, "..") != 0))
			{
				GetFiles(Path::Combine(dir, findData.name), outFiles, isRecursively, searchPattern);
			}
		}
		else
		{
			outFiles.Add(Path::Combine(dir, findData.name));
		}

	} while (_findnext(handle, &findData) == 0);
	_findclose(handle);
#else
	DIR* dirObj = opendir(dir.c_str());
	if (dirObj == nullptr) {
		return;
	}
	dirent* ent = nullptr;
	struct stat statObj;
	HeapString tempDir;
	while ((ent = readdir(dirObj)) != nullptr)
	{
		tempDir = Path::Combine(dir, ent->d_name);
		lstat(tempDir.c_str(), &statObj);
		if (S_ISDIR(statObj.st_mode))
		{
			if (isRecursively && (strcmp(ent->d_name, ".") != 0) && (strcmp(ent->d_name, "..") != 0))
			{
				GetFiles(Path::Combine(dir, ent->d_name), outFiles, isRecursively, searchPattern);
			}
		}
		else
		{
			if (IsFitSearchPattern(ent->d_name, searchPattern))
			{
				outFiles.Add(Path::Combine(dir, ent->d_name));
			}
		}

	}
	closedir(dirObj);

#endif
}



void Directory::GetDirectories(const StringRef& dir, List<HeapString>& outDirectories, bool isRecursively/*=true*/, const StringRef& searchPattern/*=StringRef::Empty*/)
{
#ifdef WIN32
	_finddata_t findData;
	HeapString curDir = dir;
	curDir += Path::DirectorySeparatorChar;

	if (!searchPattern.IsEmpty())
	{
		curDir += searchPattern;
	}
	else
	{
		curDir += "*";
	}

	intp handle = _findfirst(curDir.c_str(), &findData);
	if (handle == -1)
	{
		return;
	}

	do
	{
		if (findData.attrib&_A_SUBDIR)
		{
			if ((strcmp(findData.name, ".") != 0) && (strcmp(findData.name, "..") != 0))
			{
				HeapString subDir = Path::Combine(dir, findData.name);
				outDirectories.Add(subDir);
				if (isRecursively)
				{
					GetDirectories(subDir, outDirectories, isRecursively, searchPattern);
				}
			}
		}

	} while (_findnext(handle, &findData) == 0);
	_findclose(handle);
#else

	DIR* dirObj = opendir(dir.c_str());
	if (dirObj == nullptr) {
		return;
	}
	dirent* ent = nullptr;
	struct stat statObj;
	HeapString tempDir;

	while ((ent = readdir(dirObj)) != nullptr)
	{
		tempDir = Path::Combine(dir, ent->d_name);
		lstat(tempDir.c_str(), &statObj);

		if (S_ISDIR(statObj.st_mode))
		{
			if ((strcmp(ent->d_name, ".") != 0) && (strcmp(ent->d_name, "..") != 0))
			{

				HeapString subDir = Path::Combine(dir, ent->d_name);
				if (IsFitSearchPattern(ent->d_name, searchPattern))
				{
					outDirectories.Add(subDir);
				}

				if (isRecursively)
				{
					GetDirectories(subDir, outDirectories, isRecursively, searchPattern);
				}
			}
		}
	}
	closedir(dirObj);
#endif
}

void Directory::SearchFiles(const StringRef& searchPath, List<HeapString>& outFiles, bool recursively /*= true*/)
{
	if (Path::IsDirectory(searchPath))
	{
		Directory::GetFiles(searchPath, outFiles, recursively);
	}
	else
	{
		if (Path::IsPath(searchPath))
		{
			FileInfo fileInfo(searchPath);
			Directory::GetFiles(fileInfo.Directory(), outFiles, recursively, fileInfo.FullName());
		}
		else
		{
			outFiles.Add(searchPath);
		}
	}
}

void Directory::SearchDirectories(const StringRef& searchPath, List<HeapString>& outDirectories, bool recursively /*= true*/)
{
	if (Path::IsDirectory(searchPath))
	{
		Directory::GetDirectories(searchPath, outDirectories, recursively);
	}
	else
	{
		if (Path::IsPath(searchPath))
		{
			FileInfo fileInfo(searchPath);
			Directory::GetDirectories(fileInfo.Directory(), outDirectories, recursively, fileInfo.FullName());
		}
	}
}

bool Directory::RemoveDir(const StringRef& dir)
{
	if (!dir.IsEmpty())
	{
#ifdef WIN32
		return _rmdir(dir.c_str()) == 0;
#else
		return rmdir(dir.c_str()) == 0;
#endif


	}

	return true;

}

bool Directory::RemoveDirRecursively(const StringRef& dir)
{
#ifdef WIN32
	_finddata_t findData;
	HeapString curDir = Path::Combine(dir, "*");
	intp handle = _findfirst(curDir.c_str(), &findData);
	if (handle == -1)
	{
		return false;
	}

	do
	{
		if (findData.attrib&_A_SUBDIR)
		{
			if ((strcmp(findData.name, ".") != 0) && (strcmp(findData.name, "..") != 0))
			{
				HeapString subDir = Path::Combine(dir, findData.name);
				RemoveDirRecursively(subDir);
				RemoveDir(subDir);
			}
		}
		else
		{
			File::Delete(Path::Combine(dir, findData.name));
		}

	} while (_findnext(handle, &findData) == 0);
	_findclose(handle);
#else
	DIR* dirObj = opendir(dir.c_str());
	if (dirObj == nullptr) {
		return false;
	}
	dirent* ent = nullptr;
	struct stat statObj;
	HeapString tempDir;

	while ((ent = readdir(dirObj)) != nullptr)
	{
		tempDir = Path::Combine(dir, ent->d_name);
		lstat(tempDir.c_str(), &statObj);
		if (S_ISDIR(statObj.st_mode))
		{
			if ((strcmp(ent->d_name, ".") != 0) && (strcmp(ent->d_name, "..") != 0))
			{
				HeapString subDir = Path::Combine(dir, ent->d_name);
				RemoveDirRecursively(subDir);
				RemoveDir(subDir);
			}
		}
		else
		{
			File::Delete(Path::Combine(dir, ent->d_name));
		}

	}
	closedir(dirObj);

#endif

	return true;
}

bool Directory::IsFitSearchPattern(const StringRef& fileName, const StringRef& searchPattern)
{
	RETURN_TRUE_IF_EMPTY(searchPattern);
	intp index = searchPattern.IndexOf('*');
	if (index >= 0)
	{
		if (index > 0 && searchPattern[index - 1] == '.')	//contains .*
		{
			FileInfo info(fileName);
			StringRef name = searchPattern.SubString(0, index - 1);
			return info.FullName() == name;
		}
		else if (index + 1 < (int)searchPattern.Length() && searchPattern[index + 1] == '.')	//contains *.
		{
			FileInfo info(fileName);
			StringRef ext = searchPattern.SubString(index + 1);
			return info.Extension() == ext;
		}
		else	//only *
		{
			return true;
		}
	}
	else
	{
		return fileName == searchPattern;
	}

}


MEDUSA_END;
