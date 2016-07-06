// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Pattern/Property/StringPropertySet.h"
#include "Core/IO/Stream/IStreamable.h"
#include "Core/Pattern/IClone.h"

MEDUSA_BEGIN;


class ISirenAttribute :public IStreamable, public IClone<ISirenAttribute>
{
public:
	ISirenAttribute();
	ISirenAttribute(const StringPropertySet& val);

	virtual ~ISirenAttribute(void);
public:
	const StringPropertySet& KeyValues() const { return mKeyValues; }
	StringPropertySet& MutalbeKeyValues() { return mKeyValues; }

	bool Load(const StringRef& str);
	bool AddAttribute(StringRef name, StringRef val);

	HeapString ToString()const
	{
		return mKeyValues.ToString();
	}
public:
	virtual bool LoadFrom(IStream& stream)override;
	virtual bool SaveTo(IStream& stream)const override;
protected:
	virtual bool OnLoaded() { return true; }
protected:
	StringPropertySet mKeyValues;
	
};

MEDUSA_END;
