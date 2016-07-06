// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Graphics/Buffer/IGraphicsBuffer.h"
#include "Core/Math/Math.h"
MEDUSA_BEGIN;


template<typename T, uint32 TSizeLimit = Math::UIntMaxValue>
class ListGraphicsBuffer :public IGraphicsBuffer
{
public:
	typedef T ItemType;
	typedef List<T, NoCompare> ListType;
	const static uint32 SizeLimit = TSizeLimit;
	using IGraphicsBuffer::LoadBufferData;
public:
	ListGraphicsBuffer(GraphicsBufferType bufferType, GraphicsBufferUsage usageType, GraphicsDataType dataType, uint componentCount, bool isNormlized = false, uint size = 256) :IGraphicsBuffer(bufferType, usageType, dataType, componentCount, isNormlized), mItems(size) {}
	virtual ~ListGraphicsBuffer(void) {}
public:
	virtual uint Count()const { return static_cast<uint>(mItems.Count()); }
	void ForceSetCount(uint count)
	{
		mItems.ForceSetCount(count);
		if (count > 0)
		{
			LimitDirtyRange(count - 1);
		}
		else
		{
			mDirtyRange.Reset();
		}
	}

	void ClearData()
	{
		mItems.Clear();
		mIsDataLoaded = false;
		DeleteObject();
		CleanDirty();
	}

	void AppendData(const ICollection<T>& items)
	{
		RETURN_IF_EMPTY(items);
		size_t count = mItems.Count();
		mItems.AppendRange(items);
		SetDirtyFrom(count);
	}

	void AppendData(const T& item)
	{
		size_t count = mItems.Count();
		mItems.Append(item);
		SetDirtyFrom(count);
	}

	void AppendOrUpdateData(size_t index, const T& item)
	{
		if (index == mItems.Count())
		{
			mItems.Append(item);
			SetDirtyFrom(index);
		}
		else if (index < mItems.Count())
		{
			mItems.Set(index, item);
			SetDirtyRange(index, index, mItems.Count() - 1);
		}

	}

	void UpdateData(size_t index, const T& item)
	{
		mItems.Set(index, item);
		SetDirtyRange(index, index, mItems.Count() - 1);
	}

	bool ReserveData(size_t newSize, size_t& outOriginalCount)
	{
		outOriginalCount = mItems.Count();
		if (outOriginalCount == newSize)
		{
			return false;
		}

		if (outOriginalCount < newSize)
		{
			mItems.ReserveSize(newSize);
			mItems.ForceSetCount(newSize);
			GenerateData(outOriginalCount);
			SetDirtyFrom(outOriginalCount);
		}
		else
		{
			mItems.ForceSetCount(newSize);
			LimitDirtyRange(newSize - 1);
			//no need to release items' extra size
		}

		return true;
	}
	void RemoveDataFrom(size_t index)
	{
		if (mItems.Count() > index)
		{
			mItems.RemoveFrom(index);
			if (!mItems.IsEmpty())
			{
				LimitDirtyRange(mItems.Count() - 1);
			}
		}
	}

	void RemoveDataRange(size_t index, size_t count)
	{
		if (mItems.Count() > index + count)
		{
			mItems.RemoveRange(index, count);
			if (!mItems.IsEmpty())
			{
				SetDirtyFrom(index);
			}
		}
	}

	void InsertDataCount(size_t index, const T& item, size_t count)
	{
		mItems.Insert(index, item, count);
		SetDirtyFrom(count);
	}

	void InsertDataRange(size_t index, const ICollection<T>& items)
	{
		mItems.InsertRange(index, items);
		SetDirtyFrom(index);
	}

	void SetDataRange(size_t index, const ICollection<T>& items)
	{
		mItems.ReserveSize(index + items.Count());
		mItems.SetRange(index, items);
		SetDirtyRange(index, index + items.Count(), mItems.Count() - 1);
	}

	void SetDataRange(size_t index, const T* items, size_t count)
	{
		mItems.ReserveSize(index + count);
		mItems.SetRange(index, items, count);
		SetDirtyRange(index, index + count, mItems.Count() - 1);
	}

	void SetDataRange(size_t index, const T& items, size_t count)
	{
		mItems.ReserveSize(index + count);
		mItems.SetRange(index, items, count);
		SetDirtyRange(index, index + count, mItems.Count() - 1);
	}

	void ReserveNewSize(size_t index, size_t originalCount, size_t newCount, const T& item)
	{
		if (originalCount < newCount)
		{
			InsertDataCount(index + originalCount, item, newCount - originalCount);
		}
		else if (originalCount > newCount)
		{
			RemoveDataRange(index + newCount, originalCount - newCount);
		}
	}

	void ReserveSize(size_t index, size_t newCount)
	{
		mItems.ReserveSize(index + newCount);
	}

	bool IsEmpty()const { return mItems.IsEmpty(); }
	const ListType& Data() const { return mItems; }
	ListType& MutableData() { return mItems; }
	virtual bool IsAvailableFor(size_t newCount)const { return TSizeLimit - mItems.Count() >= newCount; }
	void SetSingleDirtyIndex(size_t index)
	{
		if (!mItems.IsEmpty())
		{
			SetDirtyRange(index, index, mItems.Count() - 1);
		}
	}
	void SetDirtyFrom(size_t minIndex)
	{
		mDirtyRange.ExpandRangeFrom(minIndex, mItems.IsEmpty() ? 0 : (uint)mItems.Count() - 1);
	}


	virtual void GenerateData(size_t beginIndex) {}

protected:
	virtual void UpdateBufferData()
	{
		if (!mIsDataLoaded)
		{
			LoadBufferData(static_cast<uint32>(mItems.ByteSize()), mItems.MutableItems());
		}
		else
		{
			size_t count = mDirtyRange.Count();
			if (count == mItems.Count() || mItems.IsEmpty() || mItems.ByteSize() > mBufferSize)
			{
				LoadBufferData(static_cast<uint32>(mItems.ByteSize()), mItems.MutableItems());
			}
			else
			{
				size_t byteSize = (count)*sizeof(T);

				size_t byteOffset = mDirtyRange.Min*sizeof(T);
				const T* items = mItems.Items();
				items += mDirtyRange.Min;
				ModifyBufferSubData(byteOffset, byteSize, items);
			}

		}
	}


protected:
	ListType mItems;
};

MEDUSA_END;