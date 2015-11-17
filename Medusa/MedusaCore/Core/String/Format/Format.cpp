// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "Core/String/HeapString.h"
#include "Format.h"

MEDUSA_BEGIN;

namespace String
{
	HeapString FormatC(const char* format, ...)
	{
		HeapString str;
		va_list ap;
		va_start(ap, format);
		int length = StdString::GetFormatLength(format, ap);
		size_t size = length + 1;	//for 0
		if (size > 0)
		{
			str.ReserveSize(size);
			StdString::VSPrintf(str.MutableBuffer(), size, format, ap);
			str.ForceSetLength(length);
		}
		va_end(ap);
		return std::move(str);
	}

	WHeapString FormatC(const wchar_t* format, ...)
	{
		WHeapString str;
		va_list ap;
		va_start(ap, format);
		int length = StdString::GetFormatLength(format, ap);
		size_t size = length + 1;	//for 0
		if (size > 0)
		{
			str.ReserveSize(size);
			StdString::VSPrintf(str.MutableBuffer(), size, format, ap);
			str.ForceSetLength(length);
		}
		va_end(ap);
		return std::move(str);
	}

	HeapString Format(const StringRef& format)
	{
		return format;
	}

	WHeapString Format(const WStringRef& format)
	{
		return format;
	}

	HeapString& AppendFormat(HeapString& str, const StringRef& format)
	{
		str += format;
		return str;
	}

	WHeapString& AppendFormat(WHeapString& str, const WStringRef& format)
	{
		str += format;
		return str;
	}

	int Print(std::FILE* file, const StringRef& format)
	{
		return ::fprintf(file, format.c_str());
	}

	int Print(std::FILE* file, const WStringRef& format)
	{
		return ::fwprintf(file, format.c_str());
	}

	int Printf(std::FILE* file, const StringRef& format)
	{
		return ::fprintf(file, format.c_str());
	}

	int Printf(std::FILE* file, const WStringRef& format)
	{
		return ::fwprintf(file, format.c_str());
	}

}





MEDUSA_END;
