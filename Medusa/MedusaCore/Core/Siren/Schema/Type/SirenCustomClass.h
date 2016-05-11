// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "BaseSirenCustomType.h"
#include "Core/Collection/Dictionary.h"
#include "Core/Siren/Schema/Field/SirenField.h"
#include "Core/Siren/Schema/Attribute/SirenClassAttribute.h"
#include "Core/Collection/HashSet.h"

MEDUSA_BEGIN;


class SirenCustomClass :public BaseSirenCustomType
{
public:
	SirenCustomClass();
	virtual ~SirenCustomClass(void);
public:
	virtual bool IsCustomClass()const { return true; }
	virtual bool IsCustomEnum()const { return false; }

	virtual SirenTypeId Id()const override { return SirenTypeId::Struct; }

	virtual bool Parse(SirenAssembly& assembly, StringRef& refProto)override;
	virtual bool AddAttribute(StringRef name, StringRef val) override;
	virtual bool SetAttribute(const StringRef& val)override;

	const Dictionary<StringRef, BaseSirenCustomType*>& Types()const { return mTypes; }
	BaseSirenCustomType* FindType(const StringRef& name)const;
	bool HasType(const StringRef& name)const;
	SirenCustomClass* BaseType() const { return mBaseType; }

	const Dictionary<StringRef, SirenField*>& Fields() const { return mFields; }
	size_t GetFieldCountRecursively()const;
	virtual bool Link(SirenAssembly& assembly);
	virtual bool IsCompleted()const override;

	virtual bool Merge(const BaseSirenCustomType& other) override;
	virtual SirenCustomClass* Clone() const override;

	const SirenClassAttribute& Attribute() const { return mAttribute; }
	virtual bool IsGenerate()const override {return mAttribute.IsGenerate();}
	const HashSet<BaseSirenCustomType*>& IncludeTypes() const { return mIncludeTypes; }
	virtual StringRef Directory()const override { return mAttribute.Directory(); }

public:
	virtual bool LoadFrom(IStream& stream)override;
	virtual bool SaveTo(IStream& stream)const override;
protected:
	bool AddField(SirenField* val);
	bool AddType(BaseSirenCustomType* val);
	bool TryAddIncludeType(ISirenType* val);
protected:
	HeapString mBaseTypeName;
	SirenCustomClass* mBaseType = nullptr;
	SirenClassAttribute mAttribute;
	Dictionary<StringRef, SirenField*> mFields;
	Dictionary<StringRef, BaseSirenCustomType*> mTypes;	//may have nest classes
	HashSet<BaseSirenCustomType*> mIncludeTypes;
};

MEDUSA_END;
