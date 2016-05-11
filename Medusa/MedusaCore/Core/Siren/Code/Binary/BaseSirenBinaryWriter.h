// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.

#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Siren/Serialization/ISirenWriter.h"

MEDUSA_BEGIN;

class BaseSirenBinaryWriter:public ISirenWriter
{
public:
	BaseSirenBinaryWriter(IStream& stream)
		:mStream(stream) {}

	template<typename T>
	inline bool WriteVariableUnsigned(T value)
	{
		while (value > 0x7F)
		{
			mStream.WriteChar(static_cast<char>((value & 0x7F) | 0x80));
			value >>= 7;
		}
		mStream.WriteChar(static_cast<char>(value & 0x7F));
		return true;
	}
protected:
	IStream& mStream;

};

MEDUSA_END;
