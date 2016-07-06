// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Pattern/Singleton.h"
#include "SirenAssembly.h"
#include "Core/Siren/Schema/Type/SirenBuildinType.h"
#include "Core/Siren/Schema/Type/BaseSirenCustomType.h"

MEDUSA_BEGIN;


class SirenMachine :public Singleton<SirenMachine>
{
	using AssemblyDictionary = Dictionary<StringRef, SirenAssembly*>;
	using BuildinTypeDictionary= Dictionary<StringRef, SirenBuildinType*>;
	friend class Singleton<SirenMachine>;
	SirenMachine();
	~SirenMachine(void);
public:
	SirenAssembly* FindAssembly(const StringRef& name)const;
	SirenAssembly* NewAssembly(const StringRef& name);
	bool RemoveAssembly(SirenAssembly* assembly);

	SirenAssembly* LoadAssembly(const FileIdRef& fileId);
	SirenAssembly* LoadAssembly(const FileIdRef& fileId, const MemoryData& data);
public:
	const SirenBuildinList& List() const { return mList; }
	const SirenBuildinDictionary& Dictionary() const { return mDictionary; }
	const SirenBuildinBool& Bool() const { return mBool; }
	const SirenBuildinInt8& Int8() const { return mInt8; }
	const SirenBuildinUInt8& UInt8() const { return mUInt8; }
	const SirenBuildinInt16& Int16() const { return mInt16; }
	const SirenBuildinUInt16& UInt16() const { return mUInt16; }
	const SirenBuildinInt32& Int32() const { return mInt32; }
	const SirenBuildinUInt32& UInt32() const { return mUInt32; }
	const SirenBuildinInt64& Int64() const { return mInt64; }
	const SirenBuildinUInt64& UInt64() const { return mUInt64; }
	const SirenBuildinFloat& Float() const { return mFloat; }
	const SirenBuildinDouble& Double() const { return mDouble; }
	const SirenBuildinString& String() const { return mString; }
	const SirenBuildinBlob& Blob() const { return mBlob; }
	const SirenBuildinType* FindBuildinType(const StringRef& name)const;
	const BaseSirenCustomType* FindCustomType(const StringRef& name)const;

	const ISirenType* FindType(const StringRef& name)const;

protected:
	AssemblyDictionary mAssemblies;
protected:
	//Build in types
	SirenBuildinBool mBool;
	SirenBuildinInt8 mInt8;
	SirenBuildinUInt8 mUInt8;
	SirenBuildinInt16 mInt16;
	SirenBuildinUInt16 mUInt16;
	SirenBuildinInt32 mInt32;
	SirenBuildinUInt32 mUInt32;
	SirenBuildinInt64 mInt64;
	SirenBuildinUInt64 mUInt64;
	SirenBuildinFloat mFloat;
	SirenBuildinDouble mDouble;
	SirenBuildinString mString;
	SirenBuildinBlob mBlob;

	SirenBuildinList mList;
	SirenBuildinDictionary mDictionary;

	BuildinTypeDictionary mBuildinTypes;	//weak
};

MEDUSA_END;
