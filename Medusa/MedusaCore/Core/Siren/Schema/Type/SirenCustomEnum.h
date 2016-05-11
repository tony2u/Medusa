// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "BaseSirenCustomType.h"
#include "Core/Collection/List.h"
#include "Core/Siren/Schema/Field/SirenField.h"
#include "Core/Siren/Schema/Attribute/SirenEnumAttribute.h"

MEDUSA_BEGIN;


class SirenCustomEnum:public BaseSirenCustomType
{
public:
	SirenCustomEnum();
	virtual ~SirenCustomEnum(void);
public:
	virtual bool IsCustomClass()const { return false; }
	virtual bool IsCustomEnum()const { return true; }

	virtual bool Parse(SirenAssembly& assembly, StringRef& refProto)override;
	virtual bool AddAttribute(StringRef name, StringRef val) override;
	virtual bool SetAttribute(const StringRef& val)override;
	virtual bool Merge(const BaseSirenCustomType& other) override { return false; }
	virtual SirenCustomEnum* Clone() const override{ return new SirenCustomEnum(*this); }
	virtual SirenTypeId Id()const override { return SirenTypeId::Enum; }

	bool HasValue(int val)const;
	bool HasField(const StringRef& name)const;

	int GetValue(const StringRef& name)const;
	const SirenEnumAttribute& Attribute() const { return mAttribute; }

	virtual bool IsGenerate()const override { return mAttribute.IsGenerate(); }
	const List<HeapString>& FieldNames() const { return mFieldNames; }
	const List<int>& FieldValues() const { return mFieldValues; }

	StringRef UnderlyType() const { return mUnderlyType; }
	virtual StringRef Directory()const override { return mAttribute.Directory(); }

public:
	virtual bool LoadFrom(IStream& stream)override;
	virtual bool SaveTo(IStream& stream)const override;
protected:
	bool AddField(const StringRef& name, int val);
	static bool ValidateUnderlyType(SirenAssembly& assembly, StringRef val);
protected:
	SirenEnumAttribute mAttribute;

	List<HeapString> mFieldNames;	//to keep enum in order, so do not use dictionary
	List<int> mFieldValues;

	HeapString mUnderlyType;
};

MEDUSA_END;
