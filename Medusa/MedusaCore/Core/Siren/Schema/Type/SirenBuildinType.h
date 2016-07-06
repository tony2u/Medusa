// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "ISirenType.h"
MEDUSA_BEGIN;


class SirenBuildinType :public ISirenType
{
public:
	SirenBuildinType(const StringRef& name);
	virtual ~SirenBuildinType(void);
public:
	virtual bool IsBuildIn()const override { return true; }
	virtual bool SaveTo(IStream& stream)const override { return true; }
};



class SirenBuildinBool :public SirenBuildinType
{
public:
	using SirenBuildinType::SirenBuildinType;
	virtual SirenTypeId Id()const override { return SirenTypeId::Bool; }
	virtual SirenBuildinBool* Clone() const override { return (SirenBuildinBool*)this; }	//return self
};

class SirenBuildinInt8 :public SirenBuildinType
{
public:
	using SirenBuildinType::SirenBuildinType;
	virtual SirenTypeId Id()const override { return SirenTypeId::Int8; }
	virtual SirenBuildinInt8* Clone() const override { return (SirenBuildinInt8*)this; }	//return self
};

class SirenBuildinUInt8 :public SirenBuildinType
{
public:
	using SirenBuildinType::SirenBuildinType;
	virtual SirenTypeId Id()const override { return SirenTypeId::UInt8; }
	virtual SirenBuildinUInt8* Clone() const override { return (SirenBuildinUInt8*)this; }	//return self
};

class SirenBuildinInt16 :public SirenBuildinType
{
public:
	using SirenBuildinType::SirenBuildinType;
	virtual SirenTypeId Id()const override { return SirenTypeId::Int16; }
	virtual SirenBuildinInt16* Clone() const override { return (SirenBuildinInt16*)this; }	//return self
};

class SirenBuildinUInt16 :public SirenBuildinType
{
public:
	using SirenBuildinType::SirenBuildinType;
	virtual SirenTypeId Id()const override { return SirenTypeId::UInt16; }
	virtual SirenBuildinUInt16* Clone() const override { return (SirenBuildinUInt16*)this; }	//return self
};

class SirenBuildinInt32 :public SirenBuildinType
{
public:
	using SirenBuildinType::SirenBuildinType;
	virtual SirenTypeId Id()const override { return SirenTypeId::Int32; }
	virtual SirenBuildinInt32* Clone() const override { return (SirenBuildinInt32*)this; }	//return self
};

class SirenBuildinUInt32 :public SirenBuildinType
{
public:
	using SirenBuildinType::SirenBuildinType;
	virtual SirenTypeId Id()const override { return SirenTypeId::UInt32; }
	virtual SirenBuildinUInt32* Clone() const override { return (SirenBuildinUInt32*)this; }	//return self
};

class SirenBuildinInt64 :public SirenBuildinType
{
public:
	using SirenBuildinType::SirenBuildinType;
	virtual SirenTypeId Id()const override { return SirenTypeId::Int64; }
	virtual SirenBuildinInt64* Clone() const override { return (SirenBuildinInt64*)this; }	//return self
};

class SirenBuildinUInt64 :public SirenBuildinType
{
public:
	using SirenBuildinType::SirenBuildinType;
	virtual SirenTypeId Id()const override { return SirenTypeId::UInt64; }
	virtual SirenBuildinUInt64* Clone() const override { return (SirenBuildinUInt64*)this; }	//return self
};


class SirenBuildinFloat :public SirenBuildinType
{
public:
	using SirenBuildinType::SirenBuildinType;
	virtual SirenTypeId Id()const override { return SirenTypeId::Float; }
	virtual SirenBuildinFloat* Clone() const override { return (SirenBuildinFloat*)this; }	//return self
};

class SirenBuildinDouble :public SirenBuildinType
{
public:
	using SirenBuildinType::SirenBuildinType;
	virtual SirenTypeId Id()const override { return SirenTypeId::Double; }
	virtual SirenBuildinDouble* Clone() const override { return (SirenBuildinDouble*)this; }	//return self
};

class SirenBuildinString :public SirenBuildinType
{
public:
	using SirenBuildinType::SirenBuildinType;
	virtual SirenTypeId Id()const override { return SirenTypeId::String; }
	virtual SirenBuildinString* Clone() const override { return (SirenBuildinString*)this; }	//return self
};

class SirenBuildinBlob :public SirenBuildinType
{
public:
	using SirenBuildinType::SirenBuildinType;
	virtual SirenTypeId Id()const override { return SirenTypeId::Blob; }
	virtual SirenBuildinBlob* Clone() const override { return (SirenBuildinBlob*)this; }	//return self
};

class SirenBuildinList :public SirenBuildinType
{
public:
	using SirenBuildinType::SirenBuildinType;
	virtual bool IsTemplate()const override { return true; }
	virtual SirenTypeId Id()const override { return SirenTypeId::List; }
	virtual SirenBuildinList* Clone() const override { return (SirenBuildinList*)this; }	//return self

};

class SirenBuildinDictionary :public SirenBuildinType
{
public:
	using SirenBuildinType::SirenBuildinType;
	virtual bool IsTemplate()const override { return true; }
	virtual SirenTypeId Id()const override { return SirenTypeId::Dictionary; }
	virtual SirenBuildinDictionary* Clone() const override { return (SirenBuildinDictionary*)this; }	//return self

};

MEDUSA_END;
