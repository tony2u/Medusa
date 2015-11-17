// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "FormatValue.h"
#include "FormatSpec.h"
#include "Formatter.h"

MEDUSA_BEGIN;

namespace String
{
	template <typename... TArgs>
	HeapString Format(const StringRef& format, const TArgs&... args)
	{
		const internal::FormatValue<char> vals[] = { args... };
		return internal::Format(format, vals);
	}

	template <typename... TArgs>
	WHeapString Format(const WStringRef& format, const TArgs&... args)
	{
		const internal::FormatValue<wchar_t> vals[] = { args... };
		return internal::Format(format, vals);
	}

	HeapString Format(const StringRef& format);
	WHeapString Format(const WStringRef& format);


	template <typename... TArgs>
	HeapString& AppendFormat(HeapString& str, const StringRef& format, const TArgs&... args)
	{
		const internal::FormatValue<char> vals[] = { args... };
		internal::Format(str, format, vals);
		return str;
	}

	template <typename... TArgs>
	WHeapString& AppendFormat(WHeapString& str, const WStringRef& format, const TArgs&... args)
	{
		const internal::FormatValue<wchar_t> vals[] = { args... };
		internal::Format(str, format, vals);
		return str;
	}

	HeapString& AppendFormat(HeapString& str, const StringRef& format);
	WHeapString& AppendFormat(WHeapString& str, const WStringRef& format);


	int Print(std::FILE* file, const StringRef& format);

	int Print(std::FILE* file, const WStringRef& format);
	template <typename... TArgs>
	int Print(std::FILE* file, const StringRef& format, const TArgs&... args)
	{
		//args count should > 0
		HeapString&& str = Format(format, args...);
		return ::fprintf(file, str.c_str());
	}

	template <typename... TArgs>
	int Print(std::FILE* file, const WStringRef& format, const TArgs&... args)
	{
		//args count should > 0
		WHeapString&& str = Format(format, args...);
		return ::fwprintf(file, str.c_str());
	}

	template <typename... TArgs>
	int Print(const StringRef& format, const TArgs&... args)
	{
		return Print(stdout, format, args...);
	}

	template <typename... TArgs>
	int Print(const WStringRef& format, const TArgs&... args)
	{
		return Print(stdout, format, args...);
	}

#pragma region C printf

	HeapString FormatC(const char* format, ...);
	WHeapString FormatC(const wchar_t* format,...);


	int Printf(std::FILE* file, const StringRef& format);
	int Printf(std::FILE* file, const WStringRef& format);
	template <typename... TArgs>
	int Printf(std::FILE* file, const StringRef& format, const TArgs&... args)
	{
		return ::fprintf(file, format.c_str(),args...);
	}

	template <typename... TArgs>
	int Printf(std::FILE* file, const WStringRef& format, const TArgs&... args)
	{
		return ::fwprintf(file, format.c_str(),args...);
	}

	template <typename... TArgs>
	int Printf(const StringRef& format, const TArgs&... args)
	{
		return printf(format.c_str(), args...);
	}

	template <typename... TArgs>
	int Printf(const WStringRef& format, const TArgs&... args)
	{
		return wprintf(format.c_str(), args...);
	}
#pragma endregion C printf

}





MEDUSA_END;
