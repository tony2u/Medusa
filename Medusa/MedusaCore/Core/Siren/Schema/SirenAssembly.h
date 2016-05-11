// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Siren/Schema/Type/ISirenType.h"
#include "Core/IO/IFileLoadable.h"
#include "Core/Collection/Dictionary.h"
#include "Core/IO/Stream/IStreamable.h"
#include "Core/Collection/HashSet.h"

MEDUSA_BEGIN;


class SirenAssembly :public IFileLoadable, public IStreamable
{
public:
	SirenAssembly(const StringRef& name = StringRef::Empty);
	~SirenAssembly(void);
public:
	StringRef Name() const { return mName; }
	void SetName(const StringRef& name) { mName = name; }
	const Dictionary<StringRef, BaseSirenCustomType*>& Types() const { return mTypes; }

public:
	virtual bool LoadFromData(const FileIdRef& fileId, const MemoryData& data, uint format = (uint)-1) override;	//format used to indicate some other control option
	virtual void Unload();

	BaseSirenCustomType* FindCustomType(const StringRef& name)const;
	ISirenType* FindType(const StringRef& name)const;

	BaseSirenCustomType* FindCustomTypeWithReference(const StringRef& name)const;
	ISirenType* FindTypeWithReference(const StringRef& name)const;


	bool Parse(const FileIdRef& file);
	bool Parse(IStream& stream);


	void Print();
	bool Link();
	bool Execute();
	bool IsCompleted()const;

	bool Merge(const SirenAssembly& other);
public:
	virtual bool LoadFrom(IStream& stream)override;
	virtual bool SaveTo(IStream& stream)const override;
protected:
	virtual uint OnCheckFormat(StringRef path)const override;
public:
	bool AddType(BaseSirenCustomType* type);
	bool HasType(BaseSirenCustomType* type)const;
	bool HasType(const StringRef& name)const;

	bool HasTypeWithReference(BaseSirenCustomType* type)const;
	bool HasTypeWithReference(const StringRef& name)const;


	bool AddFunction(ISirenFunction* val);
	bool AddReference(SirenAssembly* assembly);
	bool AddReference(const FileIdRef& file);

protected:
	HeapString mName;
	List<SirenAssembly*> mReferenceAssemblies;	//weak


	Dictionary<StringRef, BaseSirenCustomType*> mTypes;
	List<ISirenFunction*> mFunctions;

	HashSet<HeapString> mLoadedFiles;

	constexpr static uint32 FixedSignature = 1396790093;	// 'SASM';	//Little endian, I mean 'MSAS'
};

MEDUSA_END;
