// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/Collection/ISet.h"
#include "Core/Collection/List.h"

MEDUSA_BEGIN;

template<typename T, typename THashCoder = DefaultHashCoder<T>, typename TCompare = EqualCompare<T> >
class HashSet :public ISet<T, TCompare>
{
public:
	typedef HashSet<T, THashCoder, TCompare> SelfType;

	typedef typename SelfType::TReturnType TReturnType;
	typedef typename SelfType::TParameterType TParameterType;
	typedef typename SelfType::TReferenceType TReferenceType;
	typedef typename SelfType::TConstReturnType TConstReturnType;
	typedef typename SelfType::TPointerType TPointerType;
	typedef typename SelfType::TConstPointerType TConstPointerType;


private:
	struct Entry
	{
		intp HashCode;    // Lower 31 bits of hash code, -1 if unused  
		intp Next;        // Index of next entry, -1 if last
		T Value;
	};
public:
	HashSet(size_t capacity = 0)
	{
		Initialize(capacity);
	}

	HashSet(const HashSet& dict)
	{
		Initialize(dict.Count());

		FOR_EACH_COLLECTION(i, dict)
		{
			Add(*i);
		}

	}
	HashSet& operator=(const HashSet& dict)
	{
		Clear();
		FOR_EACH_COLLECTION(i, dict)
		{
			Add(*i);
		}
		return *this;
	}

	HashSet(HashSet&& other)
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

	HashSet& operator=(HashSet&& other)
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

	virtual ~HashSet()
	{
		SAFE_FREE(mEntries);
		SAFE_FREE(mBuckets);
		mAddedCount = 0;
		this->mCount = 0;
	}

#pragma region IEnumerable
public:
	class Enumerator :public IEnumerator<TReturnType, TPointerType>	//[IGNORE_PRE_DECLARE_FILE]
	{
		friend class HashSet<T, THashCoder, TCompare>;
		explicit Enumerator(Entry* entries, size_t count) :mEntries(entries), mIndex(0), mAddedCount(count), mCurrent(nullptr) {}

	public:
		virtual TReturnType Current() { return mCurrent->Value; }
		virtual TPointerType CurrentPtr() { return &(mCurrent->Value); }

		TReturnType operator*() { return mCurrent->Value; }
		TPointerType operator->() { return &(mCurrent->Value); }

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

			mIndex = mAddedCount + 1;
			mCurrent = nullptr;

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

	class ConstEnumerator :public IEnumerator<TConstReturnType, TConstPointerType>	//[IGNORE_PRE_DECLARE_FILE]
	{
		friend class HashSet<T, THashCoder, TCompare>;
		explicit ConstEnumerator(const Entry* entries, size_t count) :mEntries(entries), mIndex(0), mAddedCount(count), mCurrent(nullptr) {}

	public:
		virtual TConstReturnType Current() { return mCurrent->Value; }
		virtual TConstPointerType CurrentPtr() { return &(mCurrent->Value); }

		TConstReturnType operator*() { return mCurrent->Value; }
		TConstPointerType operator->() { return &(mCurrent->Value); }


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

			mIndex = mAddedCount + 1;
			mCurrent = nullptr;

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
		TConstReturnType operator*()const { return mEntries[mIndex].Value; }
		TConstPointerType operator->()const { return &(mEntries[mIndex].Value); }
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
		TReturnType operator*()const { return mEntries[mIndex].Value; }
		TPointerType operator->()const { return &(mEntries[mIndex].Value); }
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
	ConstInterator begin()const { return ConstInterator(this->mEntries, this->mAddedCount, FirstIndex()); }
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
		return FindEntry(val) >= 0;
	}

	virtual size_t CopyTo(T* outArray, size_t arraySize)const
	{
		RETURN_ZERO_IF_NULL(mEntries);
		intp index = 0;
		FOR_EACH_SIZE(i, mSize)
		{
			const Entry& entry = mEntries[i];
			if (entry.HashCode >= 0)
			{
				outArray[index++] = entry.Value;
			}
		}
		return index;
	}


#pragma endregion ICollection

#pragma region ISet

public:

