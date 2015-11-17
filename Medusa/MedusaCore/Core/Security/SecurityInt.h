// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once
#include "MedusaCorePreDeclares.h"
#include "Core/Security/SecurityValue.h"

MEDUSA_BEGIN;

template<bool TIsResetKey>
class SecurityValue<int,TIsResetKey>	//[IGNORE_PRE_DECLARE]
{
public:
	SecurityValue()
	{
		ResetKey();
		Lock();
	}
	~SecurityValue()
	{
		
	}
	SecurityValue(int val){ResetKey();mValue=val;Lock();}
	SecurityValue(const SecurityValue& field){ResetKey();mValue=field.Value();Lock();}
	SecurityValue& operator=(const SecurityValue& field){SetValue(field.Value());return *this;}
	SecurityValue& operator=(int val){SetValue(val);return *this;}
public:
	inline operator int()const
	{
		return mValue^mKey;
	}

	int Value()const
	{
		return mValue^mKey;
	}

	void SetValue(int val) { mValue = val; Lock();}

	int operator -()const
	{
		return -(mValue^mKey);
	}

	int operator ~()const
	{
		return ~(mValue^mKey);
	}
	int operator !()const
	{
		return !(mValue^mKey);
	}

	SecurityValue& operator ++()
	{
		Unlock();
		++mValue;
		Lock();
		return *this;
	}

	int operator ++(int)
	{
		Unlock();
		int temp=mValue+1;
		Lock();
		return temp;
	}

	SecurityValue& operator --()
	{
		Unlock();
		--mValue;
		Lock();
		return *this;
	}

	int operator --(int)
	{
		Unlock();
		int temp=mValue+1;
		Lock();
		return temp;
	}

	SecurityValue& operator +=(int val)
	{
		Unlock();
		mValue+=val;
		Lock();
		return *this;
	}

	SecurityValue& operator -=(int val)
	{
		Unlock();
		mValue-=val;
		Lock();
		return *this;
	}

	SecurityValue& operator *=(int val)
	{
		Unlock();
		mValue*=val;
		Lock();
		return *this;
	}

	SecurityValue& operator /=(int val)
	{
		Unlock();
		mValue/=val;
		Lock();
		return *this;
	}
	SecurityValue& operator <<=(int val)
	{
		Unlock();
		mValue<<=val;
		Lock();
		return *this;
	}
	SecurityValue& operator >>=(int val)
	{
		Unlock();
		mValue>>=val;
		Lock();
		return *this;
	}
	SecurityValue& operator %=(int val)
	{
		Unlock();
		mValue%=val;
		Lock();
		return *this;
	}
	SecurityValue& operator ^=(int val)
	{
		Unlock();
		mValue^=val;
		Lock();
		return *this;
	}

	SecurityValue& operator &=(int val)
	{
		Unlock();
		mValue&=val;
		Lock();
		return *this;
	}
	SecurityValue& operator |=(int val)
	{
		Unlock();
		mValue|=val;
		Lock();
		return *this;
	}
private:
	void ResetKey()
	{
		mKey=Random::Global().Next();
	}
	void Lock()
	{
		if (TIsResetKey)
		{
			ResetKey();
		}
		mValue^=mKey;
	}
	void Unlock(){mValue^=mKey;}

	int ForceGetValue()const{return mValue;}
	void ForceSetValue(int val) { mValue = val;}

private:
	int mValue;
	int mKey;
};

//[PRE_DECLARE_BEGIN]
typedef SecurityValue<int,false> SecurityInt;
typedef SecurityValue<int,true> StrongSecurityInt;
//[PRE_DECLARE_END]

MEDUSA_END;