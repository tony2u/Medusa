// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/IO/FileSystem.h"

MEDUSA_BEGIN;

class MemoryFileAutoRegister
{
public:
	template<typename T>
	MemoryFileAutoRegister(const FileIdRef& fileId, TMemoryData<T> data)
	{
		FileSystem::Instance().Memory().RegisterMemory(data.template Cast<byte>(), fileId);

	}
	template<typename T>
	MemoryFileAutoRegister(const FileIdRef& fileId, T* buffer, size_t byteSize)
	{
		MemoryData data = MemoryData::FromStatic((byte*)buffer, byteSize);
		FileSystem::Instance().Memory().RegisterMemory(data, fileId);
	}
	template<typename T, size_t size>
	MemoryFileAutoRegister(const FileIdRef& fileId, T(&buffer)[size])
	{
		MemoryData data = MemoryData::FromStatic((byte*)buffer, size*sizeof(T));
		FileSystem::Instance().Memory().RegisterMemory(data, fileId);
	}


	template<typename T>
	static void Register(const FileIdRef& fileId, TMemoryData<T> data)
	{
		FileSystem::Instance().Memory().RegisterMemory(data.template Cast<byte>(), fileId);

	}
	template<typename T>
	static void Register(const FileIdRef& fileId, T* buffer, size_t byteSize)
	{
		MemoryData data = MemoryData::FromStatic((byte*)buffer, byteSize);
		FileSystem::Instance().Memory().RegisterMemory(data, fileId);
	}
	template<typename T, size_t size>
	static void Register(const FileIdRef& fileId, T(&buffer)[size])
	{
		MemoryData data = MemoryData::FromStatic((byte*)buffer, size*sizeof(T));
		FileSystem::Instance().Memory().RegisterMemory(data, fileId);
	}
};

MEDUSA_END;