	virtual void Clear()
	{
		mFreeList = -1;
		mAddedCount = 0;
		mFreeCount = 0;
		this->mCount = 0;

		Memory::Set(mBuckets, (char)-1, mSize);

	}

	template<typename T2>
	bool ContainsOther(T2 otherValue, intp hashCode)const
	{
		return FindEntryByOther(otherValue, hashCode) >= 0;
	}

	template<typename TKey2>
	TPointerType TryGetByOther(TKey2 key, intp hashCode)
	{
		intp i = FindEntryByOther(key, hashCode);
		if (i >= 0)
		{
			return (TPointerType)&(mEntries[(size_t)i].Value);
		}
		return nullptr;
	}

	template<typename TKey2>
	TConstPointerType TryGetByOther(TKey2 key, intp hashCode)const
	{
		intp i = FindEntryByOther(key, hashCode);
		if (i >= 0)
		{
			return (TConstPointerType)&(mEntries[(size_t)i].Value);
		}
		return nullptr;
	}


	template<typename TKey2>
	T TryGetWithFailedByOther(TKey2 key, intp hashCode, TParameterType failedReturn)
	{
		intp i = FindEntryByOther(key, hashCode);
		if (i >= 0)
		{
			return mEntries[(size_t)i].Value;
		}
		return failedReturn;
	}


	virtual void Add(TParameterType value)
	{
		if (mBuckets == nullptr || mEntries == nullptr)
		{
			Resize();
		}

		intp hashCode = (THashCoder::HashCode(value)) & 0x7FFFFFFF;
		intp targetBucket = hashCode%mSize;
		for (intp i = mBuckets[(size_t)targetBucket]; i >= 0; i = mEntries[(size_t)i].Next)
		{
			if (mEntries[(size_t)i].HashCode == hashCode && (TCompare::Compare(value, mEntries[(size_t)i].Value) == 0))
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
				Resize();
				targetBucket = hashCode%mSize;
			}
			index = mAddedCount;
			++mAddedCount;
		}
		Entry& entry = mEntries[(size_t)index];
		entry.HashCode = hashCode;
		entry.Next = mBuckets[(size_t)targetBucket];
		Memory::Construct(&entry.Value);
		entry.Value = value;
		mBuckets[(size_t)targetBucket] = index;
		++this->mCount;
	}

