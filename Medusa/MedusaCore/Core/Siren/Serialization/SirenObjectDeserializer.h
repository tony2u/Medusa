// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"

MEDUSA_BEGIN;

class SirenObjectDeserializer
{
public:
	SirenObjectDeserializer(ISirenReader& reader) :mReader(reader) {}
public:
	bool Deserialize(SirenObject& obj, const ISirenType& type, ISirenType* keyType=nullptr, ISirenType* valueType=nullptr);
private:
	bool Visit(SirenObject& obj, const SirenBuildinBool& type);
	bool Visit(SirenObject& obj, const SirenBuildinInt8& type);
	bool Visit(SirenObject& obj, const SirenBuildinUInt8& type);
	bool Visit(SirenObject& obj, const SirenBuildinInt16& type);
	bool Visit(SirenObject& obj, const SirenBuildinUInt16& type);
	bool Visit(SirenObject& obj, const SirenBuildinInt32& type);
	bool Visit(SirenObject& obj, const SirenBuildinUInt32& type);
	bool Visit(SirenObject& obj, const SirenBuildinInt64& type);
	bool Visit(SirenObject& obj, const SirenBuildinUInt64& type);
	bool Visit(SirenObject& obj, const SirenBuildinFloat& type);
	bool Visit(SirenObject& obj, const SirenBuildinDouble& type);
	bool Visit(SirenObject& obj, const SirenBuildinString& type);
	bool Visit(SirenObject& obj, const SirenBuildinBlob& type);
	bool Visit(SirenObject& obj, const SirenBuildinList& type, const ISirenType& valueType);
	bool Visit(SirenObject& obj, const SirenBuildinDictionary& type, const ISirenType& keyType, const ISirenType& valueType);
	bool Visit(SirenObject& obj, const SirenCustomEnum& type);
	bool Visit(SirenObject& obj, const SirenCustomClass& type);
	
	bool VisitFields(SirenObject& obj, const SirenCustomClass& type);
protected:
	ISirenReader& mReader;

};

MEDUSA_END;