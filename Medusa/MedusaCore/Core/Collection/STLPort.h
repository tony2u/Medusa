// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once

#include "MedusaCorePreDeclares.h"
#include "Core/Memory/Memory.h"
#include "Core/Compile/TypeTraits.h"

MEDUSA_BEGIN;

#pragma region Compare

struct STLMapLessPtr
{
	template<typename T1, typename T2>
	inline bool operator()(const T1& str1, const T2& str2)const
	{
		return str1<str2;
	}
};

struct STLMapLessPtrForPointer
{
	template<typename T1, typename T2>
	inline bool operator()(const T1* t1, const T2* t2)const
	{
		return t1->Compare(*t2)<0;
	}
};


struct DefaultCompare
{
	template<typename T1, typename T2>
	static int Compare(const T1& t1, const T2& t2)
	{
		if (t1<t2)
		{
			return -1;
		}
		else if (t2<t1)
		{
			return 1;
		}
		return 0;
	}

	template<typename T1, typename T2>
	inline bool operator()(const T1& t1, const T2& t2)const
	{
		return t1<t2;
	}
};


struct CustomCompare
{
	template<typename T1, typename T2>
	static int Compare(const T1& t1, const T2& t2)
	{
		return t1.Compare(t2);
	}

	template<typename T1, typename T2>
	inline bool operator()(const T1& t1, const T1& t2)const
	{
		return t1<t2;
	}
};


struct DefaultCompareForPointer
{
	template<typename T1, typename T2>
	static int Compare(const T1& t1, const T2& t2)
	{
		if (*t1<*t2)
		{
			return -1;
		}
		else if (*t2<*t1)
		{
			return 1;
		}
		return 0;
	}

	template<typename T1, typename T2>
	inline bool operator()(const T1& t1, const T2& t2)const
	{
		return *t1<*t2;
	}
};

struct CustomCompareForPointer
{
	template<typename T1, typename T2>
	static int Compare(const T1& t1, const T2& t2)
	{
		return t1->Compare(*t2);
	}

	template<typename T1, typename T2>
	inline bool operator()(const T1& t1, const T2& t2)const
	{
		return *t1<*t2;
	}
};

struct DefaultCompareForShare
{
	template<typename T1, typename T2>
	static int Compare(const Share<T1>& t1, const Share<T2>& t2)
	{
		if (*t1 < *t2)
		{
			return -1;
		}
		else if (*t2 < *t1)
		{
			return 1;
		}
		return 0;
	}

	template<typename T1, typename T2>
	inline bool operator()(const Share<T1>& t1, const Share<T2>& t2)const
	{
		return *t1 < *t2;
	}
};

struct CustomCompareForShare
{
	template<typename T1, typename T2>
	static int Compare(const Share<T1>& t1, const Share<T2>& t2)
	{
		return t1->Compare(*t2);
	}

	template<typename T1, typename T2>
	inline bool operator()(const Share<T1>& t1, const Share<T2>& t2)const
	{
		return *t1 < *t2;
	}
};

struct InverseCompare
{
	template<typename T1, typename T2>
	static int Compare(const T1& t1, const T2& t2)
	{
		if (t1<t2)
		{
			return 1;
		}
		else if (t2<t1)
		{
			return -1;
		}
		return 0;
	}

	template<typename T1, typename T2>
	inline bool operator()(const T1& t1, const T2& t2)const
	{
		return t1>t2;
	}
};

struct InverseCustomCompare
{
	template<typename T1, typename T2>
	static int Compare(const T1& t1, const T2& t2)
	{
		return t1.Compare(t2);
	}

	template<typename T1, typename T2>
	inline bool operator()(const T1& t1, const T2& t2)const
	{
		return t1>t2;
	}
};

struct NoCompare
{
	template<typename T1, typename T2>
	static int Compare(const T1& t1, const T2& t2)
	{
		return 0;
	}
};

struct EqualCompare
{
	template<typename T1,typename T2>
	static int Compare(const T1& t1, const T2& t2)
	{
		if (t1 == t2)
		{
			return 0;
		}
		return -1;
	}
	
	template<typename T1, typename T2>
	inline bool operator()(const T1& t1, const T2& t2)const
	{
		return t1 == t2;
	}

};

struct ObjectEqualCompare
{
	template<typename T1, typename T2>
	static int Compare(const T1& t1, const T2& t2)
	{
		if (t1.Equals(t2))
		{
			return 0;
		}
		return -1;
	}

	template<typename T1, typename T2>
	inline bool operator()(const T1& t1, const T2& t2)const
	{
		return t1.Equals(t2);
	}
};

struct PointerEqualCompare
{
	template<typename T1, typename T2>
	static int Compare(const T1& t1, const T2& t2)
	{
		if (t1->Equals(*t2))
		{
			return 0;
		}
		return -1;
	}

	template<typename T1, typename T2>
	inline bool operator()(const T1& t1, const T2& t2)const
	{
		return t1->Equals(*t2);
	}
};

#pragma endregion Compare

#pragma region Hash

struct DefaultHashCoder
{
	template<typename T>
	static intp HashCode(const T& key)
	{
		return GetHashCodeHelper(key, std::integral_constant<bool,Compile::TypeTraits<T>::IsArithmetic || Compile::TypeTraits<T>::IsPointer || Compile::TypeTraits<T>::IsEnum>());
	}
private:
	template<typename T>
	static intp GetHashCodeHelper(const T& key, std::false_type isStdArith)
	{
		return key.HashCode();
	}
	template<typename T>
	static intp GetHashCodeHelper(const T& key, std::true_type isStdArith)
	{
		return (intp)key;
	}

};

struct SafeEnumHashCoder
{
	template<typename T>
	static intp HashCode(T key)
	{
		return (intp)key;
	}
};

struct NoHashCoder
{
	template<typename T>
	static intp HashCode(const T& key)
	{
		return 0;
	}
};

struct DefaultPointerHashCoder
{
	template<typename T>
	static intp HashCode(const T& key)
	{
		return key->HashCode();
	}
};


#pragma endregion Hash

#pragma region New Delete

struct DefaultDeleter
{
	template<typename T>
	static void Delete(const T& p)
	{
		Memory::Delete(p);
	}
};


struct DefaultPointerDeleter
{
	template<typename T>
	static void Delete(const T& p)
	{
		if (p!=nullptr)
		{
			delete p;
		}
	}
};

struct DefaultPointerReleaser
{
	template<typename T>
	static void Delete(const T& p)
	{
		if (p != nullptr)
		{
			p->Release();
		}
	}
};


struct NoDeleter
{
	template<typename T>
	static void Delete(const T& p)
	{
	}
};

template<typename TObject>
struct DefaultNewer
{
	typedef typename Compile::TypeTraits<TObject>::UnderlyingType TObjectPointeeType;

	static TObject New()
	{
		return new TObjectPointeeType();
	}

};

template<typename TId,typename TObject>
struct DefaultNewerById
{
	typedef typename Compile::TypeTraits<TId>::ParameterType TIdParameterType;
	typedef typename Compile::TypeTraits<TObject>::UnderlyingType TObjectPointeeType;

	static TObject New(TIdParameterType id)
	{
		return new TObjectPointeeType(id);
	}

};

#pragma endregion New Delete

MEDUSA_END;