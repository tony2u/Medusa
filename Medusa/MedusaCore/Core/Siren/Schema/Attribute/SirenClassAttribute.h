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

};

class SirenClassAttribute :public ISirenAttribute
{
public:
	using ISirenAttribute::ISirenAttribute;
	virtual ~SirenClassAttribute(void);

	virtual SirenClassAttribute* Clone() const override { return new SirenClassAttribute(mKeyValues); }

	SirenClassGenerateMode Mode() const { return mMode; }
	void SetMode(SirenClassGenerateMode val) { mMode = val; }

	bool Has(SirenClassGenerateMode val)const { return MEDUSA_FLAG_HAS(mMode, val); }
	bool IsGenerate()const { return Has(SirenClassGenerateMode::Generate); }
	bool IsEmbeded()const { return Has(SirenClassGenerateMode::Embeded); }
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
