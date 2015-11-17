#pragma once

#include "MedusaCorePreDeclares.h"
#include "Core/String/BaseString.h"
#include "Core/String/Format/Formatter.h"


MEDUSA_BEGIN;

template<typename T>
template<typename... TArgs>
bool BaseString<T>::Format(const T* format, const TArgs&... args)
{
	Clear();
	const String::internal::FormatValue<T> vals[] = { args... };
	return String::internal::Formatter<T>(*this, vals).Run(format) == String::FormatResult::Success;
}

template<typename T>
template<typename... TArgs>
bool BaseString<T>::AppendFormat(const T* format, const TArgs&... args)
{
	const String::internal::FormatValue<T> vals[] = { args... };
	return String::internal::Formatter<T>(*this, vals).Run(format) == String::FormatResult::Success;
}

MEDUSA_END;