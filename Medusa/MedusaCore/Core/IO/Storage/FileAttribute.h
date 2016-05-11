// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Siren/SirenHeader.h"

//SIREN_HEADER_INCLUDE_BEGIN
#include "Core/Hash/HasherType.h"
#include "Core/IO/Storage/FilePermission.h"
//SIREN_HEADER_INCLUDE_END

MEDUSA_BEGIN;

class FileAttribute
{
public:
	const static FileAttribute Empty;
	const static FileAttribute Readonly;
	struct Schema;
	FileAttribute();
	~FileAttribute();
	FileAttribute(FilePermission permission);

//SIREN_HEADER_METHOD_BEGIN
public:
	SIREN_METHOD(HasherType, Hasher);
	SIREN_METHOD(uint, ChunkSize);
	SIREN_METHOD(uint64, Coders);
	SIREN_METHOD(FilePermission, Permission);
//SIREN_HEADER_METHOD_END
public:
	bool IsTrivial()const { return mCoders == 0; }
	bool IsReadonly()const { return !MEDUSA_FLAG_HAS(mPermission, FilePermission::Write); }
	void UseDefaultCoder();
//SIREN_HEADER_FIELD_BEGIN
protected:
	HasherType mHasher;
	uint mChunkSize;
	uint64 mCoders;
	FilePermission mPermission;
//SIREN_HEADER_FIELD_END
};

//SIREN_HEADER_SCHEMA_BEGIN
struct FileAttribute::Schema
{
	SIREN_FIELD(0, 0, Required, FileAttribute, HasherType, mHasher);
	SIREN_FIELD(1, 1, Optional, FileAttribute, uint, mChunkSize);
	SIREN_FIELD(2, 2, Optional, FileAttribute, uint64, mCoders);
	SIREN_FIELD(3, 3, Optional, FileAttribute, FilePermission, mPermission);
	SIREN_FIELDS_4(void,FileAttribute);
};//SIREN_HEADER_SCHEMA_END

MEDUSA_END;