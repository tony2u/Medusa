// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/String/HeapString.h"
#include "Core/IO/Stream/IStreamable.h"
#include "Core/Pattern/IClone.h"
#include "Core/Siren/Schema/Type/SirenTypeId.h"

MEDUSA_BEGIN;

class ISirenType :public IStreamable, public IClone<ISirenType>
{
public:
	ISirenType();
	ISirenType(const StringRef& name);
	virtual ~ISirenType(void);
public:
	virtual bool IsBuildIn()const { return false; }
	virtual bool IsTemplate()const { return false; }
	virtual bool IsCustomClass()const { return false; }
	virtual bool IsCustomEnum()const { return false; }
public:
	StringRef Name() const { return mName; }
	HeapString& MutableName() { return mName; }
	void SetName(const StringRef& val) { mName = val; }

	StringRef FullName() const { return mFullName; }
	virtual SirenTypeId Id()const=0;

public:
	virtual bool Parse(SirenAssembly& assembly, StringRef& refProto) { return false; };
	virtual bool Link(SirenAssembly& assembly) { return true; }
	virtual bool IsCompleted()const { return true; }

public:
	virtual bool LoadFrom(IStream& stream)override;
	virtual bool SaveTo(IStream& stream)const override;
protected:
	HeapString mName;
	HeapString mFullName;

};

MEDUSA_END;
