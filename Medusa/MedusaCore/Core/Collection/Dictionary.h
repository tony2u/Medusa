// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/Collection/IDictionary.h"
#include "Core/Collection/List.h"

MEDUSA_BEGIN;

template<typename TKey, typename TValue, typename TKeyHashCoder = DefaultHashCoder<TKey>, typename TValueHashCoder = DefaultHashCoder<TValue>, typename TKeyCompare = EqualCompare<TKey>, typename TValueCompare = EqualCompare<TValue> >
class Dictionary :public IDictionary < TKey, TValue, KeyValuePair<TKey, TValue, TKeyHashCoder, TValueHashCoder> >
{
public:
	typedef Dictionary<TKey, TValue, TKeyHashCoder, TValueHashCoder, TKeyCompare, TValueCompare> SelfType;

	typedef typename SelfType::KeyValuePairType KeyValuePairType;
	typedef typename SelfType::TReturnType TReturnType;
	typedef typename SelfType::TConstReturnType TConstReturnType;
	typedef typename SelfType::TPointerType TPointerType;
	typedef typename SelfType::TConstPointerType TConstPointerType;
	typedef typename SelfType::TParameterType TParameterType;
	typedef typename SelfType::TKeyParameterType TKeyParameterType;
	typedef typename SelfType::TValueParameterType TValueParameterType;
	typedef typename SelfType::TValueReferenceType TValueReferenceType;
	typedef typename SelfType::TValueConstReturnType TValueConstReturnType;
	typedef typename SelfType::TValuePointerType TValuePointerType;
	typedef typename SelfType::TKeyPointerType TKeyPointerType;
	typedef typename SelfType::TKeyConstPointerType TKeyConstPointerType;
	typedef typename SelfType::TValueConstPointerType TValueConstPointerType;

	const static SelfType Empty;
private:
	struct Entry
	{
		intp HashCode;    // Lower 31 bits of hash code, -1 if unused  
		intp Next;        // Index of next entry, -1 if last
		KeyValuePairType Pair;
		Entry() {}
		Entry(const Entry& other) :HashCode(other.HashCode), Next(other.Next), Pair(other.Pair) {}
		Entry& operator=(const Entry& other) { HashCode = other.HashCode; Next = other.Next; Pair = other.Pair; return *this; }
	};
public:
	Dictionary(size_t capacity = 0)
	{
		mEntries = nullptr;
		mBuckets = nullptr;
		mSize = 0;
		mAddedCount = 0;
		mFreeList = -1;
		mFreeCount = 0;
		this->mCount = 0;

		Resize(capacity);
	}

	Dictionary(const Dictionary& dict)
	{
		mEntries = nullptr;
		mBuckets = nullptr;
		mSize = dict.Count();
		Resize(dict.Count());

		FOR_EACH_COLLECTION(i, dict)
		{
			Add(i->Key, i->Value);
		}

	}

	Dictionary& operator=(const Dictionary& dict)
	{
		Clear();
		FOR_EACH_COLLECTION(i, dict)
		{
			Add(i->Key, i->Value);
		}
		return *this;
	}

	Dictionary(Dictionary&& other)
	{
		if (this != &other)
		{
			this->mCount = other.mCount;
			this->mBuckets = other.mBuckets;
			this->mEntries = other.mEntries;
			this->mSize = other.mSize;
			this->mFreeList = other.mFreeList;
			this->mFreeCount = other.mFreeCount;
			this->mAddedCount = other.mAddedCount;

			other.mCount = 0;
			other.mBuckets = nullptr;
			other.mEntries = nullptr;
			other.mSize = 0;
			other.mFreeList = 0;
			other.mFreeCount = 0;
			other.mAddedCount = 0;
		}
	}

