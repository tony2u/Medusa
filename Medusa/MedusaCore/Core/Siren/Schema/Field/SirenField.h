// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Siren/Schema/Type/SirenTypeId.h"
#include "SirenFieldModifier.h"
#include "Core/Siren/Schema/Attribute/SirenFieldAttribute.h"
#include "Core/IO/Stream/IStreamable.h"
#include "Core/Pattern/IClone.h"
#include "Core/Siren/SirenObject.h"

MEDUSA_BEGIN;


class SirenField :public IStreamable, public IClone<SirenField>
{
public:
	SirenField();
	~SirenField(void);
public:
	ISirenType* Type() const { return mType; }
	ISirenType* KeyType() const { return mKeyType; }
	ISirenType* ValueType() const { return mValueType; }


	SirenCustomClass* ParentType() const { return mParentType; }
	void SetParentType(SirenCustomClass* val) { mParentType = val; }

	ushort Index() const { return mIndex; }
	void SetIndex(ushort val) { mIndex = val; }

	ushort Id() const;

	StringRef Name() const { return mName; }

	bool Parse(SirenAssembly& assembly, SirenCustomClass* parentClass, StringRef token, StringRef& refProto);
	bool SetAttribute(const StringRef& val);
	bool IsCompleted()const;	
	bool Link(SirenAssembly& assembly);
	virtual SirenField* Clone() const override { return new SirenField(*this); }
	bool IsRequired()const { return mAttribute.IsRequired(); }

	StringRef DefaultValueString()const { return mDefaultValueString; }
	const SirenObject& DefaultValue()const { return mDefaultValue; }
	const SirenFieldAttribute& Attribute() const { return mAttribute; }

public:
	virtual bool LoadFrom(IStream& stream)override;
	virtual bool SaveTo(IStream& stream)const override;
protected:
	ISirenType* OnFindType(SirenAssembly& assembly, SirenCustomClass* parentClass, const StringRef& name)const;
protected:
	SirenFieldAttribute mAttribute;
	HeapString mTypeName;
	HeapString mKeyTypeName;
	HeapString mValueTypeName;

	HeapString mName;
	HeapString mDefaultValueString;
	SirenObject mDefaultValue;

	ushort mIndex = 0;
	
	ISirenType* mType = nullptr;
	ISirenType* mKeyType = nullptr;
	ISirenType* mValueType = nullptr;
	SirenCustomClass* mParentType = nullptr;
};

MEDUSA_END;
