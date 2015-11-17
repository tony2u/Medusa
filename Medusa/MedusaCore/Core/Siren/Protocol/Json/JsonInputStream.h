// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"


MEDUSA_SIREN_BEGIN;

template <typename TStream>
class JsonInputStream
{
public:
	typedef char Ch;
	JsonInputStream(TStream& input)
		:mStream(input)
	{
	}


	char Peek()
	{
		return mStream.PeekChar();
	}

	uintp Tell() const
	{
		return mStream.Length();
	}

	char Take()
	{
		return mStream.ReadChar();
	}

	// not implemented for read only stream
	char* PutBegin() { MEDUSA_ASSERT_SILENT(false); return 0; }
	void Put(char c) { MEDUSA_ASSERT_SILENT(false); }
	uint PutEnd(char* begin) { MEDUSA_ASSERT_SILENT(false); return 0; }



private:
	TStream& mStream;
};





MEDUSA_SIREN_END;