	Dictionary& operator=(Dictionary&& other)
	{
		if (this != &other)
		{
			Clear();
			SAFE_FREE(this->mBuckets);
			SAFE_FREE(this->mEntries);

			this->mCount = other.mCount;
			this->mBuckets = other.mBuckets;
			this->mEntries = other.mEntries;
			this->mSize = other.mSize;
			this->mFreeList = other.mFreeList;
			this->mFreeCount = other.mFreeCount;
			this->mAddedCount = other.mAddedCount;

			other.mCount = 0;
			other.mBuckets = nullptr;
			other.mEntries = nullptr;
			other.mSize = 0;
			other.mFreeList = 0;
			other.mFreeCount = 0;
			other.mAddedCount = 0;
		}
		return *this;
	}


	virtual ~Dictionary()
	{
		SAFE_FREE(mBuckets);

		//destroy all valid objects
		uint index = 0;
		while (index < mAddedCount)
		{
			if (mEntries[index].HashCode >= 0)
			{
				Memory::Destory(&(mEntries[index].Pair));
			}
			index++;
		}

		SAFE_FREE(mEntries);
	}

	void ForceReserve(size_t capacity)
	{
		if (capacity > 0)
		{
			Resize(capacity);
		}
		else
		{
			Clear();
		}
	}

	TConstPointerType First()const
	{
		uint index = 0;
		while (index < mAddedCount)
		{
			if (mEntries[index].HashCode >= 0)
			{
				return &(mEntries[index].Pair);
			}
			index++;
		}
		return nullptr;
	}

	TPointerType MutableFirst()
	{
		uint index = 0;
		while (index < mAddedCount)
		{
			if (mEntries[index].HashCode >= 0)
			{
				return &(mEntries[index].Pair);
			}
			index++;
		}
		return nullptr;
	}
#pragma region IEnumerable
public:
	class Enumerator :public IEnumerator < TReturnType, TPointerType >	//[IGNORE_PRE_DECLARE_FILE]
	{
	public:
		explicit Enumerator(Entry* entries, size_t count) :mEntries(entries), mIndex(0), mAddedCount(count), mCurrent(nullptr) {}
		virtual TReturnType Current() { return mCurrent->Pair; }
		virtual TPointerType CurrentPtr() { return &(mCurrent->Pair); }

		TReturnType operator*() { return mCurrent->Pair; }
		TPointerType operator->() { return &(mCurrent->Pair); }


		virtual bool MoveNext()
		{
			RETURN_FALSE_IF_NULL(mEntries);
			while (mIndex < mAddedCount)
			{
				if (mEntries[mIndex].HashCode >= 0)
				{
					mCurrent = &(mEntries[mIndex]);
					mIndex++;
					return true;
				}
				mIndex++;
			}
			return false;
		}
		virtual void Reset()
		{
			mCurrent = nullptr;
			mIndex = 0;
		}
	protected:
		Entry* mEntries;
		size_t mIndex;
		size_t mAddedCount;
		Entry* mCurrent;
	};

	class ConstEnumerator :public IEnumerator < TConstReturnType, TConstPointerType >	//[IGNORE_PRE_DECLARE_FILE]
	{
	public:
		explicit ConstEnumerator(const Entry* entries, size_t count) :mEntries(entries), mIndex(0), mAddedCount(count),mCurrent(nullptr) {}
		virtual TConstReturnType Current() { return mCurrent->Pair; }
		virtual TConstPointerType CurrentPtr() { return &(mCurrent->Pair); }

		TConstReturnType operator*() { return mCurrent->Pair; }
		TConstPointerType operator->() { return &(mCurrent->Pair); }


