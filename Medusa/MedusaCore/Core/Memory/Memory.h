// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once
#include "MedusaCorePreDeclares.h"
#include "Core/Compile/TypeTraits.h"
#include "Core/Assertion/CommonAssert.h"
#include "Core/Math/Math.h"
MEDUSA_BEGIN;

namespace Memory
{
	inline float Compare(const float* first, const float* second, size_t count)
	{
		FOR_EACH_SIZE(i, count)
		{
			float compare = Math::Compare(first[i], second[i]);
			if (compare != 0.f)
			{
				return compare;
			}
		}
		return 0.f;
	}

	inline double Compare(const double* first, const double* second, size_t count)
	{
		FOR_EACH_SIZE(i, count)
		{
			double compare = Math::Compare(first[i], second[i]);
			if (compare != 0.0)
			{
				return compare;
			}
		}
		return 0.0;
	}

	template <typename T, typename TCompare=DefaultCompare<T>>
	inline typename std::enable_if<Compile::TypeTraits<T>::IsPOD, int>::type Compare(const T* first, const T* second, size_t count)
	{
		return memcmp(first, second, count);
	}

	template <typename T, typename TCompare = DefaultCompare<T>>
	inline typename std::enable_if<!Compile::TypeTraits<T>::IsPOD, int>::type Compare(const T* first, const T* second, size_t count)
	{
		FOR_EACH_SIZE(i, count)
		{
			int compare = TCompare::Compare(first[i], second[i]);
			RETURN_SELF_IF_NOT_ZERO(compare);
		}
		return 0;
	}

	template <typename T, size_t N, typename TCompare=DefaultCompare<T>>
	inline int Compare(const T(&first)[N], const T(&second)[N])
	{
		return Compare<T, TCompare>(first, second, N);
	}

	namespace MemoryPrivate
	{
		template <typename T>
		inline void SafeCopy_Imp(T* dest, size_t destSize, const T* src, size_t count, std::true_type)
		{
#ifdef MEDUSA_WINDOWS
			memmove_s(dest, destSize*sizeof(T), src, count*sizeof(T));
#else
			memmove((void*)dest, (void*)src, count*sizeof(T));
#endif
		}

		template <typename T>
		inline void SafeCopy_Imp(T* dest, size_t destSize, const T* src, size_t count, std::false_type)
		{
			MEDUSA_ASSERT_IF(destSize >= count, "");

			if (dest <= src || (char *)dest >= ((char *)src + count))
			{
				/*
				* Non-Overlapping Buffers
				* copy from lower addresses to higher addresses
				*/
				while (count--)
				{
					*dest++ = *src++;
				}
			}
			else
			{
				/*
				* Overlapping Buffers
				* copy from higher addresses to lower addresses
				*/
				dest = dest + count - 1;
				src = src + count - 1;

				while (count--)
				{
					*dest-- = *src--;
				}
			}
		}

		template <typename T>
		inline void SafeCopyOne_Imp(T* dest, const T* src, std::true_type)
		{
			*dest = *src;
		}

		template <typename T>
		inline void SafeCopyOne_Imp(T* dest, const T* src, std::false_type)
		{
#ifdef MEDUSA_WINDOWS
			memmove_s(dest, sizeof(T), src, sizeof(T));
#else
			memmove((void*)dest, (void*)src, sizeof(T));
#endif
		}


	}

	inline const void* FindFirstChar(const void* src, size_t size, char val)
	{
		return memchr(src, val, size);
	}

	inline void* FindFirstChar(void* src, size_t size, char val)
	{
		return memchr(src, val, size);
	}

	inline const wchar_t* FindFirstWchar(const wchar_t* src, size_t size, wchar_t val)
	{
		return wmemchr(src, val, size);
	}

	inline wchar_t* FindFirstWchar(wchar_t* src, size_t size, wchar_t val)
	{
		return wmemchr(src, val, size);
	}

	inline int Compare(const void* p, const void* q, size_t num)
	{
		return memcmp(p, q, num);
	}

	inline int Compare(const wchar_t* p, const wchar_t* q, size_t num)
	{
		return wmemcmp(p, q, num);
	}

	template<typename T>
	inline T* Alloc(size_t count)
	{
		return (T*)malloc(count*sizeof(T));
	}

