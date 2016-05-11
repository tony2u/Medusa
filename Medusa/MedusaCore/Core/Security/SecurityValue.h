// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once
#include "MedusaCorePreDeclares.h"
#include "Core/Compile/TypeTraits.h"
#include "Core/Math/Random/Random.h"

MEDUSA_BEGIN;
template<typename T,bool TIsResetKey>
class SecurityValueAutoUnlock;

template<typename T,bool TIsResetKey>
class SecurityValue
{
	friend class SecurityValueAutoUnlock<T,TIsResetKey>;
public:
	typedef typename Compile::TypeTraits<T>::ParameterType TParameterType;
public:
	SecurityValue()
	{
		ResetKey();
		Lock();
	}
	~SecurityValue()
	{
		Unlock();
	}
	SecurityValue(TParameterType val){ResetKey();mValue=val;Lock();}
	SecurityValue(const SecurityValue& field){ResetKey();mValue=field.Value();Lock();}
	SecurityValue& operator=(const SecurityValue& field){SetValue(field.Value());return *this;}
	SecurityValue& operator=(TParameterType val){SetValue(val.Get());return *this;}
public:
	inline operator T()
	{
		Unlock();
		T temp=mValue;
		Lock();
		return temp;
	}

	T Value()const
	{
		Unlock();
		T temp=mValue;
		Lock();
		return temp;
	}

	void SetValue(TParameterType val) {Unlock();mValue = val; Lock();}
private:
	void ResetKey()
	{
		Random rand;
		MemoryData key=MemoryData::Alloc(sizeof(T));
		rand.NextBytes(key);
		mEncoder.SetKey(key);
		mDecoder.SetKey(key);
	}
	void Lock()
	{
		if (TIsResetKey)
		{
			ResetKey();
		}
       const MemoryData input=MemoryData::FromStatic(&mValue,sizeof(T));
         MemoryData output=MemoryData::FromStatic(&mValue,sizeof(T));
		mEncoder.Code(input,output);
	}
	void Unlock()
    {
        const MemoryData input=MemoryData::FromStatic(&mValue,sizeof(T));
        MemoryData output=MemoryData::FromStatic(&mValue,sizeof(T));
        
        mDecoder.Code(input,output);
    }

	const T& ForceGetValue()const{return mValue;}
	T& ForceGetValue(){return mValue;}
	void ForceSetValue(TParameterType val) { mValue = val;}

private:
	T mValue;
	XOREncoder mEncoder;
	XORDecoder mDecoder;
};

template<typename T,bool TIsResetKey=false>
class SecurityValueAutoUnlock
{
public:
	typedef typename Compile::TypeTraits<T>::ParameterType TParameterType;

	SecurityValueAutoUnlock(SecurityValue<T,TIsResetKey>& val ):mValue(val)
	{
		mValue.Unlock();
	}
	~SecurityValueAutoUnlock()
	{
		mValue.Lock();
	}

	const T& Get()const{return mValue.ForceGetValue();}
	T& Get(){return mValue.ForceGetValue();}
	void SetValue(TParameterType val) { mValue.ForceSetValue(val);}
private:
	SecurityValue<T,TIsResetKey>& mValue;

};


MEDUSA_END;