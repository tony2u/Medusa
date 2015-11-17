// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.

#pragma once
#include "MedusaCorePreDeclares.h"

MEDUSA_SIREN_BEGIN;

template <typename TStream>
class BaseBinaryWriter
{
public:
	BaseBinaryWriter(TStream& stream) :mStream(stream) {}

	template<typename T>
	inline void WriteVariableUnsigned(T value)
	{
		while (value > 0x7F)
		{
			mStream.WriteChar(static_cast<char>((value & 0x7F) | 0x80));
			value >>= 7;
		}
		mStream.WriteChar(static_cast<char>(value & 0x7F));

	}
	void OnError()
	{

	}
protected:
	TStream& mStream;

};

MEDUSA_SIREN_END;