	template<typename T>
	inline void Realloc(T*& buffer, size_t count)
	{
		const uint size = sizeof(T);
		T* temp = buffer;
		buffer = (T*)realloc(buffer, count*size);
		if (buffer == nullptr&&temp != nullptr)
		{
			SAFE_FREE(temp);
		}
	}

	template <typename T>
	inline typename std::enable_if<Compile::TypeTraits<T>::IsPOD, void>::type Copy(T* dest, const T* src, size_t count)
	{
		memcpy(dest, src, count*sizeof(T));
	}

	template <typename T>
	inline typename std::enable_if<!Compile::TypeTraits<T>::IsPOD, void>::type Copy(T* dest, const T* src, size_t count)
	{
		FOR_EACH_SIZE(i, count)
		{
			*dest++ = *src++;
		}
	}


	template <typename T>
	inline void SafeCopyShallowOne(T* dest, const T* src)
	{
		MemoryPrivate::SafeCopyOne_Imp(dest, src, std::integral_constant<bool,Compile::TypeTraits<T>::IsArithmetic || Compile::TypeTraits<T>::IsPOD>());
	}

	template <typename T>
	inline void SafeCopy(T* dest, size_t destSize, const T* src, size_t count)
	{
		MemoryPrivate::SafeCopy_Imp(dest, destSize, src, count, std::integral_constant<bool,Compile::TypeTraits<T>::IsPOD>());
	}

	template <typename T>
	inline void SafeCopyShallow(T* dest, size_t destSize, const T* src, size_t count)
	{
		MemoryPrivate::SafeCopy_Imp(dest, destSize, src, count, std::true_type());
	}

	template <typename T>
	inline void SafeCopyDeep(T* dest, size_t destSize, const T* src, size_t count)
	{
		MemoryPrivate::SafeCopy_Imp(dest, destSize, src, count, std::false_type());
	}

	template <typename T, typename TValue>
	inline typename std::enable_if<sizeof(TValue) == 1, void>::type Set(T* src, TValue val, size_t count)
	{
		assert(sizeof(TValue) == 1);
		memset(src, *reinterpret_cast<int*>(&val), count*sizeof(T));
	}

	template <typename T, typename TValue>
	inline typename std::enable_if<sizeof(TValue) != 1, void>::type Set(T* src, TValue val, size_t count)
	{
#ifdef MEDUSA_IOS
		while (count-- > 0)
		{
			*src++ = val;
		}
#else
		const static char compareBlock[sizeof(TValue)] = { 0 };
		if (Compare((const char*)compareBlock, (const char*)&val, sizeof(TValue)) == 0)
		{
			memset((void*)src, 0, count*sizeof(T));
		}
		else
		{
			while (count-- > 0)
			{
				*src++ = val;
			}
		}
#endif
	}

	template <typename T>
	inline void ClearZero(T* src)
	{
		memset(src, 0, sizeof(T));
	}

	template <typename T>
	inline typename std::enable_if<Compile::TypeTraits<T>::IsPOD, void>::type SetZero(T* src, size_t count)
	{
		memset(src, 0, count*sizeof(T));
	}

	template <typename T>
	inline typename std::enable_if<!Compile::TypeTraits<T>::IsPOD, void>::type SetZero(T* src, size_t count)
	{
		while (count-- > 0)
		{
			*src++ = 0;
		}
	}


	template <typename T, size_t N>
	inline void SetZero(T(&src)[N])
	{
		SetZero(src, N);
	}

	template <typename T>
	inline bool EqualsAll(const T* first, size_t count,const T& val)
	{
		FOR_EACH_SIZE(i, count)
		{
			if (!Math::IsEqual(first[i], val))
			{
				return false;
			}
		}
		return true;
	}

	template <typename T>
	inline bool Equals(const T* first, const T* second, size_t count)
	{
		return memcmp(first, second, count) == 0;
	}

	inline bool EqualsFloat(const float* first, const float* second, size_t count)
	{
		FOR_EACH_SIZE(i, count)
		{
			if (!Math::IsEqual(first[i], second[i]))
			{
				return false;
			}
		}
		return true;
	}

	template <size_t N>
	inline bool EqualsFloat(const float(&first)[N], const float(&second)[N])
	{
		FOR_EACH_SIZE(i, N)
		{
			if (!Math::IsEqual(first[i], second[i]))
			{
				return false;
			}
		}
		return true;
	}

