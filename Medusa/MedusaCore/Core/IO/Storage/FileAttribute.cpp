// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
//SIREN_BODY_INCLUDE_BEGIN
#include "FileAttribute.h"
//SIREN_BODY_INCLUDE_END
#include "Core/Math/Math.h"

MEDUSA_BEGIN;

FileAttribute::FileAttribute()
{
//SIREN_BODY_CONSTRUCT_BEGIN
	mHasher = (HasherType)0;
	mChunkSize = 4096;
	mCoders = 0;
	mPermission = (FilePermission)384;
//SIREN_BODY_CONSTRUCT_END
}

FileAttribute::FileAttribute(FilePermission permission)
{
	mHasher = (HasherType)0;
	mChunkSize = 4096;
	mCoders = 0;
	mPermission = permission;
}

FileAttribute::~FileAttribute()
{
//SIREN_BODY_DESTRUCT_BEGIN
//SIREN_BODY_DESTRUCT_END
}

void FileAttribute::UseDefaultCoder()
{
	mCoders = Math::UInt64MaxValue;
}

//SIREN_BODY_METADATA_BEGIN
SIREN_METADATA(FileAttribute, 13);
SIREN_PROPERTY_METADATA(0, FileAttribute, Hasher, 6, (HasherType)0);
SIREN_PROPERTY_METADATA(1, FileAttribute, ChunkSize, 9, 4096);
SIREN_PROPERTY_METADATA(2, FileAttribute, Coders, 6, 0);
SIREN_PROPERTY_METADATA(3, FileAttribute, Permission, 10, (FilePermission)384);
//SIREN_BODY_METADATA_END

const FileAttribute FileAttribute::Empty;
const FileAttribute FileAttribute::Readonly(FilePermission::Read);

MEDUSA_END;