// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once

#include "MedusaCorePreDeclares.h"


MEDUSA_BEGIN;

enum class FileOpenMode { ReadOnly, DestoryWriteOrCreate, AppendWriteKeepEOFOrCreate, ReadWrite, DestoryReadWriteOrCreate, AppendReadWriteClearEOFOrCreate };
enum class FileDataType { Binary, Text };
enum class FileMode { File, Directory };

enum class FileType :char
{
	Unknown = -1,

	rawimg = 1,
	png = 2,
	jpeg = 3,
	gif = 4,
	pvr = 5,

	pcm = 10,
	wav = 11,
	ogg = 12,

	fsh = 20,
	vsh = 21,
	pod = 22,
	pfx = 23,
	ttf = 24,
	fnt = 25,
	json = 26,
	xml = 27,
	bin = 28,
	atlas = 29,
	mpf = 30,	//medusa custom package file

	zip = 40,
	mpk = 41	//medusa custom package
};


enum class ImageFileType :char
{
	raw = (char)FileType::rawimg,
	png = (char)FileType::png,
	jpeg = (char)FileType::jpeg,
	gif = (char)FileType::gif,
	pvr = (char)FileType::pvr,
};

enum class AudioFileType :char
{
	pcm = (char)FileType::pcm,
	ogg = (char)FileType::ogg,
	wav = (char)FileType::wav
};

enum class ShaderFileType
{
	fsh = 5,
	vsh = 6
};

enum class FileBufferMode
{
	Full = _IOFBF,
	Line = _IOLBF,
	None = _IONBF
};


MEDUSA_END;