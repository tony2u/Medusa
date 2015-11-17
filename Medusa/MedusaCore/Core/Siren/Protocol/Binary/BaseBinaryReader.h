// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.

#pragma once
#include "MedusaCorePreDeclares.h"

MEDUSA_SIREN_BEGIN;

template <typename TStream>
class BaseBinaryReader
{
public:
	BaseBinaryReader(TStream& stream) :mStream(stream),  mCurrentPropertyId(0), mCurrentPropertyType(0), mCurrentKeyType(0),mCurrentValueType(0), mIsPropertyWaiting(false) {}

	template<typename T>
	inline void ReadVariableUnsigned(T& outValue)
	{
		outValue = 0;
		uint8_t c;
		uint8_t shift = 0;

		do
		{
			c = (uint8_t)mStream.ReadChar();
			T part = c & 0x7f;
			outValue += part << shift;
			shift += 7;
		} while (c >= 0x80);
	}

	bool IsEnd()const
	{
		return mStream.IsEnd();
	}

	void OnError()
	{

	}
protected:
	template<typename T>
	inline void SkipVariableUnsigned()
	{
		uint8_t c;
		do
		{
			c = (uint8_t)mStream.ReadChar();
		} while (c >= 0x80);
	}
protected:
	TStream& mStream;
	ushort mCurrentPropertyId;
	byte mCurrentPropertyType;
	byte mCurrentKeyType;
	byte mCurrentValueType;
	bool mIsPropertyWaiting;
};

MEDUSA_SIREN_END;