	template <typename T, size_t N>
	inline bool Equals(const T(&first)[N], const T(&second)[N])
	{
		return memcmp(first, second, N) == 0;
	}

	template <typename T, size_t N>
	inline bool EqualsAll(const T(&first)[N], const T& val)
	{
		return EqualsAll(first, N, val);
	}

	template<typename T,typename... TArgs>
	inline void Construct(T* p,TArgs&&... args)
	{
		::new (static_cast<void*>(p)) T(std::forward<TArgs>(args)...);
	}

	template<typename T, typename... TArgs>
	inline void ConstructRange(T* p, size_t size, TArgs&&... args)
	{
		FOR_EACH_SIZE(i, size)
		{
			::new (static_cast<void*>(p+i)) T(std::forward<TArgs>(args)...);
		}
	}

	template<typename T, typename TP>
	inline typename std::enable_if<Compile::TypeTraits<T>::IsPOD, void>::type CopyConstruct(T* p, TP val)
	{
		*p = val;
	}

	template<typename T, typename TP>
	inline typename std::enable_if<!Compile::TypeTraits<T>::IsPOD, void>::type CopyConstruct(T* p, TP val)
	{
		::new (static_cast<void*>(p)) T(val);
	}


	template<typename T, typename TP>
	inline typename std::enable_if<Compile::TypeTraits<T>::IsPOD, void>::type CopyConstructRange(T* p, TP val, size_t size)
	{
		Set(p, val,size);
	}

	template<typename T, typename TP>
	inline typename std::enable_if<!Compile::TypeTraits<T>::IsPOD, void>::type CopyConstructRange(T* p, TP val, size_t size)
	{
		FOR_EACH_SIZE(i, size)
		{
			::new (static_cast<void*>(p + i)) T(val);
		}
	}

	template<typename T>
	inline typename std::enable_if<Compile::TypeTraits<T>::IsPOD, void>::type CopyConstructIterator(T* dest, const T* src, size_t size)
	{
		MemoryPrivate::SafeCopy_Imp(dest, size, src, size, std::true_type());
	}

	template<typename T>
	inline typename std::enable_if<!Compile::TypeTraits<T>::IsPOD, void>::type CopyConstructIterator(T* dest, const T* src, size_t size)
	{
		FOR_EACH_SIZE(i, size)
		{
			::new (static_cast<void*>(dest + i)) T(*(src + i));
		}
	}

	template<typename T>
	inline typename std::enable_if<Compile::TypeTraits<T>::IsPointer, void>::type Delete(T p)
	{
		delete p;
	}

	template<typename T>
	inline typename std::enable_if<!Compile::TypeTraits<T>::IsPointer, void>::type Delete(T p)
	{
		//do nothing
	}


	template<typename T>
	inline typename std::enable_if<Compile::TypeTraits<T>::IsPOD, void>::type Destory(T* p)
	{
		//do nothing
	}

	template<typename T>
	inline typename std::enable_if<!Compile::TypeTraits<T>::IsPOD, void>::type Destory(T* p)
	{
		p->~T();
	}

	template<typename T>
	inline typename std::enable_if<Compile::TypeTraits<T>::IsPOD, void>::type DestoryRange(T* p, size_t size)
	{
		//do nothing
	}

	template<typename T>
	inline typename std::enable_if<!Compile::TypeTraits<T>::IsPOD, void>::type DestoryRange(T* p, size_t size)
	{
		FOR_EACH_SIZE(i, size)
		{
			(p + i)->~T();
		}
	}


	
	inline size_t FillCharArray(char* buffer, wchar_t wchar)
	{
		*buffer++ = (char)(int)wchar;
		*buffer++ = (char)((int)wchar >> 8);

		if (sizeof(wchar_t)==4)	//will be optimized
		{
			*buffer++ = (char)((int)wchar >> 16);
			*buffer = (char)((int)wchar >> 24);
		}
		
		return sizeof(wchar_t);
	}

	template < typename T >
	inline void LazyAssign(T*& dest, const T* src)
	{
		if (dest == nullptr)
		{
			if (src != nullptr)
			{
				dest = new T(*src);
			}
		}
		else
		{
			if (src == nullptr)
			{
				delete dest;
				dest = nullptr;
			}
			else
			{
				*dest = *src;
			}
		}
	}
}


MEDUSA_END;
