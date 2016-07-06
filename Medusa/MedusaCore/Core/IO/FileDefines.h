// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once

#include "MedusaCorePreDeclares.h"
#include "Core/String/StringRef.h"


MEDUSA_BEGIN;

enum class FileOpenMode { ReadOnly, DestoryWriteOrCreate, AppendWriteKeepEOFOrCreate, ReadWrite, DestoryReadWriteOrCreate, AppendReadWriteClearEOFOrCreate };
enum class FileDataType { Binary, Text };
enum class FileMode { File, Directory };

enum class FileType :char
{
	None = 0,

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
	zip = 30,
	tmx = 31,	//tiled map 
	xaml = 32,	//xaml file
	plist = 33,	//apple plist file
	bplist = 34,	//apple binary plist file

	matlas = 40,	//medusa custom atlas file
	mpk = 41,	//medusa custom package
	mp = 42,	//medusa custom siren proto file
	mpb = 43,	//medusa custom siren assembly
	csb = 44,

	lua = 45,
	ttc = 46,

	Count = 47,
};


namespace FileExtensions
{
	const extern StringRef png;
	const extern StringRef jpeg;
	const extern StringRef jpg;

	const extern StringRef gif;
	const extern StringRef pvr;

	const extern StringRef pcm;
	const extern StringRef wav;
	const extern StringRef ogg;

	const extern StringRef fsh;
	const extern StringRef vsh;
	const extern StringRef pod;
	const extern StringRef pfx;
	const extern StringRef ttf;
	const extern StringRef ttc;

	const extern StringRef fnt;
	const extern StringRef json;
	const extern StringRef xml;
	const extern StringRef bin;
	const extern StringRef atlas;
	const extern StringRef zip;
	const extern StringRef tmx;
	const extern StringRef xaml;
	const extern StringRef plist;
	const extern StringRef bplist;



	const extern StringRef matlas;
	const extern StringRef mpk;
	const extern StringRef mp;
	const extern StringRef mpb;
	const extern StringRef csb;
	const extern StringRef lua;





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
	fsh = (char)FileType::fsh,
	vsh = (char)FileType::vsh
};

enum class ScriptFileType
{
	lua = (char)FileType::lua,
};

enum class FileBufferMode
{
	Full = _IOFBF,
	Line = _IOLBF,
	None = _IONBF
};

enum class FileShareMode
{
	ReadWrite = _SH_DENYNO,	//Permits read and write access.
	Write = _SH_DENYRD,	//Denies read access to the file.
	None = _SH_DENYRW,	//Denies read and write access to the file.
	Read = _SH_DENYWR	//Denies write access to the file.
};

#define _SH_DENYRW      0x10    // deny read/write mode
#define _SH_DENYWR      0x20    // deny write mode
#define _SH_DENYRD      0x30    // deny read mode
#define _SH_DENYNO      0x40    // deny none mode
#define _SH_SECURE      0x80    // secure mode

MEDUSA_END;