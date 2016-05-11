// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"


MEDUSA_BEGIN;

class SirenObjectSerializer
{
public:
	SirenObjectSerializer(ISirenWriter& writer) :mWriter(writer) {}
public:
	bool Serialize(const SirenObject& obj, const ISirenType& type, ISirenType* keyType=nullptr, ISirenType* valueType=nullptr);
private:
	bool Visit(const SirenObject& obj, const SirenBuildinBool& type);
	bool Visit(const SirenObject& obj, const SirenBuildinInt8& type);
	bool Visit(const SirenObject& obj, const SirenBuildinUInt8& type);
	bool Visit(const SirenObject& obj, const SirenBuildinInt16& type);
	bool Visit(const SirenObject& obj, const SirenBuildinUInt16& type);
	bool Visit(const SirenObject& obj, const SirenBuildinInt32& type);
	bool Visit(const SirenObject& obj, const SirenBuildinUInt32& type);
	bool Visit(const SirenObject& obj, const SirenBuildinInt64& type);
	bool Visit(const SirenObject& obj, const SirenBuildinUInt64& type);
	bool Visit(const SirenObject& obj, const SirenBuildinFloat& type);
	bool Visit(const SirenObject& obj, const SirenBuildinDouble& type);
	bool Visit(const SirenObject& obj, const SirenBuildinString& type);
	bool Visit(const SirenObject& obj, const SirenBuildinBlob& type);
	bool Visit(const SirenObject& obj, const SirenBuildinList& type, const ISirenType& valueType);
	bool Visit(const SirenObject& obj, const SirenBuildinDictionary& type, const ISirenType& keyType, const ISirenType& valueType);
	bool Visit(const SirenObject& obj, const SirenCustomEnum& type);
	bool Visit(const SirenObject& obj, const SirenCustomClass& type);
	bool VisitFields(const SirenObject& obj, const SirenCustomClass& type);
	
protected:
	ISirenWriter& mWriter;

};

MEDUSA_END;