// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "SirenAssembly.h"
#include "Core/IO/FileInfo.h"
#include "Core/Siren/Schema/SirenTextParser.h"
#include "Core/Log/Log.h"
#include "SirenMachine.h"
#include "Core/Siren/Schema/Type/SirenCustomClass.h"
#include "Core/String/StringParser.h"
#include "Core/System/System.h"
#include "Core/IO/File.h"
#include "Core/IO/Stream/MemoryStream.h"
#include "Core/Siren/Schema/Type/SirenCustomEnum.h"
#include "Core/Siren/Schema/Type/SirenCustomClass.h"
#include "Core/Siren/Schema/Function/ISirenFunction.h"
#include "Core/IO/FileIdRef.h"
#include "Core/IO/FileSystem.h"

MEDUSA_BEGIN;

SirenAssembly::SirenAssembly(const StringRef& name /*= StringRef::Empty*/)
	:mName(name)
{

}

SirenAssembly::~SirenAssembly(void)
{
	Unload();
}


bool SirenAssembly::LoadFromData(const FileIdRef& fileId, const MemoryData& data, uint format /*= (uint)-1*/)
{
	FileType fileType = (FileType)format;
	RETURN_FALSE_IF_NOT_EQUAL(fileType, FileType::mpb);

	MemoryStream stream(data);
	return LoadFrom(stream);
}


void SirenAssembly::Unload()
{
	SAFE_DELETE_DICTIONARY_VALUE(mTypes);
	SAFE_DELETE_COLLECTION(mFunctions);
}

uint SirenAssembly::OnCheckFormat(StringRef path) const
{
	return (uint)FileInfo::ExtractType(path);
}


bool SirenAssembly::Parse(const FileIdRef& file)
{
	if (mLoadedFiles.Contains(file.Name))
	{
		return true;
	}
	Log::FormatInfo("Parse:{}", file.Name);
	SirenTextParser compiler(*this);
	bool isSuccess = compiler.ParseFile(file);
	mLoadedFiles.Add(file.Name);
	return isSuccess;
}

bool SirenAssembly::Parse(IStream& stream)
{
	SirenTextParser compiler(*this);
	return compiler.ParseStream(stream);
}


void SirenAssembly::Print()
{
	Log::FormatInfo("Assembly:{}", mName);
	Log::FormatInfo("TypeCount:{}", mTypes.Count());
}

bool SirenAssembly::Link()
{
	//types
	for (auto& typePair : mTypes)
	{
		auto* type = typePair.Value;
		RETURN_FALSE_IF_FALSE(type->Link(*this));
	}
	return true;
}

bool SirenAssembly::Execute()
{
	for (auto func : mFunctions)
	{
		func->Execute(*this);
	}
	SAFE_DELETE_COLLECTION(mFunctions);
	return true;
}

bool SirenAssembly::IsCompleted() const
{
	for (auto& typePair : mTypes)
	{
		auto* type = typePair.Value;
		RETURN_FALSE_IF_FALSE(type->IsCompleted());
	}

	return true;
}

bool SirenAssembly::Merge(const SirenAssembly& other)
{
	//merge references
	for (auto ref:other.mReferenceAssemblies)
	{
		AddReference(ref);
	}


	for (auto& typePair : other.mTypes)
	{
		auto* curType = FindCustomType(typePair.Key);
		if (curType == nullptr)
		{
			AddType((BaseSirenCustomType*)typePair.Value->Clone());
		}
		else
		{
			auto* otherType = typePair.Value;
			if (!curType->Merge(*otherType))
			{
				Log::FormatError("Cannot merge class:{}", typePair.Key);
				return false;
			}
		}
	}

	

	return Link();
}

bool SirenAssembly::LoadFrom(IStream& stream)
{
	uint32 signature = stream.Read<uint32>();
	if (signature != FixedSignature)
	{
		Log::FormatError("Invalid siren assembly signature:{} vs {}", signature, FixedSignature);
		return false;
	}

	mName = stream.ReadString();
	uint refCount = stream.Read<uint32>();
	FOR_EACH_SIZE(i, refCount)
	{
		auto assName = stream.ReadString();
		
		auto* ass= SirenMachine::Instance().LoadAssembly(assName);
		if (ass==nullptr)
		{
			Log::FormatError("Cannot find reference assembly:{}", assName);
			return false;
		}
		mReferenceAssemblies.Add(ass);
	}


	uint typeCount = stream.Read<uint32>();
	FOR_EACH_SIZE(i, typeCount)
	{
		char isClass = (char)stream.ReadChar();
		if (isClass == 1)
		{
			std::unique_ptr<SirenCustomClass> type(new SirenCustomClass());
			RETURN_FALSE_IF_FALSE(type->LoadFrom(stream));
			mTypes.Add(type->Name(), type.get());
			type.release();
		}
		else
		{
			std::unique_ptr<SirenCustomEnum> type(new SirenCustomEnum());
			RETURN_FALSE_IF_FALSE(type->LoadFrom(stream));
			mTypes.Add(type->Name(), type.get());
			type.release();
		}
	}

	return Link();
}

