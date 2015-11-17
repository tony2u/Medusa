// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Math/Math.h"

MEDUSA_BEGIN;

struct BinaryPackageBlockHeader
{
	BinaryPackageBlockHeader();
	uint32 Id;
	uint32 PrevId;
	uint32 NextId;
	uint32 LeftSize;	//<block size

	bool operator==(const BinaryPackageBlockHeader& other)const { return Id == other.Id; }
	int Compare(const BinaryPackageBlockHeader& other)const;

	bool ParseFrom(const IStream& stream);
	bool WriteTo(IStream& stream);

	bool HasPrev()const { return PrevId != Math::UIntMaxValue; }
	bool HasNext()const { return NextId != Math::UIntMaxValue; }
	bool IsFree(uint blockSize)const { return LeftSize == blockSize; }
};


MEDUSA_END;