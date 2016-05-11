// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
MEDUSA_BEGIN;

class SirenJsonOutputStream
{
public:
	SirenJsonOutputStream(IStream& output)
		: mOutput(output)
	{
	}

	// not implemented for write-only stream
	char Peek() { MEDUSA_ASSERT_SILENT(false); return 0; }
	uint Tell() const { MEDUSA_ASSERT_SILENT(false); return 0; }
	char Take() { MEDUSA_ASSERT_SILENT(false); return 0; }

	char* PutBegin()
	{
		return 0;
	}

	void Put(char c)
	{
		mOutput.WriteChar(c);
	}

	uint PutEnd(char* begin)
	{
		MEDUSA_ASSERT_SILENT(begin == 0);
		return 0;
	}

	void Flush() 
	{
		mOutput.WriteChar('\0');
	}

private:
	IStream& mOutput;
};



MEDUSA_END;


