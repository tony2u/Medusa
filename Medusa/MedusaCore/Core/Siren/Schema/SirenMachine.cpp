// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "SirenMachine.h"
#include "Core/IO/FileIdRef.h"
#include "Core/IO/Path.h"

MEDUSA_BEGIN;

SirenMachine::SirenMachine()
	:mBool("bool"),
	mInt8("char"),
	mUInt8("byte"),
	mInt16("short"),
	mUInt16("ushort"),
	mInt32("int"),
	mUInt32("uint"),
	mInt64("int64"),
	mUInt64("uint64"),
	mFloat("float"),
	mDouble("double"),
	mString("HeapString"),
	mBlob("MemoryData"),
	mList("List"),
	mDictionary("Dictionary")
{
	mBuildinTypes.Add(mBool.Name(), &mBool);
	mBuildinTypes.Add(mInt8.Name(), &mInt8);
	mBuildinTypes.Add(mUInt8.Name(), &mUInt8);
	mBuildinTypes.Add(mInt16.Name(), &mInt16);
	mBuildinTypes.Add(mUInt16.Name(), &mUInt16);
	mBuildinTypes.Add(mInt32.Name(), &mInt32);
	mBuildinTypes.Add(mUInt32.Name(), &mUInt32);
	mBuildinTypes.Add(mInt64.Name(), &mInt64);
	mBuildinTypes.Add(mUInt64.Name(), &mUInt64);
	mBuildinTypes.Add(mFloat.Name(), &mFloat);
	mBuildinTypes.Add(mDouble.Name(), &mDouble);
	mBuildinTypes.Add(mString.Name(), &mString);
	mBuildinTypes.Add(mBlob.Name(), &mBlob);
	mBuildinTypes.Add(mList.Name(), &mList);
	mBuildinTypes.Add(mDictionary.Name(), &mDictionary);

	//alias
	mBuildinTypes.Add("int8", &mInt8);
	mBuildinTypes.Add("uint8", &mUInt8);
	mBuildinTypes.Add("int16", &mInt16);
	mBuildinTypes.Add("uint16", &mUInt16);
	mBuildinTypes.Add("int32", &mInt32);
	mBuildinTypes.Add("uint32", &mUInt32);

	mBuildinTypes.Add("long", &mInt64);
	mBuildinTypes.Add("ulong", &mUInt64);
	mBuildinTypes.Add("string", &mString);
	mBuildinTypes.Add("blob", &mBlob);

}

SirenMachine::~SirenMachine(void)
{
	SAFE_DELETE_DICTIONARY_VALUE(mAssemblies);
}

SirenAssembly* SirenMachine::FindAssembly(const StringRef& name) const
{
	return mAssemblies.GetOptional(name, nullptr);
}

SirenAssembly* SirenMachine::NewAssembly(const StringRef& name)
{
	auto* result = FindAssembly(name);
	if (result == nullptr)
	{
		result = new SirenAssembly(name);
		mAssemblies.Add(name, result);
	}

	return result;
}

bool SirenMachine::RemoveAssembly(SirenAssembly* assembly)
{
	return mAssemblies.RemoveKey(assembly->Name());
}

SirenAssembly* SirenMachine::LoadAssembly(const FileIdRef& fileId, const MemoryData& data)
{
	auto* ass = FindAssembly(Path::GetFileName(fileId.Name));
	RETURN_SELF_IF_NOT_NULL(ass);

	ass = new SirenAssembly();
	if (ass->LoadFromData(fileId, data))
	{
		mAssemblies.Add(ass->Name(), ass);
		return ass;
	}

	SAFE_DELETE(ass);
	return ass;
}

SirenAssembly* SirenMachine::LoadAssembly(const FileIdRef& fileId)
{
	auto* ass = FindAssembly(fileId.Name);
	RETURN_SELF_IF_NOT_NULL(ass);

	ass = new SirenAssembly();
	if (ass->LoadFromFileSystem(fileId))
	{
		mAssemblies.Add(ass->Name(), ass);
		return ass;
	}

	SAFE_DELETE(ass);
	return ass;
}

const SirenBuildinType* SirenMachine::FindBuildinType(const StringRef& name) const
{
	return mBuildinTypes.GetOptional(name, nullptr);
}

const BaseSirenCustomType* SirenMachine::FindCustomType(const StringRef& name) const
{
	//for each assembly
	for (auto& assembly : mAssemblies)
	{
		auto* val = assembly.Value->FindCustomType(name);
		RETURN_SELF_IF_NOT_NULL(val);
	}
	return nullptr;
}

const ISirenType* SirenMachine::FindType(const StringRef& name) const
{
	auto* val = FindBuildinType(name);
	RETURN_SELF_IF_NOT_NULL(val);
	return FindCustomType(name);
}

MEDUSA_END;
