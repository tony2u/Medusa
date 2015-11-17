// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once

#include "MedusaCorePreDeclares.h"
#include "Core/Memory/Memory.h"
#include "Core/Compile/TypeTraits.h"

MEDUSA_BEGIN;

#pragma region Compare
template<typename T>
struct STLMapLessPtr
{
	inline bool operator()(const T& str1, const T& str2)const
	{
		return str1<str2;
	}
};

template<typename T>
struct STLMapLessPtrForPointer
{
	inline bool operator()(const T* t1, const T* t2)const
	{
		return t1->Compare(*t2)<0;
	}
};


template<typename T>
struct DefaultCompare
{
	typedef typename Compile::TypeTraits<T>::ParameterType TParameterType;

	static int Compare(TParameterType t1, TParameterType t2)
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

	inline bool operator()(const T& t1, const T& t2)const
	{
		return t1<t2;
	}
};

template<typename T>
struct CustomCompare
{
	typedef typename Compile::TypeTraits<T>::ParameterType TParameterType;

	static int Compare(TParameterType t1, TParameterType t2)
	{
		return t1.Compare(t2);
	}

	inline bool operator()(const T& t1, const T& t2)const
	{
		return t1<t2;
	}
};


template<typename T>
struct DefaultCompareForPointer
{
	static int Compare(const T* t1, const T* t2)
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

	inline bool operator()(const T* t1, const T* t2)const
	{
		return *t1<*t2;
	}
};

template<typename T>
struct CustomCompareForPointer
{
	static int Compare(T t1, T t2)
	{
		return t1->Compare(*t2);
	}

	inline bool operator()(T t1, T t2)const
	{
		return *t1<*t2;
	}
};

template<typename T>
struct InverseCompare
{
	typedef typename Compile::TypeTraits<T>::ParameterType TParameterType;

	static int Compare(TParameterType t1, TParameterType t2)
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

	inline bool operator()(const T& t1, const T& t2)const
	{
		return t1>t2;
	}
};

template<typename T>
struct InverseCustomCompare
{
	typedef typename Compile::TypeTraits<T>::ParameterType TParameterType;

	static int Compare(TParameterType t1, TParameterType t2)
	{
		return t1.Compare(t2);
	}

	inline bool operator()(const T& t1, const T& t2)const
	{
		return t1>t2;
	}
};

template<typename T>
struct NoCompare
{
	typedef typename Compile::TypeTraits<T>::ParameterType TParameterType;

	static int Compare(TParameterType t1, TParameterType t2)
	{
		return 0;
	}
};

template<typename T>
struct EqualCompare
{
	typedef typename Compile::TypeTraits<T>::ParameterType TParameterType;

	static int Compare(TParameterType t1, TParameterType t2)
	{
		if (t1==t2)
		{
			return 0;
		}
		return -1;
	}

	inline bool operator()(const T& t1, const T& t2)const
	{
		return t1==t2;
	}
};

template<typename T>
struct ObjectEqualCompare
{
	typedef typename Compile::TypeTraits<T>::ParameterType TParameterType;

	static int Compare(TParameterType t1, TParameterType t2)
	{
		if (t1.Equals(t2))
		{
			return 0;
		}
		return -1;
	}

	inline bool operator()(const T& t1, const T& t2)const
	{
		return t1.Equals(t2);
	}
};

template<typename T>
struct PointerEqualCompare
{
	typedef typename Compile::TypeTraits<T>::ParameterType TParameterType;

	static int Compare(TParameterType t1, TParameterType t2)
	{
		if (t1->Equals(*t2))
		{
			return 0;
		}
		return -1;
	}

	inline bool operator()(const T& t1, const T& t2)const
	{
		return t1->Equals(*t2);
	}
};

#pragma endregion Compare

#pragma region Hash
template<typename T>
struct DefaultHashCoder
{
	typedef typename Compile::TypeTraits<T>::ParameterType TParameterType;

	static intp HashCode(TParameterType key)
	{
		return GetHashCodeHelper(key, std::integral_constant<bool,Compile::TypeTraits<T>::IsArithmetic || Compile::TypeTraits<T>::IsPointer || Compile::TypeTraits<T>::IsEnum>());
	}

	
//
private:
	static intp GetHashCodeHelper(TParameterType key, std::false_type isStdArith)
	{
		return key.HashCode();
	}

	static intp GetHashCodeHelper(TParameterType key, std::true_type isStdArith)
	{
		return (intp)key;
	}

};

template<typename T>
struct SafeEnumHashCoder
{
	static intp HashCode(T key)
	{
		return (intp)key;
	}
};

template<typename T>
struct NoHashCoder
{
	static intp HashCode(T key)
	{
		return 0;
	}
};

template<typename T>
struct DefaultPointerHashCoder
{
	static intp HashCode(T key)
	{
		return key->HashCode();
	}
};


#pragma endregion Hash

#pragma region New Delete
template<typename T>
struct DefaultDeleter
{
	typedef typename Compile::TypeTraits<T>::ParameterType TParameterType;

	static void Delete(TParameterType p)
	{
		Memory::Delete(p);
	}
};


template<typename T>
struct DefaultPointerDeleter
{
	typedef typename Compile::TypeTraits<T*>::ParameterType TParameterType;

	static void Delete(TParameterType p)
	{
		if (p!=nullptr)
		{
			delete p;
		}
	}
};

template<typename T>
struct DefaultPointerReleaser
{
	typedef typename Compile::TypeTraits<T*>::ParameterType TParameterType;

	static void Delete(TParameterType p)
	{
		if (p != nullptr)
		{
			p->Release();
		}
	}
};


template<typename T>
struct NoDeleter
{
	typedef typename Compile::TypeTraits<T>::ParameterType TParameterType;

	static void Delete(TParameterType p)
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