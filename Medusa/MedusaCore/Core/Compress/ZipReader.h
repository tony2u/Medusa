// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/String/HeapString.h"
#include "Core/String/StackString.h"
#include "Core/Memory/MemoryData.h"
#include "Core/Collection/Dictionary.h"

#include "CoreLib/Common/zip/zip.h"
#include "CoreLib/Common/zip/unzip.h"

MEDUSA_BEGIN;


class ZipReader
{
	struct ZipFileInfo
	{
		unz_file_pos Pos;
		uLong UncompressedSize;
		bool operator==(const ZipFileInfo& info)const{return Pos.num_of_file==info.Pos.num_of_file&&Pos.pos_in_zip_directory==info.Pos.pos_in_zip_directory&&UncompressedSize==info.UncompressedSize;}
	};
public:
	ZipReader();
	~ZipReader();

	bool Open(StringRef path);
	void Close();

	bool IsValid()const{return mZipFile!=nullptr;}
	bool Exists(StringRef fileName) const;
	MemoryByteData ReadAllData(StringRef fileName)const;
	static MemoryByteData DecompressGZIP(const MemoryByteData& data, size_t expectedSize);

private:
	unzFile mZipFile;
	Dictionary<HeapString,ZipFileInfo>  mFileDict;
};


MEDUSA_END;