		virtual bool MoveNext()
		{
			RETURN_FALSE_IF_NULL(mEntries);
			while (mIndex < mAddedCount)
			{
				if (mEntries[mIndex].HashCode >= 0)
				{
					mCurrent = &(mEntries[mIndex]);
					mIndex++;
					return true;
				}
				mIndex++;
			}
			return false;
		}
		virtual void Reset()
		{
			mCurrent = nullptr;
			mIndex = 0;
		}
	protected:
		const Entry* mEntries;
		size_t mIndex;
		size_t mAddedCount;
		const Entry* mCurrent;
	};
public:
	ConstEnumerator GetEnumerator()const { return ConstEnumerator(mEntries, mAddedCount); }
	Enumerator GetEnumerator() { return Enumerator(mEntries, mAddedCount); }
protected:
	virtual IEnumerator<TConstReturnType, TConstPointerType>* GetEnumeratorVirtualHelper()const { return new ConstEnumerator(mEntries, mAddedCount); }
	virtual IEnumerator<TReturnType, TPointerType>* GetEnumeratorVirtualHelper() { return new Enumerator(mEntries, mAddedCount); }
public:
	class ConstInterator	//[IGNORE_PRE_DECLARE_FILE]
	{
	public:
		explicit ConstInterator(const Entry* entryies, size_t addedCount, size_t index) :mEntries(entryies), mAddedCount(addedCount), mIndex(index) {}
		TConstReturnType operator*()const { return mEntries[mIndex].Pair; }
		TConstPointerType operator->()const { return &(mEntries[mIndex].Pair); }
		bool operator==(const ConstInterator& other)const { return mIndex == other.mIndex; }
		bool operator!=(const ConstInterator& other)const { return mIndex != other.mIndex; }
		ConstInterator& operator++()
		{
			do
			{
				++mIndex;
			} while (mEntries[mIndex].HashCode < 0 && mIndex < mAddedCount);
			return *this;
		}
		ConstInterator operator++(int)const
		{
			size_t index = mIndex;
			do
			{
				++index;
			} while (mEntries[index].HashCode < 0 && index < mAddedCount);
			return ConstInterator(mEntries, mAddedCount, index);
		}
		ConstInterator& operator--()
		{
			do
			{
				--mIndex;
			} while (mEntries[mIndex].HashCode < 0 && mIndex>0);
			return *this;
		}
		ConstInterator operator--(int)const 
		{
			size_t index = mIndex;
			do
			{
				--index;
			} while (mEntries[index].HashCode < 0 && index>0);
			return ConstInterator(mEntries, mAddedCount, index);
		}
	protected:
		const Entry* mEntries;
		size_t mAddedCount;
		size_t mIndex;
	};

	class Interator	//[IGNORE_PRE_DECLARE_FILE]
	{
	public:
		explicit Interator(Entry* entryies, size_t addedCount, size_t index) :mEntries(entryies), mAddedCount(addedCount), mIndex(index) {}
		TReturnType operator*()const { return mEntries[mIndex].Pair; }
		TPointerType operator->()const { return &(mEntries[mIndex].Pair); }
		bool operator==(const Interator& other)const { return mIndex == other.mIndex; }
		bool operator!=(const Interator& other)const { return mIndex != other.mIndex; }
		Interator& operator++()
		{
			do
			{
				++mIndex;
			} while (mEntries[mIndex].HashCode < 0 && mIndex < mAddedCount);
			return *this;
		}
		Interator operator++(int)const
		{
			size_t index = mIndex;
			do
			{
				++index;
			} while (mEntries[index].HashCode < 0 && index < mAddedCount);
			return Interator(mEntries, mAddedCount, index);
		}
		Interator& operator--()
		{
			do
			{
				--mIndex;
			} while (mEntries[mIndex].HashCode < 0 && mIndex>0);
			return *this;
		}
		Interator operator--(int)const
		{
			size_t index = mIndex;
			do
			{
				--index;
			} while (mEntries[index].HashCode < 0 && index>0);
			return Interator(mEntries, mAddedCount, index);
		}
	protected:
		Entry* mEntries;
		size_t mAddedCount;
		size_t mIndex;
	};
	ConstInterator begin()const { return ConstInterator(this->mEntries,this->mAddedCount,FirstIndex()); }
	ConstInterator end()const { return ConstInterator(this->mEntries, this->mAddedCount, this->mAddedCount); }
	Interator begin() { return Interator(this->mEntries, this->mAddedCount, FirstIndex()); }
	Interator end() { return Interator(this->mEntries, this->mAddedCount, this->mAddedCount); }
	size_t FirstIndex()const
	{
		uint index = 0;
		while (index < mAddedCount)
		{
			if (mEntries[index].HashCode >= 0)
			{
				return index;
			}
			index++;
		}
		return mAddedCount;
	}
#pragma endregion IEnumerable

#pragma region ICollection
public:
	virtual bool IsLinear() const { return false; }
	virtual TConstPointerType Items() const { MEDUSA_ASSERT_NOT_IMPLEMENT(); return nullptr; }
	virtual TPointerType MutableItems() { MEDUSA_ASSERT_NOT_IMPLEMENT(); return nullptr; }

