// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once
#include "MedusaCorePreDeclares.h"
#include "Core/Memory/Memory.h"

MEDUSA_BEGIN;
template<typename T>
class MemoryData
{
private:
	MemoryData(const T* data, size_t size, int* refCount) :mData((T*)data), mSize(size), mRefCount(refCount)
	{
		ForceRetain();
	}

public:
	MemoryData() :mData(nullptr), mSize(0), mRefCount(nullptr) {}

	MemoryData(const MemoryData& data) :mData(data.mData), mSize(data.mSize), mRefCount(data.mRefCount)
	{
		ForceRetain();
	}

	MemoryData& operator=(const MemoryData& data)
	{
		if (this != &data)
		{
			ForceRelease();
			mData = (T*)data.mData;
			mSize = data.mSize;
			mRefCount = data.mRefCount;
			ForceRetain();
		}
		return *this;
	}

	MemoryData(MemoryData&& data) :mData(data.mData), mSize(data.mSize), mRefCount(data.mRefCount)
	{
		data.mData = nullptr;
		data.mSize = 0;
		data.mRefCount = nullptr;
	}
	MemoryData& operator=(MemoryData&& data)
	{
		if (this != &data)
		{
			ForceRelease();
			mData = data.mData;
			mSize = data.mSize;
			mRefCount = data.mRefCount;

			data.mData = nullptr;
			data.mSize = 0;
			data.mRefCount = nullptr;
		}

		return *this;
	}

	bool operator==(const MemoryData& data)const
	{
		return mData == data.mData&&mSize == data.mSize&&mRefCount == data.mRefCount;
	}

	bool operator!=(const MemoryData& data)const
	{
		return mData != data.mData || mSize != data.mSize || mRefCount != data.mRefCount;
	}

	~MemoryData()
	{
		ForceRelease();
	}
public:
	const T* Data()const { return mData; }
	T* MutableData() { return mData; }
	size_t Size() const { return mSize; }
	size_t ByteSize() const { return mSize*sizeof(T); }

	int RefCount()const { return mRefCount != nullptr ? *mRefCount : 0; }


	bool IsNull()const { return mData == nullptr || mSize == 0; }
	bool IsEmpty()const { return mData == nullptr || mSize == 0; }

	bool IsValid()const { return !IsNull(); }
	bool IsDataEqual(const MemoryData& data)const { return mData == data.mData; }

	bool IsContentEqual(const MemoryData& data)const { return mSize == data.mSize&&Memory::Compare(mData, data.mData, mSize) == 0; }

	size_t LengthAsString()const
	{
		return IsNull() ? 0 : (mData[mSize - 1] == 0 ? mSize - 1 : mSize);
	}

	const T& operator[](size_t index)const { return mData[index]; }
	T& operator[](size_t index) { return mData[index]; }



	void ClearZero()
	{
		Memory::SetZero(mData, mSize);
	}

	MemoryData Clone()const
	{
		T* outData = nullptr;
		if (mData != nullptr)
		{
			outData = new T[mSize];
			Memory::SafeCopy(outData, mSize, mData, mSize);
		}
		return MemoryData(outData, mSize, new int(0));
	}

	MemoryData Sub(size_t offset, size_t count)const
	{
		MEDUSA_ASSERT(offset + count <= mSize, "");
		return MemoryData(mData + offset, count, mRefCount);
	}

	MemoryData Sub(size_t offset)const
	{
		MEDUSA_ASSERT(offset <= mSize, "");
		return MemoryData(mData + offset, mSize - offset, mRefCount);
	}


	template<typename T1>
	MemoryData<T1> Cast()const
	{
		return MemoryData<T1>::Share((T1*)mData, mSize*sizeof(T) / sizeof(T1), mRefCount);
	}

	static MemoryData CopyFrom(const T* buffer, size_t size)
	{
		T* result = new T[size];
		Memory::SafeCopy(result, size, buffer, size);
		return MemoryData(result, size, new int(0));
	}

public:
	static MemoryData FromStatic(const T* data, size_t size)
	{
		return MemoryData(data, size, nullptr);
	}

	template<size_t size>
	static MemoryData FromStatic(const T(&data)[size])
	{
		return MemoryData((T*)data, size, nullptr);
	}

	static MemoryData Take(const T* data, size_t size)
	{
		return MemoryData(data, size, new int(1));
	}

	template<size_t size>
	static MemoryData Take(const T(&data)[size])
	{
		return MemoryData((T*)data, size, new int(0));
	}

	static MemoryData Alloc(size_t size)
	{
		if (size == 0)
		{
			return MemoryData::Empty;
		}
		T* buffer = new T[size];
		return MemoryData(buffer, size, new int(0));
	}

	static MemoryData Share(const T* data, size_t size, int* refCount)
	{
		if (refCount != nullptr)
		{
			++*refCount;
		}
		return MemoryData(data, size, refCount);
	}
public:
	void Copy(const MemoryData& val)
	{
		Memory::SafeCopy(mData, mSize, val.Data(), val.Size());
	}

	void ForceSetData(T* val) { mData = val; }
	void ForceSetSize(size_t val) { mSize = val; }
	void ForceSetDataAndSize(T* val, size_t size) { mData = val; mSize = size; }
	void ForceOffsetDataAndSize(int offset) { mData += offset; mSize -= offset; }

	void ForceRetain()
	{
		if (mRefCount != nullptr)
		{
			++*mRefCount;
		}
	}

	void ForceRelease()
	{
		if (mRefCount != nullptr)
		{
			--*mRefCount;
			if (*mRefCount <= 0)
			{
				SAFE_DELETE_ARRAY(mData);
				mSize = 0;
				delete mRefCount;
				mRefCount = nullptr;
			}
		}
	}

	void ForceEnsureRefCount()
	{
		if (mRefCount == nullptr)
		{
			mRefCount = new int(1);
		}
	}

	void ForceMakeStatic()
	{
		SAFE_DELETE(mRefCount);
	}

	int* ForceGetRefCountPtr()const { return mRefCount; }
private:
	T* mData = nullptr;
	size_t mSize = 0;
	int* mRefCount = nullptr;
public:
	const static MemoryData Empty;
};

template<typename T>
const MemoryData<T> MemoryData<T>::Empty;

//[PRE_DECLARE_BEGIN]
typedef MemoryData<short> MemoryShortData;
typedef MemoryData<byte> MemoryByteData;
typedef MemoryData<char> MemoryCharData;
typedef MemoryData<wchar_t> MemoryWCharData;
typedef MemoryData<int> MemoryIntData;
typedef MemoryData<uint> MemoryUIntData;
typedef MemoryData<byte> Blob;
//[PRE_DECLARE_END]



MEDUSA_END;