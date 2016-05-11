// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.

#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Siren/Serialization/ISirenReader.h"

MEDUSA_BEGIN;

class BaseSirenBinaryReader:public ISirenReader
{
public:
	BaseSirenBinaryReader(IStream& stream)
		:mStream(stream) 
	{
	}

	template<typename T>
	inline bool ReadVariableUnsigned(T& outValue)
	{
		outValue = 0;
		uint8_t c;
		uint8_t shift = 0;

		do
		{
			int c1=mStream.ReadChar();
			if (c1<0)
			{
				return false;
			}
			c = (uint8_t)c1;
			T part = c & 0x7f;
			outValue += part << shift;
			shift += 7;
		} while (c >= 0x80);

		return true;
	}

	virtual bool IsEnd()const override
	{
		return mStream.IsEnd();
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
	IStream& mStream;
	ushort mCurrentFieldId=0;
	byte mCurrentFieldType=0;
	byte mCurrentKeyType=0;
	byte mCurrentValueType=0;
	bool mIsFieldWaiting=false;
};

MEDUSA_END;
