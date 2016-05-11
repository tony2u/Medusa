// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once
#include "MedusaCorePreDeclares.h"
#include "Core/Memory/Memory.h"

MEDUSA_BEGIN;
template<typename T>
class TMemoryData
{
private:
	TMemoryData(const T* data, size_t size, int* refCount) :mData((T*)data), mSize(size), mRefCount(refCount)
	{
		ForceRetain();
	}

public:
	TMemoryData() :mData(nullptr), mSize(0), mRefCount(nullptr) {}

	TMemoryData(const TMemoryData& data) :mData(data.mData), mSize(data.mSize), mRefCount(data.mRefCount)
	{
		ForceRetain();
	}

	TMemoryData& operator=(const TMemoryData& data)
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

	TMemoryData(TMemoryData&& data) :mData(data.mData), mSize(data.mSize), mRefCount(data.mRefCount)
	{
		data.mData = nullptr;
		data.mSize = 0;
		data.mRefCount = nullptr;
	}
	TMemoryData& operator=(TMemoryData&& data)
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

	bool operator==(const TMemoryData& data)const
	{
		return mData == data.mData&&mSize == data.mSize&&mRefCount == data.mRefCount;
	}

	bool operator!=(const TMemoryData& data)const
	{
		return mData != data.mData || mSize != data.mSize || mRefCount != data.mRefCount;
	}

	~TMemoryData()
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
	bool IsDataEqual(const TMemoryData& data)const { return mData == data.mData; }

	bool IsContentEqual(const TMemoryData& data)const { return mSize == data.mSize&&Memory::Compare(mData, data.mData, mSize) == 0; }

	size_t LengthAsString()const
	{
		return IsNull() ? 0 : (mData[mSize - 1] == 0 ? mSize - 1 : mSize);
	}

	const T& operator[](size_t index)const { return mData[index]; }
	T& operator[](size_t index) { return mData[index]; }



	void ClearZero()
	{
		Memory::ClearZero(mData, mSize);
	}

	TMemoryData Clone()const
	{
		T* outData = nullptr;
		if (mData != nullptr)
		{
			outData = Memory::Alloc<T>(mSize);
			Memory::SafeCopy(outData, mSize, mData, mSize);
		}
		return TMemoryData(outData, mSize, new int(0));
	}

	TMemoryData Sub(size_t offset, size_t count)const
	{
		MEDUSA_ASSERT(offset + count <= mSize, "");
		return TMemoryData(mData + offset, count, mRefCount);
	}

	TMemoryData Sub(size_t offset)const
	{
		MEDUSA_ASSERT(offset <= mSize, "");
		return TMemoryData(mData + offset, mSize - offset, mRefCount);
	}


	template<typename T1>
	TMemoryData<T1> Cast()const
	{
		return TMemoryData<T1>::Share((T1*)mData, mSize*sizeof(T) / sizeof(T1), mRefCount);
	}

	static TMemoryData CopyFrom(const T* buffer, size_t size)
	{
		T* result = Memory::Alloc<T>(size);
		Memory::SafeCopy(result, size, buffer, size);
		return TMemoryData(result, size, new int(0));
	}

public:
	static TMemoryData FromStatic(const T* data, size_t size)
	{
		return TMemoryData(data, size, nullptr);
	}

	template<size_t size>
	static TMemoryData FromStatic(const T(&data)[size])
	{
		return TMemoryData((T*)data, size, nullptr);
	}

	static TMemoryData Take(const T* data, size_t size)
	{
		return TMemoryData(data, size, new int(1));
	}

	template<size_t size>
	static TMemoryData Take(const T(&data)[size])
	{
		return TMemoryData((T*)data, size, new int(0));
	}

	static TMemoryData Alloc(size_t size)
	{
		if (size == 0)
		{
			return TMemoryData::Empty;
		}
		T* buffer = Memory::Alloc<T>(size);
		return TMemoryData(buffer, size, new int(0));
	}

	static TMemoryData AllocZero(size_t size)
	{
		if (size == 0)
		{
			return TMemoryData::Empty;
		}
		T* buffer = Memory::AllocZero<T>(size);
		return TMemoryData(buffer, size, new int(0));
	}

	static TMemoryData Share(const T* data, size_t size, int* refCount)
	{
		if (refCount != nullptr)
		{
			++*refCount;
		}
		return TMemoryData(data, size, refCount);
	}
public:
	void Copy(const TMemoryData& val)
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
				SAFE_FREE(mData);
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
	const static TMemoryData Empty;
};

template<typename T>
const TMemoryData<T> TMemoryData<T>::Empty;

//[PRE_DECLARE_BEGIN]
typedef TMemoryData<short> MemoryShortData;
typedef TMemoryData<byte> MemoryData;
typedef TMemoryData<char> MemoryCharData;
typedef TMemoryData<wchar_t> MemoryWCharData;
typedef TMemoryData<int> MemoryIntData;
typedef TMemoryData<uint> MemoryUIntData;
typedef TMemoryData<float> MemoryFloatData;

typedef TMemoryData<byte> Blob;
//[PRE_DECLARE_END]



MEDUSA_END;