	template<typename TKey2>
	TReferenceType NewAdd(TKey2 key, intp hashCode)
	{
		if (mBuckets == nullptr || mEntries == nullptr)
		{
			Resize();
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
				Resize();
				targetBucket = hashCode%mSize;
			}
			index = mAddedCount;
			++mAddedCount;
		}
		Entry& entry = mEntries[(size_t)index];
		entry.HashCode = hashCode;
		entry.Next = mBuckets[(size_t)targetBucket];
		Memory::Construct(&entry.Value);
		mBuckets[(size_t)targetBucket] = index;
		++this->mCount;
		return entry.Value;
	}

	virtual bool TryAdd(TParameterType value)
	{
		if (mBuckets == nullptr || mEntries == nullptr)
		{
			Resize();
		}
		intp hashCode = (THashCoder::HashCode(value)) & 0x7FFFFFFF;
		intp targetBucket = hashCode%mSize;
		for (intp i = mBuckets[(size_t)targetBucket]; i >= 0; i = mEntries[(size_t)i].Next)
		{
			if (mEntries[(size_t)i].HashCode == hashCode && (TCompare::Compare(value, mEntries[(size_t)i].Value) == 0))
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
				Resize();
				targetBucket = hashCode%mSize;
			}
			index = mAddedCount;
			++mAddedCount;
		}
		Entry& entry = mEntries[(size_t)index];
		entry.HashCode = hashCode;
		entry.Next = mBuckets[(size_t)targetBucket];
		Memory::Construct(&entry.Value);
		entry.Value = value;
		mBuckets[(size_t)targetBucket] = index;
		++this->mCount;
		return true;
	}


	virtual bool Remove(TParameterType val)
	{
		RETURN_FALSE_IF_NULL(mEntries);

		intp hashCode = (THashCoder::HashCode(val)) & 0x7FFFFFFF;
		intp bucket = hashCode%mSize;
		intp last = -1;
		for (intp i = mBuckets[(size_t)bucket]; i >= 0; last = i, i = mEntries[(size_t)i].Next)
		{
			if (mEntries[(size_t)i].HashCode == hashCode && (TCompare::Compare(val, mEntries[(size_t)i].Value) == 0))
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
				Memory::Destory(&entry.Value);
				mFreeList = i;
				mFreeCount++;
				--this->mCount;
				return true;
			}
		}

		return false;

	}


	template<typename T2>
	bool RemoveOtherValue(T2 otherValue, intp otherHashCode)
	{
		RETURN_FALSE_IF_NULL(mEntries);

		intp hashCode = (otherHashCode)& 0x7FFFFFFF;
		intp bucket = hashCode%mSize;
		intp last = -1;
		for (intp i = mBuckets[(size_t)bucket]; i >= 0; last = i, i = mEntries[(size_t)i].Next)
		{
			if (mEntries[(size_t)i].HashCode == hashCode && (TCompare::Compare(otherValue, mEntries[(size_t)i].Value) == 0))
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
				Memory::Destory(&entry.Value);
				mFreeList = i;
				mFreeCount++;
				--this->mCount;
				return true;
			}
		}

		return false;

	}

	// Modifies the current object to contain all elements that are present in itself, the specified collection, or both.
	virtual void UnionWith(const ICollection<T>& other)
	{
		FOR_EACH_COLLECTION_VIRTUAL(i, other)
		{
			TryAdd(*i);
		}
	}

	//Modifies the current object to contain only elements that are present in that object and in the specified collection.
	virtual void IntersectWith(const ICollection<T>& other)
	{
		if (other.IsEmpty())
		{
			Clear();
			return;
		}

		FOR_EACH_SIZE(i, mSize)
		{
			const Entry& entry = mEntries[i];
			if (entry.HashCode >= 0)
			{
				if (other.Contains(entry.Value))
				{
					Remove(entry.Value);
				}
			}
		}
	}

	// Removes all elements in the specified collection from the current object.
	virtual void ExceptWith(const ICollection<T>& other)
	{
		RETURN_IF_EMPTY(other);
		if ((SelfType*)&other == this)
		{
			Clear();
			return;
		}

		FOR_EACH_COLLECTION_VIRTUAL(i, other)
		{
			Remove(*i);
		}

	}


	//Modifies the current object to contain only elements that are present either in that object or in the specified collection, but not both.
	virtual void SymmetricExceptWith(const ICollection<T>& other)
	{
		if (this->IsEmpty())
		{
			UnionWith(other);
		}
		else if ((SelfType*)&other == this)
		{
			Clear();
		}
		else
		{
			FOR_EACH_COLLECTION_VIRTUAL(i, other)
			{
				if (!Remove(*i))
				{
					TryAdd(*i);
				}
			}

		}
	}

	//Determines whether a object is a subset of the specified collection.
	virtual bool IsSubsetOf(const ICollection<T>& other)const
	{
		if (this->IsEmpty())
		{
			return true;
		}

		if (this->mCount > other.Count())
		{
			return false;
		}

		FOR_EACH_SIZE(i, mSize)
		{
			const Entry& entry = mEntries[i];
			if (entry.HashCode >= 0)
			{
				if (!other.Contains(entry.Value))
				{
					return false;
				}
			}
		}

		return true;


	}

	//Determines whether a object is a superset of the specified collection.
	virtual bool IsSupersetOf(const ICollection<T>& other)const
	{
		RETURN_TRUE_IF_EMPTY(other);

		if (this->mCount < other.Count())
		{
			return false;
		}

		FOR_EACH_COLLECTION_VIRTUAL(i, other)
		{
			if (!Contains(*i))
			{
				return false;
			}
		}

		return true;
	}

	//Determines whether a object is a proper superset of the specified collection.
	virtual bool IsProperSupersetOf(const ICollection<T>& other)const
	{
		RETURN_TRUE_IF_EMPTY(other);
		if (this->mCount < other.Count())
		{
			return false;
		}

		FOR_EACH_COLLECTION_VIRTUAL(i, other)
		{
			if (!Contains(*i))
			{
				return false;
			}
		}

		return this->mCount > other.Count();
	}

	//Determines whether a object is a proper superset of the specified collection.
	virtual bool IsProperSubsetOf(const ICollection<T>& other)const
	{
		if (this->IsEmpty())
		{
			return true;
		}

		if (this->mCount > other.Count())
		{
			return false;
		}

		FOR_EACH_SIZE(i, mSize)
		{
			const Entry& entry = mEntries[i];
			if (entry.HashCode >= 0)
			{
				if (!other.Contains(entry.Value))
				{
					return false;
				}
			}
		}

		return this->mCount < other.Count();
	}

	//true if the object and other share at least one common element; otherwise, false.
	virtual bool IsOverlaps(const ICollection<T>& other)const
	{
		if (this->IsEmpty())
		{
			return false;
		}

		FOR_EACH_COLLECTION_VIRTUAL(i, other)
		{
			if (Contains(*i))
			{
				return true;
			}
		}
		return false;
	}

	//Determines whether a object and the specified collection contain the same elements.
	virtual bool Equals(const ICollection<T>& other)const
	{
		if (this->mCount != other.Count())
		{
			return false;
		}

		FOR_EACH_COLLECTION_VIRTUAL(i, other)
		{
			if (!Contains(*i))
			{
				return false;
			}
		}

		return true;
	}



