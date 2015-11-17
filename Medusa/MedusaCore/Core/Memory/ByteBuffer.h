// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Collection/List.h"
MEDUSA_BEGIN;


class ByteBuffer
{
public:
	ByteBuffer();
	~ByteBuffer(void);

	ByteBuffer(const ByteBuffer& other):mBuffer(other.mBuffer){}
	ByteBuffer(ByteBuffer&& other) :mBuffer(std::move(other.mBuffer)) {}

	ByteBuffer& operator=(const ByteBuffer& other);
	ByteBuffer& operator=(ByteBuffer&& other);



	void Clear();

	const byte* Buffer()const { return mBuffer.Items(); }
	size_t Size()const { return mBuffer.Count(); }

	void Add(const void* input, size_t byteSize);
	void Add(const StringRef& str);
	void Add(const WStringRef& str);

	void Add(byte val, size_t count = 1);
	void Add(bool val);
	void Add(short val);
	void Add(ushort val);
	void Add(uint val);
	void Add(int val);
	void Add(uint64 val);
	void Add(int64 val);
	void Add(float val);
	void Add(double val);
private:
	List<byte> mBuffer;
};

MEDUSA_END;
