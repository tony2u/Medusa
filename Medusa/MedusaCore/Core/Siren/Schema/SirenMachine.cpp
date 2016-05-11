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
	mBuildinClasses.Add(mBool.Name(), &mBool);
	mBuildinClasses.Add(mInt8.Name(), &mInt8);
	mBuildinClasses.Add(mUInt8.Name(), &mUInt8);
	mBuildinClasses.Add(mInt16.Name(), &mInt16);
	mBuildinClasses.Add(mUInt16.Name(), &mUInt16);
	mBuildinClasses.Add(mInt32.Name(), &mInt32);
	mBuildinClasses.Add(mUInt32.Name(), &mUInt32);
	mBuildinClasses.Add(mInt64.Name(), &mInt64);
	mBuildinClasses.Add(mUInt64.Name(), &mUInt64);
	mBuildinClasses.Add(mFloat.Name(), &mFloat);
	mBuildinClasses.Add(mDouble.Name(), &mDouble);
	mBuildinClasses.Add(mString.Name(), &mString);
	mBuildinClasses.Add(mBlob.Name(), &mBlob);
	mBuildinClasses.Add(mList.Name(), &mList);
	mBuildinClasses.Add(mDictionary.Name(), &mDictionary);

	//alias
	mBuildinClasses.Add("int8", &mInt8);
	mBuildinClasses.Add("uint8", &mUInt8);
	mBuildinClasses.Add("int16", &mInt16);
	mBuildinClasses.Add("uint16", &mUInt16);
	mBuildinClasses.Add("int32", &mInt32);
	mBuildinClasses.Add("uint32", &mUInt32);

	mBuildinClasses.Add("long", &mInt64);
	mBuildinClasses.Add("ulong", &mUInt64);
	mBuildinClasses.Add("string", &mString);
	mBuildinClasses.Add("blob", &mBlob);

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
	return mBuildinClasses.GetOptional(name, nullptr);
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
