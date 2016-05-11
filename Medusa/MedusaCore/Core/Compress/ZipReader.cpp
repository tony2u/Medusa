// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "Core/Compress/ZipReader.h"
#include "Core/IO/Path.h"
#include "Core/Log/Log.h"

MEDUSA_BEGIN;

ZipReader::ZipReader()
{
	mZipFile=nullptr;
}


ZipReader::~ZipReader()
{
	Close();
}

bool ZipReader::Open( StringRef path)
{
	Close();
	mZipFile = unzOpen(path.c_str());
	if (mZipFile!=nullptr)
	{
		StackString<Path::MaxPathLength> outFileName;
		//unz_file_info64 outFileInfo;

		int err = unzGoToFirstFile(mZipFile);
		//int err = unzGoToFirstFile(mZipFile, &outFileInfo, outFileName.c_str(), static_cast<uLong>((outFileName.Size() - 1)*sizeof(char)));

		outFileName.ForceUpdateLength();
		while (err == UNZ_OK)
		{
			unz_file_pos posInfo;
			int posErr = unzGetFilePos(mZipFile, &posInfo);
			if (posErr == UNZ_OK)
			{
				//TODO: invoke unzGetCurrentFileInfo
				ZipFileInfo entry;
				entry.Pos = posInfo;
				//entry.UncompressedSize = (uLong)outFileInfo.uncompressed_size;
				mFileDict.Add(outFileName.ToString(),entry);
			}
			err = unzGoToNextFile(mZipFile);
			//err = unzGoToNextFile(mZipFile, &outFileInfo, outFileName.c_str(), static_cast<uLong>((outFileName.Size() - 1)*sizeof(char)));

			outFileName.ForceUpdateLength();
		}


		return true;
	}

	return false;
}


void ZipReader::Close()
{
	if (mZipFile!=nullptr)
	{
		unzClose(mZipFile);
		mZipFile=nullptr;
	}

	mFileDict.Clear();

}

bool ZipReader::Exists(StringRef fileName) const
{
	return mFileDict.ContainsOtherKey(fileName,fileName.HashCode());
}

MemoryData ZipReader::ReadAllData(StringRef fileName)const
{
	MemoryData result;

	if (mZipFile==nullptr||fileName.IsEmpty())
	{
		return result;
	}


	const ZipFileInfo* zipEntryInfo=mFileDict.TryGetByOtherKey(fileName,fileName.HashCode());
	if (zipEntryInfo==nullptr)
	{
		return result;
	}

	int err = unzGoToFilePos(mZipFile, (unz_file_pos*)&zipEntryInfo->Pos);
	if (err!=UNZ_OK)
	{
		return result;
	}

	err = unzOpenCurrentFile(mZipFile);
	if (err!=UNZ_OK)
	{
		return result;
	}

	result=MemoryData::Alloc(zipEntryInfo->UncompressedSize);
	int readSize = unzReadCurrentFile(mZipFile, result.MutableData(), (uint)zipEntryInfo->UncompressedSize);
	Log::Assert(readSize==(int)zipEntryInfo->UncompressedSize,"Invalid zip file size.");	//readSize could be 0 because we may have zero file such as "StringTable-enus.bin"
	unzCloseCurrentFile(mZipFile);

	return result;
}


MemoryData ZipReader::DecompressGZIP(const MemoryData& data, size_t expectedSize)
{
	MemoryData result = MemoryData::Alloc(expectedSize);
	int ret;
	z_stream strm;

	strm.zalloc = Z_NULL;
	strm.zfree = Z_NULL;
	strm.opaque = Z_NULL;
	strm.next_in = (byte*)data.Data();
	strm.avail_in = (uint)data.Size();
	strm.next_out = result.MutableData();
	strm.avail_out = (uint)result.Size();

	ret = inflateInit2(&strm, 15 + 32);

	if (ret != Z_OK)
	{
		return MemoryData::Empty;
	}

	do
	{
		ret = inflate(&strm, Z_SYNC_FLUSH);

		switch (ret)
		{
			case Z_NEED_DICT:
			case Z_STREAM_ERROR:
				ret = Z_DATA_ERROR;
			case Z_DATA_ERROR:
			case Z_MEM_ERROR:
				inflateEnd(&strm);
				return MemoryData::Empty;
		}

		if (ret != Z_STREAM_END)
		{
			
			byte* newData = (byte *)realloc(result.MutableData(), result.Size() * 2);
			result.ForceSetDataAndSize(newData, result.Size() * 2);

			if (!result.IsValid())
			{
				inflateEnd(&strm);
				return MemoryData::Empty;
			}

			strm.next_out = (Bytef *)(result.Data() + result.Size());
			strm.avail_out = (uint)result.Size();
		}
	} while (ret != Z_STREAM_END);

	if (strm.avail_in != 0)
	{
		return MemoryData::Empty;
	}

	inflateEnd(&strm);

	return result;
}

MEDUSA_END;