bool SirenAssembly::SaveTo(IStream& stream) const
{
	//signature
	stream.Write(FixedSignature);
	//name
	stream.WriteString(mName);

	//references
	stream.Write((uint32)mReferenceAssemblies.Count());
	for (auto& ref : mReferenceAssemblies)
	{
		stream.WriteString(ref->Name());
	}

	//types

	stream.Write((uint32)mTypes.Count());
	for (auto& typePair : mTypes)
	{
		auto* type = typePair.Value;
		char isClass = type->IsCustomClass() ? 1 : 0;
		stream.WriteChar(isClass);
		type->SaveTo(stream);
	}

	return true;
}

BaseSirenCustomType* SirenAssembly::FindCustomType(const StringRef& name) const
{
	if (name.Contains('.'))
	{
		List<StringRef> outPaths;
		StringParser::Split(name, ".", outPaths, false);
		if (outPaths.Count() <= 1)
		{
			return nullptr;
		}

		auto* rootType = mTypes.GetOptional(outPaths[0], nullptr);
		if (rootType == nullptr || !rootType->IsCustomClass())
		{
			return nullptr;
		}

		SirenCustomClass* parentType = (SirenCustomClass*)rootType;
		for (size_t i = 1; i < outPaths.Count(); ++i)
		{
			auto* childType = parentType->FindType(outPaths[i]);
			if (childType == nullptr || !childType->IsCustomClass())
			{
				return nullptr;
			}
			parentType = (SirenCustomClass*)childType;
		}

		return parentType;
	}
	else
	{
		return mTypes.GetOptional(name, nullptr);
	}
}

ISirenType* SirenAssembly::FindType(const StringRef& name) const
{
	auto* type = SirenMachine::Instance().FindBuildinType(name);
	RETURN_SELF_IF_NOT_NULL((ISirenType*)type);
	return FindCustomType(name);
}

ISirenType* SirenAssembly::FindTypeWithReference(const StringRef& name) const
{
	auto* type = SirenMachine::Instance().FindBuildinType(name);
	RETURN_SELF_IF_NOT_NULL((ISirenType*)type);
	return FindCustomTypeWithReference(name);
}

BaseSirenCustomType* SirenAssembly::FindCustomTypeWithReference(const StringRef& name) const
{
	auto* type = FindCustomType(name);
	RETURN_SELF_IF_NOT_NULL(type);
	for (auto ref:mReferenceAssemblies)
	{
		RETURN_SELF_IF_NOT_NULL(ref->FindCustomTypeWithReference(name));
	}
	return nullptr;
}

bool SirenAssembly::HasType(BaseSirenCustomType* type) const
{
	return HasType(type->Name());
}

bool SirenAssembly::HasType(const StringRef& name) const
{
	return mTypes.ContainsKey(name);
}

bool SirenAssembly::AddType(BaseSirenCustomType* type)
{
	if (mTypes.TryAdd(type->Name(), type))
	{
		return true;
	}

	Log::FormatError("Duplicate type name:{}", type->Name());
	return false;
}

bool SirenAssembly::HasTypeWithReference(BaseSirenCustomType* type) const
{
	return HasTypeWithReference(type->Name());
}

bool SirenAssembly::HasTypeWithReference(const StringRef& name) const
{
	return FindTypeWithReference(name) != nullptr;
}

bool SirenAssembly::AddFunction(ISirenFunction* val)
{
	mFunctions.Add(val);
	return true;
}

bool SirenAssembly::AddReference(SirenAssembly* assembly)
{
	if (!mReferenceAssemblies.Contains(assembly))
	{
		mReferenceAssemblies.Add(assembly);
	}
	return true;
}

bool SirenAssembly::AddReference(const FileIdRef& file)
{
	auto* ass= SirenMachine::Instance().LoadAssembly(file);
	if (ass == nullptr)
	{
		Log::FormatError("Cannot find reference assembly:{}", file.Name);
		return false;
	}
	return AddReference(ass);
}

MEDUSA_END;