// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.

#pragma once
#include "Core/String/BaseString.h"
#include "Core/String/THeapString.h"
#include "Core/Collection/List.h"
#include "Core/String/StdString.h"

MEDUSA_BEGIN;

template<typename T, size_t TBufferSize, bool TIsInitNULL=false>
class TStackString:public BaseString<T>
{
public:
	using BaseString<T>::operator =;
public:
	TStackString():BaseString<T>(mStackBuffer,TBufferSize,TIsInitNULL)
	{

	}
	TStackString(T inChar):BaseString<T>(mStackBuffer,TBufferSize,TIsInitNULL)
	{
		this->Push(inChar);
	}

	TStackString(const TStringRef<T>& inBuffer):BaseString<T>(mStackBuffer,TBufferSize,TIsInitNULL)
	{
		this->Push(inBuffer);
	}

	//enable default memory copy
	TStackString(const TStackString& inString):BaseString<T>(mStackBuffer,TBufferSize)
	{
		this->Push(inString);
	}

	TStackString(const std::basic_string<T, std::char_traits<T>, std::allocator<T> >& str):BaseString<T>(mStackBuffer,TBufferSize,TIsInitNULL)
	{
		this->Push(str.c_str());
	}

	virtual ~TStackString()
	{
		this->mLength=0;
	}
    
    
	explicit TStackString(const T* inBuffer):BaseString<T>(mStackBuffer,TBufferSize,TIsInitNULL)
	{
		this->Push(inBuffer);
	}
    
    template<size_t size>
	explicit TStackString(const T (&str)[size]):BaseString<T>(mStackBuffer,TBufferSize,TIsInitNULL)
	{
		this->Push(str);
	}
    
public:
	THeapString<T> operator+(const BaseString<T>& str)const
	{
		THeapString<T> result(*this);
		result+=str;
		return result;
	}

	THeapString<T> operator+(const TStringRef<T>& str)const
	{
		THeapString<T> result(*this);
		result+=str;
		return result;
	}

	THeapString<T> operator+(T c)const
	{
		THeapString<T> result(*this);
		result+=c;
		return result;
	}

	friend THeapString<T> operator+(T inFirstChar,const TStackString& inSecondString)
	{
		THeapString<T> result(inFirstChar);
		result+=inSecondString;
		return result;
	}

	
public:
	virtual void Clear()
	{
		if (TIsInitNULL)
		{
			Memory::SetZero(mStackBuffer,TBufferSize);
		}
		else
		{
			*mStackBuffer=0;
		}

		this->mLength=0;
	}



	template<size_t returnBufferSize>
	TStackString<T,returnBufferSize> SubString(size_t index)const
	{
		return SubString(index,this->mLength-index);
	}

	template<size_t returnBufferSize>
	TStackString<T,returnBufferSize> SubString(size_t index,size_t length)const
	{
		MEDUSA_ASSERT_FALSE(this->IsNull(),"Null string");

		return TStackString<T,returnBufferSize>(this->mBuffer+index,length);
	}

	TStackString<T,TBufferSize> SubString(size_t index)const
	{
		return SubString(index,this->mLength-index);
	}

	TStackString<T,TBufferSize> SubString(size_t index,size_t length)const
	{
		MEDUSA_ASSERT_FALSE(this->IsNull(),"Null string");

		return TStackString<T,TBufferSize>(TStringRef<T>(this->mBuffer+index,length));
	}

	typedef T StackBufferType[TBufferSize];
	const StackBufferType& StackBuffer() const { return mStackBuffer; }
	StackBufferType& StackBuffer() { return mStackBuffer; }

	size_t ByteSize()const{return sizeof(mStackBuffer);}
protected:
	virtual bool ResizeHelper(size_t)
	{
		return false;
	}

private:
	T mStackBuffer[TBufferSize];
};


template< size_t TBufferSize, bool TIsInitNULL=false>
class StackString:public TStackString<char,TBufferSize,TIsInitNULL>
{
public:
	using TStackString<char,TBufferSize,TIsInitNULL>::operator =;
public:
	StackString():TStackString<char,TBufferSize,TIsInitNULL>(){}
	StackString(char inChar):TStackString<char,TBufferSize,TIsInitNULL>(inChar){}
	StackString(const TStringRef<char>& inBuffer):TStackString<char,TBufferSize,TIsInitNULL>(inBuffer){}
	StackString(const StackString& inString):TStackString<char,TBufferSize,TIsInitNULL>(inString){}
	virtual ~StackString(){}
    
    explicit StackString(const char* inBuffer):TStackString<char,TBufferSize,TIsInitNULL>(inBuffer){}
    template<size_t size>
	explicit StackString(const char (&str)[size]):TStackString<char,TBufferSize,TIsInitNULL>(str)
	{
		
	}
};

template< size_t TBufferSize, bool TIsInitNULL=false>
class WStackString:public TStackString<wchar_t,TBufferSize,TIsInitNULL>
{
public:
	using TStackString<wchar_t,TBufferSize,TIsInitNULL>::operator =;
public:
	WStackString():TStackString<wchar_t,TBufferSize,TIsInitNULL>(){}
	WStackString(wchar_t inChar):TStackString<wchar_t,TBufferSize,TIsInitNULL>(inChar){}
	WStackString(const TStringRef<wchar_t>& inBuffer):TStackString<wchar_t,TBufferSize,TIsInitNULL>(inBuffer){}
	WStackString(const WStackString& inString):TStackString<wchar_t,TBufferSize,TIsInitNULL>(inString){}
	virtual ~WStackString(){}
    
    explicit WStackString(const wchar_t* inBuffer):TStackString<wchar_t,TBufferSize,TIsInitNULL>(inBuffer){}
    template<size_t size>
	explicit WStackString(const wchar_t (&str)[size]):TStackString<wchar_t,TBufferSize,TIsInitNULL>(str)
	{
		
	}
};

MEDUSA_END;