	virtual bool Contains(TParameterType val)const
	{
		return ContainsKey(val.Key);
	}
	virtual size_t CopyTo(KeyValuePairType* outArray, size_t arraySize)const
	{
		RETURN_ZERO_IF_NULL(mEntries);
		RETURN_ZERO_IF_ZERO(arraySize);
		intp index = 0;
		FOR_EACH_SIZE(i, mSize)
		{
			const Entry& entry = mEntries[i];
			if (entry.HashCode >= 0)
			{
				outArray[index++] = entry.Pair;
				--arraySize;
				BREAK_IF_ZERO(arraySize);
			}
		}
		return index;
	}


#pragma endregion ICollection

#pragma region IDictionary

public:
	//virtual KeyCollectionType& GetKeys()const=0;
	//virtual ValueCollectionType& GetValues()const=0;

	virtual void Add(TParameterType val)
	{
		Add(val.Key, val.Value);
	}

	virtual bool TryAdd(TParameterType val)
	{
		return TryAdd(val.Key, val.Value);
	}

	virtual bool Remove(TParameterType val)
	{
		return RemoveKey(val.Key);
	}
	virtual void Clear()
	{
		mFreeList = -1;
		mAddedCount = 0;
		mFreeCount = 0;
		this->mCount = 0;

		Memory::Set(mBuckets, (char)-1, mSize);
		//destroy all valid objects
		uint index = 0;
		while (index < mAddedCount)
		{
			if (mEntries[index].HashCode >= 0)
			{
				Memory::Destory(&(mEntries[index].Pair));
			}
			index++;
		}
	}

	virtual bool ContainsKey(TKeyParameterType key)const
	{
		return FindEntry(key) >= 0;
	}

	template<typename TKey2>
	bool ContainsOtherKey(TKey2 key, intp hashCode)const
	{
		return FindEntryByOtherKey(key, hashCode) >= 0;
	}


	virtual bool ContainsValue(TValueParameterType value)const
	{
		RETURN_FALSE_IF_NULL(mEntries);
		FOR_EACH_SIZE(i, mSize)
		{
			const Entry& entry = mEntries[i];
			if (TValueCompare::Compare(entry.Pair.Value, value) == 0)
			{
				return true;
			}
		}

		return false;
	}

	virtual TValueReferenceType GetValue(TKeyParameterType key)
	{
		intp i = FindEntry(key);
		MEDUSA_ASSERT(i >= 0, "cannot find entry");
		Entry& entry = mEntries[(size_t)i];

		return entry.Pair.Value;
	}
	virtual TValueConstReturnType GetValue(TKeyParameterType key)const
	{
		intp i = FindEntry(key);
		MEDUSA_ASSERT(i >= 0, "cannot find entry");
		const Entry& entry = mEntries[(size_t)i];

		return entry.Pair.Value;
	}

	virtual void SetValue(TKeyParameterType key, TValueParameterType value)
	{
		intp i = FindEntry(key);
		if (i >= 0)
		{
			mEntries[(size_t)i].Pair.Value = value;
		}
		else
		{
			Add(key, value);
		}
	}