#pragma endregion ISet

private:
	intp FindEntry(TParameterType val)const
	{
		if (mEntries == nullptr || mBuckets == nullptr)
		{
			return -1;
		}

		intp hashCode = (THashCoder::HashCode(val)) & 0x7FFFFFFF;
		for (intp i = mBuckets[hashCode%mSize]; i >= 0; i = mEntries[(size_t)i].Next)
		{
			if (mEntries[(size_t)i].HashCode == hashCode && (TCompare::Compare(val, mEntries[(size_t)i].Value) == 0))
			{
				return i;
			}
		}

		return -1;
	}

	template<typename T2>
	intp FindEntryByOther(T2 otherValue, intp hashCode)const
	{
		if (mEntries == nullptr || mBuckets == nullptr)
		{
			return -1;
		}

		hashCode = (hashCode)& 0x7FFFFFFF;
		for (intp i = mBuckets[hashCode%mSize]; i >= 0; i = mEntries[(size_t)i].Next)
		{
			if (mEntries[(size_t)i].HashCode == hashCode&&TCompare::Compare(mEntries[(size_t)i].Value, otherValue) == 0)
			{
				return i;
			}
		}

		return -1;
	}

	void Initialize(size_t capacity)
	{
		if (capacity > 0)
		{
			mSize = Math::GetPrime(capacity);
			mBuckets = new intp[mSize];
			Memory::Set(mBuckets, (char)-1, mSize);
			mEntries = new Entry[mSize];
		}
		else
		{
			mSize = 0;
			mBuckets = nullptr;
			mEntries = nullptr;
		}

		mAddedCount = 0;
		mFreeList = -1;
		mFreeCount = 0;
		this->mCount = 0;
	}

	void Resize()
	{
		mSize = Math::GetPrime(mAddedCount << 1);
		Memory::Realloc(mBuckets, mSize);
		Memory::Set(mBuckets, (char)-1, mSize);

		Memory::Realloc(mEntries, mSize);

		for (size_t i = 0; i < mAddedCount; i++)
		{
			intp bucket = mEntries[(size_t)i].HashCode%mSize;
			mEntries[(size_t)i].Next = mBuckets[(size_t)bucket];
			mBuckets[(size_t)bucket] = i;
		}
	}

private:
	intp* mBuckets = nullptr;
	Entry* mEntries = nullptr;

	size_t mSize = 0;
	intp mFreeList = -1;
	size_t mFreeCount = 0;
	size_t mAddedCount = 0;

};

MEDUSA_END;