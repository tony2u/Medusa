// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "BinaryPackageBlockHeader.h"
#include "Core/IO/Stream/IStream.h"
MEDUSA_BEGIN;


BinaryPackageBlockHeader::BinaryPackageBlockHeader()
{
	Id= Math::UIntMaxValue;
	PrevId = Math::UIntMaxValue;
	NextId = Math::UIntMaxValue;
	LeftSize = 0;
}

int BinaryPackageBlockHeader::Compare(const BinaryPackageBlockHeader& other) const
{
	//Id could maybe bigger than max int
	if (Id>other.Id)
	{
		return 1;
	}
	else if (Id < other.Id)
	{
		return -1;
	}
	return 0;
}

bool BinaryPackageBlockHeader::ParseFrom(const IStream& stream)
{
	stream.ReadTo(Id);

	stream.ReadTo(PrevId);
	stream.ReadTo(NextId);
	stream.ReadTo(LeftSize);
	return true;
}


bool BinaryPackageBlockHeader::WriteTo(IStream& stream)
{
	stream.Write(Id);
	stream.Write(PrevId);
	stream.Write(NextId);
	stream.Write(LeftSize);
	return true;
}


MEDUSA_END;