	virtual TValuePointerType TryGetValue(TKeyParameterType key)
	{
		intp i = FindEntry(key);
		if (i >= 0)
		{
			return (TValuePointerType)&(mEntries[(size_t)i].Pair.Value);
		}
		return nullptr;
	}

	template<typename TKey2>
	TValuePointerType TryGetValueByOtherKey(TKey2 key, intp hashCode)
	{
		intp i = FindEntryByOtherKey(key, hashCode);
		if (i >= 0)
		{
			return (TValuePointerType)&(mEntries[(size_t)i].Pair.Value);
		}
		return nullptr;
	}

	virtual TValueConstPointerType TryGetValue(TKeyParameterType key)const
	{
		intp i = FindEntry(key);
		if (i >= 0)
		{
			return (TValueConstPointerType)&(mEntries[(size_t)i].Pair.Value);
		}
		return nullptr;
	}

	template<typename TKey2>
	TValueConstPointerType TryGetValueByOtherKey(TKey2 key, intp hashCode)const
	{
		intp i = FindEntryByOtherKey(key, hashCode);
		if (i >= 0)
		{
			return (TValueConstPointerType)&(mEntries[(size_t)i].Pair.Value);
		}
		return nullptr;
	}


	virtual TValue TryGetValueWithFailed(TKeyParameterType key, TValueParameterType failedReturn)const
	{
		intp i = FindEntry(key);
		if (i >= 0)
		{
			return mEntries[(size_t)i].Pair.Value;
		}
		return failedReturn;
	}

	template<typename TKey2>
	TValue TryGetValueWithFailedByOtherKey(TKey2 key, intp hashCode, TValueParameterType failedReturn)const
	{
		intp i = FindEntryByOtherKey(key, hashCode);
		if (i >= 0)
		{
			return mEntries[(size_t)i].Pair.Value;
		}
		return failedReturn;
	}

	virtual TKeyPointerType TryGetKey(TValueParameterType value)
	{
		RETURN_NULL_IF_NULL(mEntries);
		FOR_EACH_SIZE(i, mSize)
		{
			Entry& entry = mEntries[i];
			if (TValueCompare::Compare(entry.Pair.Value, value) == 0)
			{
				return (TKeyPointerType)&(entry.Pair.Key);
			}
		}

		return nullptr;
	}

	virtual TKeyConstPointerType TryGetKey(TValueParameterType value)const
	{
		RETURN_NULL_IF_NULL(mEntries);

		FOR_EACH_SIZE(i, mSize)
		{
			const Entry& entry = mEntries[i];
			if (TValueCompare::Compare(entry.Pair.Value, value) == 0)
			{
				return (TKeyConstPointerType)&(entry.Pair.Key);
			}
		}

		return nullptr;
	}

	virtual void Add(TKeyParameterType key, TValueParameterType value)
	{
		if (mBuckets == nullptr || mEntries == nullptr)
		{
			Grow();
		}

		intp hashCode = (TKeyHashCoder::HashCode(key)) & 0x7FFFFFFF;
		intp targetBucket = hashCode%mSize;
		for (intp i = mBuckets[(size_t)targetBucket]; i >= 0; i = mEntries[(size_t)i].Next)
		{
			if (mEntries[(size_t)i].HashCode == hashCode && (TKeyCompare::Compare(key, mEntries[(size_t)i].Pair.Key) == 0))
			{
				//
				MEDUSA_ASSERT_FAILED("duplicate add");
				return;
			}
		}

		intp index = 0;
		if (mFreeCount > 0)
		{
			//add in free list
			index = mFreeList;
			mFreeList = mEntries[(size_t)index].Next;
			--mFreeCount;
		}
		else
		{
			if (mAddedCount == mSize)
			{
				Grow();
				targetBucket = hashCode%mSize;
			}
			index = mAddedCount;
			++mAddedCount;
		}
		Entry& entry = mEntries[(size_t)index];
		entry.HashCode = hashCode;
		entry.Next = mBuckets[(size_t)targetBucket];
		Memory::Construct(&entry.Pair);
		entry.Pair.Key = key;
		entry.Pair.Value = value;
		mBuckets[(size_t)targetBucket] = index;
		++this->mCount;
	}

