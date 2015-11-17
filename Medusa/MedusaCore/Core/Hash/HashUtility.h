// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once

#include "MedusaCorePreDeclares.h"
#include "Core/Compile/TypeTraits.h"

MEDUSA_BEGIN;



namespace HashUtility
{

	namespace Private
	{
		template<typename T>
		inline intp Hash_Imp(T val,std::true_type)
		{
			return (intp)val;
		}

		template<typename T>
		inline intp Hash_Imp(T val,std::false_type)
		{
			intp result=0;
			intp* p=(intp*)&val;
			FOR_EACH_SIZE(i,sizeof(T)/sizeof(intp))
			{
				result^=p[i];
			}
			return result;
		}
	}
	/*
	int32 HashString(const char* str);
	int32 HashString(const wchar_t* str);

	int32 HashString(const char* str,size_t length);
	int32 HashString(const wchar_t* str, size_t length);
	*/
	constexpr intp HashString(const char* str, intp seed = 0)
	{
		return  '\0' == *str ? seed : HashString(str + 1, seed ^ (*str + 0x9e3779b9 + (seed << 6) + (seed >> 2)));
	}
	constexpr intp HashString(const wchar_t* str, intp seed = 0)
	{
		return  '\0' == *str ? seed : HashString(str + 1, seed ^ (*str + 0x9e3779b9 + (seed << 6) + (seed >> 2)));
	}



	int32 HashIntArray(const int* buffer,size_t size,int32 initialValue=0);
	int64 HashIntArray64(const int* buffer,size_t size,int64 initialValue=0);
	int32 HashStringJenkins(const char* buffer,size_t length,int32 initialValue=0);
	int64 HashStringJenkins64(const char* buffer,size_t length,int64 initialValue=0);

	template<typename T,size_t size>
	inline intp Hash(T (&buffer)[size])
	{
		intp result=0;
		intp* p=(intp*)buffer;
		FOR_EACH_SIZE(i,size*sizeof(T)/sizeof(intp))
		{
			result^=p[i];
		}
		return result;
	}

	template<typename T>
	inline intp Hash(T val)
	{
		return HashUtility::Private::Hash_Imp(val,std::integral_constant<bool,Compile::TypeTraits<T>::IsPOD>());
	}

}

MEDUSA_END;