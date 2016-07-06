// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "ISirenAttribute.h"

MEDUSA_BEGIN;

enum class SirenClassGenerateMode
{
	None = 0,
	Generate = 1,
	Suppress = 2,
	Embeded = 4 | Generate,

	SuppressCompare = 8,
	SuppressCopy = 16,

	SirenConfig = 32 | SuppressCompare | SuppressCopy,
	Struct = 64,
};

class SirenClassAttribute :public ISirenAttribute
{
public:
	SirenClassAttribute() {}
	SirenClassAttribute(const StringPropertySet& val) :ISirenAttribute(val) {}
	SirenClassAttribute(SirenClassGenerateMode mode, const StringRef& dir);

	virtual ~SirenClassAttribute(void);

	virtual SirenClassAttribute* Clone() const override { return new SirenClassAttribute(mMode, mDir); }

	SirenClassGenerateMode Mode() const { return mMode; }
	void SetMode(SirenClassGenerateMode val) { mMode = val; }
	void AddMode(SirenClassGenerateMode val) { MEDUSA_FLAG_ADD(mMode,val); }
	void RemoveMode(SirenClassGenerateMode val) { MEDUSA_FLAG_REMOVE(mMode, val); }

	bool Has(SirenClassGenerateMode val)const { return MEDUSA_FLAG_HAS(mMode, val); }
	bool IsGenerate()const { return Has(SirenClassGenerateMode::Generate); }
	bool IsEmbeded()const { return Has(SirenClassGenerateMode::Embeded); }
	bool IsStruct()const { return Has(SirenClassGenerateMode::Struct); }

	StringRef Directory()const { return mDir; }

public:
	virtual bool LoadFrom(IStream& stream)override;
	virtual bool SaveTo(IStream& stream)const override;
protected:
	virtual bool OnLoaded() override;
protected:
	SirenClassGenerateMode mMode = SirenClassGenerateMode::Generate;
	HeapString mDir;
};

MEDUSA_END;
