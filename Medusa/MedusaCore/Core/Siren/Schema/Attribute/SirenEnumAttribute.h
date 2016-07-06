// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "ISirenAttribute.h"

MEDUSA_BEGIN;

enum class SirenEnumGenerateMode
{
	None = 0,
	Generate = 1,
	Suppress = 2,

	CustomEnum = 8,
	CustomFlag = 16,
};

class SirenEnumAttribute:public ISirenAttribute
{
public:
	SirenEnumAttribute() {}
	SirenEnumAttribute(const StringPropertySet& val) :ISirenAttribute(val) {}

	SirenEnumAttribute(SirenEnumGenerateMode mode, const StringRef& dir);
	~SirenEnumAttribute(void);
	virtual SirenEnumAttribute* Clone() const override { return new SirenEnumAttribute(mMode,mDir); }
	SirenEnumGenerateMode Mode() const { return mMode; }
	void SetMode(SirenEnumGenerateMode val) { mMode = val; }
	bool Has(SirenEnumGenerateMode val)const { return MEDUSA_FLAG_HAS(mMode, val); }
	bool IsGenerate()const { return Has(SirenEnumGenerateMode::Generate); }
	StringRef Directory()const { return  mDir; }
public:
	virtual bool LoadFrom(IStream& stream)override;
	virtual bool SaveTo(IStream& stream)const override;
protected:
	virtual bool OnLoaded() override;
protected:
	SirenEnumGenerateMode mMode= SirenEnumGenerateMode::Generate;
	HeapString mDir;

};

MEDUSA_END;