	TValueReferenceType NewAdd(TKeyParameterType key)
	{
		if (mBuckets == nullptr || mEntries == nullptr)
		{
			Grow();
		}

		intp hashCode = (TKeyHashCoder::HashCode(key)) & 0x7FFFFFFF;
		intp targetBucket = hashCode%mSize;
		intp index = 0;
		if (mFreeCount > 0)
		{
			//add in free list
			index = mFreeList;
			mFreeList = mEntries[(size_t)index].Next;
			--mFreeCount;
		}
		else
		{
			if (mAddedCount == mSize)
			{
				Grow();
				targetBucket = hashCode%mSize;
			}
			index = mAddedCount;
			++mAddedCount;
		}
		Entry& entry = mEntries[(size_t)index];
		entry.HashCode = hashCode;
		entry.Next = mBuckets[(size_t)targetBucket];
		Memory::Construct(&entry.Pair);

		entry.Pair.Key = key;
		mBuckets[(size_t)targetBucket] = index;
		++this->mCount;

		return entry.Pair.Value;
	}

	template<typename TKey2>
	TValueReferenceType NewAdd(TKey2 key, intp hashCode)
	{
		if (mBuckets == nullptr || mEntries == nullptr)
		{
			Grow();
		}

		hashCode &= 0x7FFFFFFF;
		intp targetBucket = hashCode%mSize;
		intp index = 0;
		if (mFreeCount > 0)
		{
			//add in free list
			index = mFreeList;
			mFreeList = mEntries[(size_t)index].Next;
			--mFreeCount;
		}
		else
		{
			if (mAddedCount == mSize)
			{
				Grow();
				targetBucket = hashCode%mSize;
			}
			index = mAddedCount;
			++mAddedCount;
		}
		Entry& entry = mEntries[(size_t)index];
		entry.HashCode = hashCode;
		entry.Next = mBuckets[(size_t)targetBucket];
		Memory::Construct(&entry.Pair);

		entry.Pair.Key = key;
		mBuckets[(size_t)targetBucket] = index;
		++this->mCount;
		
		return entry.Pair.Value;
	}

	virtual bool TryAdd(TKeyParameterType key, TValueParameterType value)
	{
		if (mBuckets == nullptr || mEntries == nullptr)
		{
			Grow();
		}
		intp hashCode = (TKeyHashCoder::HashCode(key)) & 0x7FFFFFFF;
		intp targetBucket = hashCode%mSize;
		for (intp i = mBuckets[(size_t)targetBucket]; i >= 0; i = mEntries[(size_t)i].Next)
		{
			if (mEntries[(size_t)i].HashCode == hashCode && (TKeyCompare::Compare(key, mEntries[(size_t)i].Pair.Key) == 0))
			{
				return false;
			}
		}

		intp index = 0;
		if (mFreeCount > 0)
		{
			//add in free list
			index = mFreeList;
			mFreeList = mEntries[(size_t)index].Next;
			--mFreeCount;
		}
		else
		{
			if (mAddedCount == mSize)
			{
				Grow();
				targetBucket = hashCode%mSize;
			}
			index = mAddedCount;
			++mAddedCount;
		}
		Entry& entry = mEntries[(size_t)index];
		entry.HashCode = hashCode;
		entry.Next = mBuckets[(size_t)targetBucket];
		Memory::Construct(&entry.Pair);

		entry.Pair.Key = key;
		entry.Pair.Value = value;
		mBuckets[(size_t)targetBucket] = index;
		++this->mCount;
		return true;
	}


