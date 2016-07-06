// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#ifdef MEDUSA_LZMA

#include "CoreLib/Common/Lzma/7zTypes.h"

MEDUSA_BEGIN;

class LZMASeqInStream :public ISeqInStream
{
public:
	LZMASeqInStream(const IStream& stream);
	static SRes LZMARead(void *p, void *buf, size_t *size);
private:
	SRes ReadTo(void *buf, size_t *size)const;
private:
	const IStream& mStream;
};


class LZMASeqOutStream :public ISeqOutStream
{
public:
	LZMASeqOutStream(IStream& stream);
	static size_t LZMAWrite(void *p, const void *buf, size_t size);
private:
	size_t WriteData(const void *buf, size_t size);
private:
	IStream& mStream;
};


MEDUSA_END;
#endif
