// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "ByteBuffer.h"
#include "Core/String/StringRef.h"


MEDUSA_BEGIN;

ByteBuffer::ByteBuffer()
{
	
}

ByteBuffer::~ByteBuffer(void)
{
	
}


ByteBuffer& ByteBuffer::operator=(const ByteBuffer& other)
{
	if (this != &other)
	{
		mBuffer = other.mBuffer;
	}
	return *this;
}

ByteBuffer& ByteBuffer::operator=(ByteBuffer&& other)
{
	if (this != &other)
	{
		mBuffer = std::move(other.mBuffer);
	}
	return *this;
}

void ByteBuffer::Clear()
{
	mBuffer.Clear();
}


void ByteBuffer::Add(const void* input, size_t byteSize)
{
	mBuffer.AppendRange((const byte*)input, byteSize);
}

void ByteBuffer::Add(const StringRef& str)
{
	Add(str.c_str(), str.Length());
}

void ByteBuffer::Add(const WStringRef& str)
{
	Add(str.c_str(), str.Length()*sizeof(wchar_t));
}

void ByteBuffer::Add(byte val, size_t count /*= 1*/)
{
	mBuffer.Add(val, count);
}

void ByteBuffer::Add(bool val)
{
	mBuffer.Add((byte)val);
}

void ByteBuffer::Add(short val)
{
	Add(&val, sizeof(val));
}

void ByteBuffer::Add(ushort val)
{
	Add(&val, sizeof(val));

}

void ByteBuffer::Add(uint val)
{
	Add(&val, sizeof(val));

}

void ByteBuffer::Add(int val)
{
	Add(&val, sizeof(val));

}

void ByteBuffer::Add(uint64 val)
{

	Add(&val, sizeof(val));
}

void ByteBuffer::Add(int64 val)
{
	Add(&val, sizeof(val));

}

void ByteBuffer::Add(float val)
{
	Add(&val, sizeof(val));

}

void ByteBuffer::Add(double val)
{
	Add(&val, sizeof(val));

}

MEDUSA_END;