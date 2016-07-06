// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once

#include "MedusaCorePreDeclares.h"
#include "Core/Pattern/RTTI/RTTIClass.h"
#include "Core/Pattern/RTTI/TRTTIClassRoot.h"
#include "Core/Pattern/RTTI/TRTTIClass.h"


/*
The reason why we need to implement my own's RTTI instead of dynamic_cast is that performance!
1. RTTI support multiple derived,but we don't need
2. RTTI throws exception when failing to cast ref,but we only need to case pointers

Performance data:
When cast derived pointer to base pointer, we 2 hava the same perf
When cast base pointer to derived pointer, here's the data:
Release:
My:				0.000003ms,10000000
dynamic_cast:	0.456289ms,10000000

Debug:
My:				1.331812ms,10000000
dynamic_cast:	0.696640ms,10000000

Test Code:
MyObject2* obj=new MyObject2();
RTTIObject* p=obj;
MyObject2* q=nullptr;
const int count=10000000;
int sum1=0;
int sum2=0;


StopWatch watch(count);

watch.Start();
FOR_EACH_SIZE(i,count)
{
q=(MyObject2*)p;
bool isKind= p->IsA<MyObject2>();
if (isKind)
{
++sum1;
}
else
{
++sum2;
}
}
watch.Stop();

watch.Start();
FOR_EACH_SIZE(i,count)
{
q= dynamic_cast<MyObject2*>(p);

bool isKind= q!=nullptr;
if (isKind)
{
++sum1;
}
else
{
++sum2;
}
}
watch.Stop();

system("PAUSE");

So we can see that in release mode, my RTTI version will get optimezed; I think it results from IsA don't need to call virtual functions and can be inlined.
*/


MEDUSA_BEGIN;

class RTTIObject
{
	
protected:
	virtual ~RTTIObject() = 0;
public:
	virtual const RTTIClass& Class()const = 0;
	template<typename T>
	bool IsA()const
	{
		return IsA(T::ClassStatic());
	}

	bool IsA(const RTTIClass& rttiClass)const
	{
		const RTTIClass* p = &Class();
		const RTTIClass* q = &rttiClass;
		do
		{
			RETURN_TRUE_IF_EQUAL(*p, *q);
			p = p->BaseClass();
		} while (p != nullptr);
		return false;
	}

	template<typename T> 
	bool IsExactly()const { return IsExactly(typename T::ClassStatic()); }
	bool IsExactly(const RTTIClass& rttiClass)const { return &Class() == &rttiClass; }
	template<typename T> 
	T* As() { return IsA<T>() ? (T*)this : nullptr; }
};

namespace RTTI
{
	template<typename T>
	inline T* SafeCast(const RTTIObject* obj)
	{
		RETURN_NULL_IF_NULL(obj);
		return obj->IsA<T>() ? (T*)obj : nullptr;
	}
}											

#define MEDUSA_RTTI_ROOT(className)	\
public:																				\
	virtual const RTTIClass& Class()const override{ return mRTTIClass.This(); }					\
	virtual const StringRef& ClassName()const { return mRTTIClass.This().Name(); }			\
	static const RTTIClass& ClassStatic() { return mRTTIClass.This(); }					\
	static const StringRef& ClassNameStatic() { return mRTTIClass.This().Name(); }			\
private:																			\
	constexpr static TRTTIClassRoot<className> mRTTIClass{#className};


#define MEDUSA_RTTI(className,baseClassName)	\
public:																				\
	virtual const RTTIClass& Class()const override{ return mRTTIClass.This(); }					\
	virtual const StringRef& ClassName()const override{ return mRTTIClass.This().Name(); }			\
	static const RTTIClass& ClassStatic() { return mRTTIClass.This(); }					\
	static const StringRef& ClassNameStatic() { return mRTTIClass.This().Name(); }			\
private:																			\
	constexpr static TRTTIClass<className,baseClassName> mRTTIClass{#className};


MEDUSA_END;