	virtual bool RemoveKey(TKeyParameterType key)
	{
		RETURN_FALSE_IF_NULL(mEntries);

		intp hashCode = (TKeyHashCoder::HashCode(key)) & 0x7FFFFFFF;
		intp bucket = hashCode%mSize;
		intp last = -1;
		for (intp i = mBuckets[(size_t)bucket]; i >= 0; last = i, i = mEntries[(size_t)i].Next)
		{
			if (mEntries[(size_t)i].HashCode == hashCode && (TKeyCompare::Compare(key, mEntries[(size_t)i].Pair.Key) == 0))
			{
				if (last < 0)
				{
					mBuckets[(size_t)bucket] = mEntries[(size_t)i].Next;
				}
				else
				{
					mEntries[(size_t)last].Next = mEntries[(size_t)i].Next;
				}

				Entry& entry = mEntries[(size_t)i];
				entry.HashCode = -1;
				entry.Next = mFreeList;
				Memory::Destory(&entry.Pair);

				mFreeList = i;
				mFreeCount++;
				--this->mCount;
				return true;
			}
		}

		return false;

	}

	virtual TValue RemoveKeyWithValueReturned(TKeyParameterType key, TValueParameterType failedReturn)
	{
		if (mBuckets == nullptr || mEntries == nullptr)
		{
			return failedReturn;
		}

		intp hashCode = (TKeyHashCoder::HashCode(key)) & 0x7FFFFFFF;
		intp bucket = hashCode%mSize;
		intp last = -1;
		for (intp i = mBuckets[(size_t)bucket]; i >= 0; last = i, i = mEntries[(size_t)i].Next)
		{
			if (mEntries[(size_t)i].HashCode == hashCode && (TKeyCompare::Compare(key, mEntries[(size_t)i].Pair.Key) == 0))
			{
				if (last < 0)
				{
					mBuckets[(size_t)bucket] = mEntries[(size_t)i].Next;
				}
				else
				{
					mEntries[(size_t)last].Next = mEntries[(size_t)i].Next;
				}

				Entry& entry = mEntries[(size_t)i];
				entry.HashCode = -1;
				entry.Next = mFreeList;
				Memory::Destory(&entry.Pair);

				mFreeList = i;
				mFreeCount++;
				--this->mCount;
				return entry.Pair.Value;
			}
		}

		return failedReturn;
	}



	template<typename TKey2>
	bool RemoveOtherKey(TKey2 key, intp otherHashCode)
	{
		RETURN_FALSE_IF_NULL(mEntries);

		intp hashCode = (otherHashCode)& 0x7FFFFFFF;
		intp bucket = hashCode%mSize;
		intp last = -1;
		for (intp i = mBuckets[(size_t)bucket]; i >= 0; last = i, i = mEntries[(size_t)i].Next)
		{
			if (mEntries[(size_t)i].HashCode == hashCode && (TKeyCompare::Compare(key, mEntries[(size_t)i].Pair.Key) == 0))
			{
				if (last < 0)
				{
					mBuckets[(size_t)bucket] = mEntries[(size_t)i].Next;
				}
				else
				{
					mEntries[(size_t)last].Next = mEntries[(size_t)i].Next;
				}

				Entry& entry = mEntries[(size_t)i];
				entry.HashCode = -1;
				entry.Next = mFreeList;
				Memory::Destory(&entry.Pair);

				mFreeList = i;
				mFreeCount++;
				--this->mCount;
				return true;
			}
		}

		return false;

	}

