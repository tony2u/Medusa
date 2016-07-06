// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
MEDUSA_BEGIN;

enum class SeekOrigin
{
	Begin = SEEK_SET,
	Current = SEEK_CUR,
	End = SEEK_END
};

enum class DataReadingMode
{
	AlwaysCopy = 0,
	DirectMove = 1
};


enum class StreamDataOperation
{
	None = 0,
	Read = 1,
	Write = 2,
	ReadWrite = 3,
	Seek = 4,
	ReadSeek = 5,
	WriteSeek = 6,
	ReadWriteSeek = 7,
	Grow = 8,	//can grow size
};

enum class StreamType
{
	File,
	Memory,
	String,
	Span,
	Hash,
	Buffer,
	CodeRead,
	CodeWrite,
	BinaryBlockRead,
	BinaryBlockWrite,

};



MEDUSA_END;