// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "BinaryPackageHeader.h"
#include "Core/Log/Log.h"
#include "Core/IO/Stream/IStream.h"
#include "BinaryPackageBlockHeader.h"
#include "Core/IO/Storage/FileStorage.h"
#include "Core/Hash/MD5.h"

MEDUSA_BEGIN;

BinaryPackageHeader::BinaryPackageHeader(PackageFlags flag/*=PackageFlags::None*/)
{
	Reset();
	mFlag = flag;
}

void BinaryPackageHeader::Reset()
{
	mSignature = FixedSignature;
	mFormatVersion = CurrentVersion;
	mHeaderSize = sizeof(BinaryPackageHeader);
	mContentVersion = 0;
	mFlag = PackageFlags::None;
	mBlockSize = FileStorage::DefaultBlockSize;
	mBlockCount = 0;
	mFirstFreeBlockId = Math::UIntMaxValue;
	mFreeBlockCount = 0;

	mCoders = 0;
	mHasher = HasherType::MD5;
	Memory::SetZero(mKeyHash);
}

bool BinaryPackageHeader::ParseFrom(const IStream& stream)
{
	mSignature = stream.Read<uint32>();
	if (mSignature != FixedSignature)
	{
		Log::FormatError("Invalid MPACK signature:{}", mSignature);
		return false;
	}

	mFormatVersion = stream.Read<uint32>();
	if (mFormatVersion != CurrentVersion)
	{
		Log::FormatError("Invalid MPACK version:{}", mFormatVersion);
		return false;
	}

	mHeaderSize = stream.Read<uint>();
	mContentVersion = stream.Read<uint>();

	mFlag.ForceSet(stream.Read<uint>());

	mBlockSize = stream.Read<uint>();
	mBlockCount = stream.Read<uint>();

	mFirstFreeBlockId = stream.Read<uint>();
	mFreeBlockCount = stream.Read<uint>();

	mHasher = (HasherType)stream.Read<uint>();
	mCoders = stream.Read<uint64>();

	MemoryByteData outData = MemoryByteData::FromStatic(mKeyHash);
	stream.ReadDataTo(outData);

	return true;
}

bool BinaryPackageHeader::WriteTo(IStream& stream)
{
	stream.Write(FixedSignature);
	stream.Write(CurrentVersion);
	stream.Write(FixedHeaderSize);
	stream.Write(mContentVersion);
	stream.Write(mFlag.ToUInt());
	stream.Write(mBlockSize);
	stream.Write(mBlockCount);
	stream.Write(mFirstFreeBlockId);
	stream.Write(mFreeBlockCount);

	stream.Write((uint32)mHasher);
	stream.Write(mCoders);

	MemoryByteData data = MemoryByteData::FromStatic(mKeyHash);
	stream.WriteData(data);

	return true;
}


void BinaryPackageHeader::SetKey(const MemoryByteData& val)
{
	if (val.IsNull())
	{
		Memory::SetZero(mKeyHash);
	}
	else
	{
		MD5 md5;
		md5.Process(val.Data(), val.Size());
		md5.Final();
		MemoryByteData hashData = MemoryByteData::FromStatic(md5.Digest(), MD5::DigestSize);
		MemoryByteData data = MemoryByteData::FromStatic(mKeyHash);
		data.Copy(hashData);
	}

}

bool BinaryPackageHeader::ValidateKey(const MemoryByteData& key) const
{
	MemoryByteData data = MemoryByteData::FromStatic(mKeyHash);
	if (key.IsNull())
	{
		return Memory::EqualsAll(mKeyHash, (byte)0);
	}

	MD5 md5;
	md5.Process(key.Data(), key.Size());
	md5.Final();

	MemoryByteData hashData = MemoryByteData::FromStatic(md5.Digest(), MD5::DigestSize);
	return data.IsContentEqual(hashData);
}

uint32 BinaryPackageHeader::BlockHeadersOffset() const
{
	return mHeaderSize + mBlockSize*mBlockCount;
}

float BinaryPackageHeader::SpaceUsage() const
{
	if (mBlockCount==0)
	{
		return 0.f;
	}
	return 1.f - (float)mFreeBlockCount / mBlockCount;
}

uint32 BinaryPackageHeader::FirstBlockOffset() const
{
	return mHeaderSize;
}

uint32 BinaryPackageHeader::GetBlockOffset(uint blockId) const
{
	return mHeaderSize + blockId*mBlockSize;
}

constexpr uint32 BinaryPackageHeader::FixedSignature;	// 'KAPM';	//Little endian, I mean 'MPAK'
constexpr uint32 BinaryPackageHeader::CurrentVersion;
constexpr uint32 BinaryPackageHeader::FixedHeaderSize;

MEDUSA_END;

