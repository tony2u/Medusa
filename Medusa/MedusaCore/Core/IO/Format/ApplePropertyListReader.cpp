// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "ApplePropertyListReader.h"
#include "Core/IO/FileInfo.h"
#include "CoreLib/Common/pugixml/pugixml.hpp"
#include "Core/Log/Log.h"
#include "Core/IO/Stream/MemoryStream.h"
#include "Core/System/BitConverter.h"
#include "Core/IO/FileIdRef.h"

MEDUSA_BEGIN;

ApplePropertyListReader::ApplePropertyListReader()
{

}

ApplePropertyListReader::~ApplePropertyListReader(void)
{

}


uint ApplePropertyListReader::CheckFormat(StringRef path)
{
	switch (FileInfo::ExtractType(path))
	{
	case FileType::plist:
		return (uint)FileType::plist;
	case FileType::bplist:
		return (uint)FileType::bplist;
	default:
		break;
	}
	return 0;
}

bool ApplePropertyListReader::LoadFromData(const FileIdRef& fileId, const MemoryData& data, uint format /*= 0*/)
{
	switch ((FileType)format)
	{
	case FileType::plist:
		return ParseFromXml(fileId, data);
	case FileType::bplist:
		return ParseFromBinary(fileId, data);
	default:
		break;
	}
	return false;
}


void ApplePropertyListReader::Unload()
{
	mRoot.Clear();
}


bool ApplePropertyListReader::ParseFromXml(const FileIdRef& fileId, const MemoryData& data)
{
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_buffer(data.Data(), data.Size());
	if (!result)
	{
		Log::AssertFailedFormat("Cannot parse xml:{} because {}", fileId, result.description());
		return false;
	}

	pugi::xml_node rootNode = doc.child("plist").first_child();
	return mRoot.Parse(rootNode);
}

bool ApplePropertyListReader::ParseFromBinary(const FileIdRef& fileId, const MemoryData& data)
{
	//http://travis.wang/133/ format spec
	MemoryStream stream(data);

	//check header
	auto headerData= stream.ReadData(8, DataReadingMode::DirectMove);
	if (!headerData.IsContentEqual(MemoryData::FromStatic((byte*)"bplist00",8)))
	{
		Log::AssertFailed("Plist:Invalid binary format header");
		return false;
	}

	ApplePropertyListNode::BinaryHeader header;
	//read trailer
	stream.Seek(-32+6, SeekOrigin::End);

	int offsetByteSize = stream.ReadChar();
	header.ObjectIntByteSize = stream.ReadChar();
	stream.Skip(4);
	int offsetsCount =BitConverter::ToLittle(stream.Read<int>());
	stream.Skip(4);
	int rootObjectIndex= BitConverter::ToLittle(stream.Read<int>());
	stream.Skip(4);
	int offsetTableOffset = BitConverter::ToLittle(stream.Read<int>());

	//parse offset table
	header.Offsets.ReserveSize(offsetsCount);
	stream.Seek(offsetTableOffset, SeekOrigin::Begin);
	auto offsetBuffer= stream.Ptr();
	FOR_EACH_INT32(i, offsetsCount)
	{
		header.Offsets.NewAdd() = BitConverter::ToInt(offsetBuffer, offsetByteSize);
		offsetBuffer += offsetByteSize;
	}
	
	return mRoot.Parse(stream, header, rootObjectIndex);
}

uint ApplePropertyListReader::OnCheckFormat(StringRef path) const
{
	return CheckFormat(path);
}

MEDUSA_END;