	template<typename TKey2>
	TValue RemoveOtherKeyWithValueReturned(TKey2 key, intp otherHashCode, TValueParameterType failedReturn)
	{
		if (mBuckets == nullptr || mEntries == nullptr)
		{
			return failedReturn;
		}
		intp hashCode = (otherHashCode)& 0x7FFFFFFF;
		intp bucket = hashCode%mSize;
		intp last = -1;
		for (intp i = mBuckets[(size_t)bucket]; i >= 0; last = i, i = mEntries[(size_t)i].Next)
		{
			if (mEntries[(size_t)i].HashCode == hashCode && (TKeyCompare::Compare(key, mEntries[(size_t)i].Pair.Key) == 0))
			{
				if (last < 0)
				{
					mBuckets[(size_t)bucket] = mEntries[(size_t)i].Next;
				}
				else
				{
					mEntries[(size_t)last].Next = mEntries[(size_t)i].Next;
				}

				Entry& entry = mEntries[(size_t)i];
				entry.HashCode = -1;
				entry.Next = mFreeList;
				Memory::Destory(&entry.Pair);

				mFreeList = i;
				mFreeCount++;
				--this->mCount;
				return entry.Pair.Value;
			}
		}

		return failedReturn;
	}

	virtual bool RemoveValue(TValueParameterType value)
	{
		RETURN_FALSE_IF_NULL(mEntries);

		FOR_EACH_SIZE(i, mSize)
		{
			const Entry& entry = mEntries[i];
			if (TValueCompare::Compare(entry.Pair.Value, value) == 0)
			{
				return RemoveKey(entry.Pair.Key);
			}
		}

		return false;
	}

#pragma endregion IDictionary

private:
	intp FindEntry(TKeyParameterType key)const
	{
		if (mEntries == nullptr || mBuckets == nullptr)
		{
			return -1;
		}

		intp hashCode = (TKeyHashCoder::HashCode(key)) & 0x7FFFFFFF;
		intp targetBucket = hashCode%mSize;
		for (intp i = mBuckets[targetBucket]; i >= 0; i = mEntries[(size_t)i].Next)
		{
			if (mEntries[(size_t)i].HashCode == hashCode && (TKeyCompare::Compare(key, mEntries[(size_t)i].Pair.Key) == 0))
			{
				return i;
			}
		}

		return -1;
	}

	template<typename TKey2>
	intp FindEntryByOtherKey(TKey2 key, intp hashCode)const
	{
		if (mEntries == nullptr || mBuckets == nullptr)
		{
			return -1;
		}

		hashCode = (hashCode)& 0x7FFFFFFF;
		intp targetBucket = hashCode%mSize;

		for (intp i = mBuckets[targetBucket]; i >= 0; i = mEntries[(size_t)i].Next)
		{
			if (mEntries[(size_t)i].HashCode == hashCode && (TKeyCompare::Compare(key, mEntries[(size_t)i].Pair.Key) == 0))
			{
				return i;
			}
		}

		return -1;
	}



	void Grow()
	{
		size_t newSize = Math::GetPrime(mAddedCount << 1);
		Resize(newSize);
	}

	void Resize(size_t newSize)
	{
		RETURN_IF(mSize >= newSize);
		Memory::Realloc(mBuckets, newSize);
		Memory::Set(mBuckets, (char)-1, newSize);
		Memory::Realloc(mEntries, newSize);


		for (size_t i = 0; i < mAddedCount; i++)
		{
			intp bucket = mEntries[(size_t)i].HashCode%newSize;
			mEntries[(size_t)i].Next = mBuckets[(size_t)bucket];
			mBuckets[(size_t)bucket] = i;
		}

		mSize = newSize;
	}

private:
	intp* mBuckets;
	Entry* mEntries;

	size_t mSize;
	intp mFreeList;
	intp mFreeCount;
	size_t mAddedCount;


};

template<typename TKey, typename TValue, typename TKeyHashCoder, typename TValueHashCoder, typename TKeyCompare, typename TValueCompare>
MEDUSA_WEAK_MULTIPLE_DEFINE const Dictionary<TKey, TValue, TKeyHashCoder, TValueHashCoder, TKeyCompare, TValueCompare> Dictionary<TKey, TValue, TKeyHashCoder, TValueHashCoder, TKeyCompare, TValueCompare>::Empty;

MEDUSA_END;