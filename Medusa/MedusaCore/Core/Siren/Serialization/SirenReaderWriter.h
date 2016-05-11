// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"

MEDUSA_BEGIN;

class SirenReaderWriter
{
public:
	SirenReaderWriter(ISirenReader& reader, ISirenWriter& writer) :mReader(reader), mWriter(writer) {}
public:
	bool Run(const ISirenType& type, ISirenType* keyType = nullptr, ISirenType* valueType = nullptr);
private:
	bool Visit(const SirenBuildinBool& type);
	bool Visit(const SirenBuildinInt8& type);
	bool Visit(const SirenBuildinUInt8& type);
	bool Visit(const SirenBuildinInt16& type);
	bool Visit(const SirenBuildinUInt16& type);
	bool Visit(const SirenBuildinInt32& type);
	bool Visit(const SirenBuildinUInt32& type);
	bool Visit(const SirenBuildinInt64& type);
	bool Visit(const SirenBuildinUInt64& type);
	bool Visit(const SirenBuildinFloat& type);
	bool Visit(const SirenBuildinDouble& type);
	bool Visit(const SirenBuildinString& type);
	bool Visit(const SirenBuildinBlob& type);
	bool Visit(const SirenBuildinList& type, const ISirenType& valueType);
	bool Visit(const SirenBuildinDictionary& type, const ISirenType& keyType, const ISirenType& valueType);
	bool Visit(const SirenCustomEnum& type);
	bool Visit(const SirenCustomClass& type);

	bool VisitFields(const SirenCustomClass& type);
protected:
	ISirenReader& mReader;
	ISirenWriter& mWriter;


};

MEDUSA_END;