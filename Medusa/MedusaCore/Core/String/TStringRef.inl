#pragma once

#include "MedusaCorePreDeclares.h"
#include "Core/String/TStringRef.h"
#include "Core/String/HeapString.h"


MEDUSA_BEGIN;

template<typename T>
THeapString<T> TStringRef<T>::operator+( const TStringRef<T>& inString ) const
{
	return THeapString<T>(mBuffer)+inString;
}


template<typename T>
THeapString<T> TStringRef<T>::operator+( T c ) const
{
	return THeapString<T>(mBuffer)+c;
}


MEDUSA_END;