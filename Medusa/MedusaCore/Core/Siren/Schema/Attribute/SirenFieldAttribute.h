// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "ISirenAttribute.h"

MEDUSA_BEGIN;

enum class SirenFieldGenerateMode
{
	None = 0,
	Optional = 1,

	ForceKeyToPtr = 2,
	ForceValueToPtr = 4,
	AddDictionaryMethods = 8,

	SuppressMethod = 16,

};

class SirenFieldAttribute:public ISirenAttribute
{
public:
	using ISirenAttribute::ISirenAttribute;
	~SirenFieldAttribute(void);
	virtual SirenFieldAttribute* Clone() const override { return new SirenFieldAttribute(mKeyValues); }

	bool IsRequired()const;
	SirenFieldGenerateMode Mode() const { return mMode; }
	void SetMode(SirenFieldGenerateMode val) { mMode = val; }
	bool Has(SirenFieldGenerateMode val)const { return MEDUSA_FLAG_HAS(mMode, val); }

	StringRef Modifier()const;
public:
	virtual bool LoadFrom(IStream& stream)override;
	virtual bool SaveTo(IStream& stream)const override;
protected:
	virtual bool OnLoaded() override;
protected:
	SirenFieldGenerateMode mMode= SirenFieldGenerateMode::None;
};

MEDUSA_END;
