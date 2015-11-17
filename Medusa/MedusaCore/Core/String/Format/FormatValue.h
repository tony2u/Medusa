// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Memory/Memory.h"
#include "FormatSpec.h"
#include "Core/String/TStringRef.h"
#include "Core/String/StringParser.h"

MEDUSA_BEGIN;

#ifdef __GNUC__
//disable warning :format string is not a string literal (potentially insecure)
#  pragma GCC diagnostic ignored "-Wformat-security"
#endif

namespace String
{
	namespace internal
	{

		//for custom 
		template<typename TChar, typename T>
		inline typename std::enable_if<std::is_class<T>::value
			&&!std::is_same<T, TStringRef<TChar>>::value
			&&!std::is_same<T, std::basic_string<TChar, std::char_traits<TChar>, std::allocator<TChar> >>::value
			&&!std::is_base_of<BaseString<TChar>,T>::value,
			FormatResult>::type DoDefaultFormat(BaseString<TChar>& stream, const T& value, const AlignmentSpec<TChar>* alignSpec /*= nullptr*/)
		{
			auto&& str = value.template ToString<TChar>();
			AlignmentSpec<TChar>::WriteString(stream, str, alignSpec);
			return FormatResult::Success;
		}

		//for number
		template<typename TChar, typename T>
		inline typename std::enable_if<std::is_arithmetic<T>::value&&!std::is_same<T, TChar>::value&&!std::is_same<T, bool>::value, FormatResult>::type DoDefaultFormat(BaseString<TChar>& stream, const T& value, const AlignmentSpec<TChar>* alignSpec /*= nullptr*/)
		{
			auto&& str = StringParser::ToStringT<TChar>(value);
			AlignmentSpec<TChar>::WriteString(stream, str, alignSpec);
			return FormatResult::Success;
		}

		//for char
		template<typename TChar, typename T>
		inline typename std::enable_if<std::is_same<T, TChar>::value, FormatResult>::type DoDefaultFormat(BaseString<TChar>& stream, const T& value, const AlignmentSpec<TChar>* alignSpec /*= nullptr*/)
		{
			AlignmentSpec<TChar>::WriteChar(stream, value, alignSpec);
			return FormatResult::Success;
		}

		//for enum
		template<typename TChar, typename T>
		inline typename std::enable_if<std::is_enum<T>::value, FormatResult>::type DoDefaultFormat(BaseString<TChar>& stream, const T& value, const AlignmentSpec<TChar>* alignSpec /*= nullptr*/)
		{
			auto&& str = StringParser::ToStringT<TChar>((int)value);
			AlignmentSpec<TChar>::WriteString(stream, str, alignSpec);
			return FormatResult::Success;
		}

		//for pointer
		template<typename TChar, typename T>
		inline typename std::enable_if<std::is_pointer<T>::value&&!std::is_same<typename std::remove_const<T>::type, TChar*>::value, FormatResult>::type DoDefaultFormat(BaseString<TChar>& stream, const T& value, const AlignmentSpec<TChar>* alignSpec /*= nullptr*/)
		{
			auto&& str = StringParser::ToStringT<TChar>((intp)value);
			AlignmentSpec<TChar>::WriteString(stream, str, alignSpec);
			return FormatResult::Success;
		}

		//for bool
		template<typename TChar, typename T>
		inline typename std::enable_if<std::is_same<T, bool>::value, FormatResult>::type DoDefaultFormat(BaseString<TChar>& stream, const T& value, const AlignmentSpec<TChar>* alignSpec /*= nullptr*/)
		{
			TStringRef<TChar> str = value ? StdString::ConstValues<TChar>::TrueString : StdString::ConstValues<TChar>::FalseString;
			AlignmentSpec<TChar>::WriteString(stream, str, alignSpec);
			return FormatResult::Success;
		}


		//for string
		template<typename TChar, typename T>
		inline typename std::enable_if<std::is_same<T, TStringRef<TChar>>::value, FormatResult>::type DoDefaultFormat(BaseString<TChar>& stream, const T& value, const AlignmentSpec<TChar>* alignSpec /*= nullptr*/)
		{
			AlignmentSpec<TChar>::WriteString(stream, value, alignSpec);
			return FormatResult::Success;
		}
		template<typename TChar, typename T>
		inline typename std::enable_if<std::is_base_of<BaseString<TChar>,T>::value, FormatResult>::type DoDefaultFormat(BaseString<TChar>& stream, const T& value, const AlignmentSpec<TChar>* alignSpec /*= nullptr*/)
		{
			AlignmentSpec<TChar>::WriteString(stream, value, alignSpec);
			return FormatResult::Success;
		}

		//for std::string
		template<typename TChar, typename T>
		inline typename std::enable_if<std::is_same<T, std::basic_string<TChar, std::char_traits<TChar>, std::allocator<TChar> >>::value, FormatResult>::type DoDefaultFormat(BaseString<TChar>& stream, const T& value, const AlignmentSpec<TChar>* alignSpec /*= nullptr*/)
		{
			AlignmentSpec<TChar>::WriteString(stream, value, alignSpec);
			return FormatResult::Success;
		}

		//for char*
		template<typename TChar, typename T>
		inline typename std::enable_if<std::is_same<typename std::remove_const<T>::type, TChar*>::value, FormatResult>::type DoDefaultFormat(BaseString<TChar>& stream, const T& value, const AlignmentSpec<TChar>* alignSpec /*= nullptr*/)
		{
			AlignmentSpec<TChar>::WriteString(stream, value, alignSpec);
			return FormatResult::Success;
		}

		template<typename TChar>
		inline FormatResult DoDefaultFormatArray(BaseString<TChar>& stream, const TChar* value, const AlignmentSpec<TChar>* alignSpec /*= nullptr*/)
		{
			AlignmentSpec<TChar>::WriteString(stream, value, alignSpec);
			return FormatResult::Success;
		}

		template<typename TChar>
		inline FormatResult DoDefaultFormatArray(BaseString<TChar>& stream, const void* value, const AlignmentSpec<TChar>* alignSpec /*= nullptr*/)
		{
			auto&& str = StringParser::ToHexString<TChar>((uintp)value, 0, true, true, false);
			AlignmentSpec<TChar>::WriteString(stream, str, alignSpec);
			return FormatResult::Success;
		}

		//empty:
		//number: begin with number types
		//custom number:begin with custom placeholders
		//date
		//string
		//custom other


		//for custom class
		template<typename TChar, typename T>
		inline typename std::enable_if<std::is_class<T>::value
			&&!std::is_same<T, DateTime>::value
			&&!std::is_same<T, TStringRef<TChar>>::value
			&&!std::is_same<T, std::basic_string<TChar, std::char_traits<TChar>, std::allocator<TChar> >>::value
			&&!std::is_base_of<BaseString<TChar>,T>::value, FormatResult>::type DoFormat(BaseString<TChar>& stream, const T& value, const TChar* formatBegin, const TChar* formatEnd, const AlignmentSpec<TChar>* alignSpec /*= nullptr*/)
		{
			//transfer format string to object self
			auto&& str = value.ToString(formatBegin, formatEnd);
			AlignmentSpec<TChar>::WriteString(stream, str, alignSpec);
			return FormatResult::Success;
		}

		//for enum
		template<typename TChar, typename T>
		inline typename std::enable_if<std::is_enum<T>::value, FormatResult>::type DoFormat(BaseString<TChar>& stream, const T& value, const TChar* formatBegin, const TChar* formatEnd, const AlignmentSpec<TChar>* alignSpec /*= nullptr*/)
		{
			return DoFormat(stream, (int)value, formatBegin, formatEnd, alignSpec);
		}

		//for pointer
		template<typename TChar, typename T>
		inline typename std::enable_if<std::is_pointer<T>::value&&!std::is_same<typename std::remove_const<T>::type, TChar*>::value, FormatResult>::type DoFormat(BaseString<TChar>& stream, const T& value, const TChar* formatBegin, const TChar* formatEnd, const AlignmentSpec<TChar>* alignSpec /*= nullptr*/)
		{
			return DoFormat(stream, (intp)value, formatBegin, formatEnd, alignSpec);
		}

		//for number
		template<typename TChar, typename T>
		inline typename std::enable_if<std::is_arithmetic<T>::value, FormatResult>::type DoFormat(BaseString<TChar>& stream, const T& value, const TChar* formatBegin, const TChar* formatEnd, const AlignmentSpec<TChar>* alignSpec /*= nullptr*/)
		{
			//parse type
			switch (*formatBegin)
			{
			case (TChar)'B':
				//do not accept flags and precision
				RETURN_OBJECT_IF(formatEnd - formatBegin > 1, FormatResult::InvalidFormatString);
				{
					TStringRef<TChar> str = value ? StdString::ConstValues<TChar>::TrueStringUppercase : StdString::ConstValues<TChar>::FalseStringUppercase;
					AlignmentSpec<TChar>::WriteString(stream, str, alignSpec);
				}
				break;
			case (TChar)'b':
				//do not accept flags and precision
				RETURN_OBJECT_IF(formatEnd - formatBegin > 1, FormatResult::InvalidFormatString);
				{
					TStringRef<TChar> str = value ? StdString::ConstValues<TChar>::TrueString : StdString::ConstValues<TChar>::FalseString;
					AlignmentSpec<TChar>::WriteString(stream, str, alignSpec);
				}
				break;
			case (TChar)'C':
				//do not accept flags and precision
				RETURN_OBJECT_IF(formatEnd - formatBegin > 1, FormatResult::InvalidFormatString);
				{
					AlignmentSpec<TChar>::WriteChar(stream, (TChar)StdString::ToUpper((TChar)value), alignSpec);
				}
				break;
			case (TChar)'c':
				//do not accept flags and precision
				RETURN_OBJECT_IF(formatEnd - formatBegin > 1, FormatResult::InvalidFormatString);
				{
					AlignmentSpec<TChar>::WriteChar(stream, (TChar)StdString::ToUpper((TChar)value), alignSpec);
				}
				break;
			case (TChar)'D':
			case (TChar)'d':
			{
				NumberFormatSpec<TChar> spec;
				FormatResult result = NumberFormatSpec<TChar>::ParseNumberFormatSpec(formatBegin + 1, formatEnd, spec);
				RETURN_SELF_IF_NOT_EQUAL(result, FormatResult::Success);
#ifdef MEDUSA_SAFE_CHECK
				if (spec.HasFlag(NumberFormatSpecFlags::AlternateForm))
				{
					//d not has alternate form
					return FormatResult::InvalidNumberFormatFlags;
				}
#endif 
				DoWriteInt(stream, value, spec, alignSpec);
			}
			break;
			case (TChar)'F':
			case (TChar)'f':
			case (TChar)'E':
			case (TChar)'e':
			{
				NumberFormatSpec<TChar> spec;
				FormatResult result = NumberFormatSpec<TChar>::ParseNumberFormatSpec(formatBegin + 1, formatEnd, spec);
				RETURN_SELF_IF_NOT_EQUAL(result, FormatResult::Success);
				DoWriteFloat(stream, value, *formatBegin, spec, alignSpec);
			}
			break;
			case (TChar)'X':
			case (TChar)'x':
			{
				NumberFormatSpec<TChar> spec;
				FormatResult result = NumberFormatSpec<TChar>::ParseNumberFormatSpec(formatBegin + 1, formatEnd, spec);
				RETURN_SELF_IF_NOT_EQUAL(result, FormatResult::Success);
				DoWriteHex(stream, value, *formatBegin, spec, alignSpec);
			}
			break;
			case (TChar)'P':
			case (TChar)'p':
			{
				NumberFormatSpec<TChar> spec;
				FormatResult result = NumberFormatSpec<TChar>::ParseNumberFormatSpec(formatBegin + 1, formatEnd, spec);
				RETURN_SELF_IF_NOT_EQUAL(result, FormatResult::Success);
				DoWritePercent(stream, value * 100, (TChar)'f', spec, alignSpec);
			}
			break;
			default:
				//custom format
				return FormatResult::InvalidFormatString;
			}
			return FormatResult::Success;
		}

		//for string
		template<typename TChar, typename T>
		inline typename std::enable_if<std::is_same<T, TStringRef<TChar>>::value || std::is_base_of<BaseString<TChar>,T>::value, FormatResult>::type DoFormat(BaseString<TChar>& stream, const T& value, const TChar* formatBegin, const TChar* formatEnd, const AlignmentSpec<TChar>* alignSpec /*= nullptr*/)
		{
			switch (*formatBegin)
			{
			case (TChar)'s':
			case (TChar)'S':
				RETURN_OBJECT_IF(formatEnd - formatBegin > 1, FormatResult::InvalidFormatString);
				AlignmentSpec<TChar>::WriteString(stream, value, alignSpec);
				break;
			default:
				return FormatResult::InvalidFormatString;
			}

			return FormatResult::Success;
		}

		//for std::string
		template<typename TChar, typename T>
		inline typename std::enable_if<std::is_same<T, std::basic_string<TChar, std::char_traits<TChar>, std::allocator<TChar> >>::value, FormatResult>::type DoFormat(BaseString<TChar>& stream, const T& value, const TChar* formatBegin, const TChar* formatEnd, const AlignmentSpec<TChar>* alignSpec /*= nullptr*/)
		{
			switch (*formatBegin)
			{
			case (TChar)'s':
			case (TChar)'S':
				RETURN_OBJECT_IF(formatEnd - formatBegin > 1, FormatResult::InvalidFormatString);
				AlignmentSpec<TChar>::WriteString(stream, value, alignSpec);
				break;
			default:
				return FormatResult::InvalidFormatString;
			}

			return FormatResult::Success;
		}

		template<typename TChar>
		FormatResult DoFormat(BaseString<TChar>& stream, const TChar* value, const TChar* formatBegin, const TChar* formatEnd, const AlignmentSpec<TChar>* alignSpec /*= nullptr*/)
		{
			switch (*formatBegin)
			{
			case (TChar)'s':
			case (TChar)'S':
				RETURN_OBJECT_IF(formatEnd - formatBegin > 1, FormatResult::InvalidFormatString);
				AlignmentSpec<TChar>::WriteString(stream, value, alignSpec);
				break;
			default:
				return FormatResult::InvalidFormatString;
			}

			return FormatResult::Success;
		}

		//for date time
		template<typename TChar, typename T>
		inline typename std::enable_if<std::is_same<T, DateTime>::value, FormatResult>::type DoFormat(BaseString<TChar>& stream, const DateTime& value, const TChar* formatBegin, const TChar* formatEnd, const AlignmentSpec<TChar>* alignSpec /*= nullptr*/)
		{
			return FormatResult::NotSupport;
		}

		template<typename TChar, typename T>
		FormatResult DoWriteInt(BaseString<TChar>& stream, const T& value, const NumberFormatSpec<TChar>& spec, const AlignmentSpec<TChar>* alignSpec /*= nullptr*/)
		{
			bool sign;
			auto&& str = StringParser::ToStringTWithoutSign<TChar>(value, sign);
			size_t resultLength = spec.CalculateIntFormattedLength(str.Length(), sign);

			size_t zeroPrependCount = 0;
			if (spec.HasFlag(NumberFormatSpecFlags::PrependZero) && spec.Precision > resultLength)
			{
				zeroPrependCount = spec.Precision - resultLength;
				resultLength = spec.Precision;
			}

			TChar signChar = '\0';
			if (spec.HasFlag(NumberFormatSpecFlags::DefaultSign))
			{
				if (!sign)
				{
					//add '-' to negative value
					++resultLength;
					signChar = '-';
				}
			}
			else if (spec.HasFlag(NumberFormatSpecFlags::AlwaysShowSign))
			{
				//add '+' or '-'
				signChar = sign ? '+' : '-';
				++resultLength;
			}
			else if (spec.HasFlag(NumberFormatSpecFlags::PrependSpaceToPositiveSign))
			{
				//add '-' to negative value
				//add ' ' to positive value
				signChar = sign ? ' ' : '-';
				++resultLength;
			}

			size_t outLeftAlignWidth;
			size_t outRightAlignWidth;
			AlignmentSpec<TChar>::CalculateWidth(resultLength, outLeftAlignWidth, outRightAlignWidth, alignSpec);

			//add align left
			if (outLeftAlignWidth != 0)
			{
				stream.Append(alignSpec->Fill, outLeftAlignWidth);
			}

			//add sign
			if (signChar != '\0')
			{
				stream += signChar;
			}

			//add prepend zero
			if (zeroPrependCount != 0)
			{
				stream.Append('0', zeroPrependCount);
			}

			//add content
			stream += str;

			//add align right
			if (outRightAlignWidth != 0)
			{
				stream.Append(alignSpec->Fill, outRightAlignWidth);
			}

			return FormatResult::Success;
		}

		template<typename TChar, typename T>
		FormatResult DoWriteFloat(BaseString<TChar>& stream, const T& value, TChar type, const NumberFormatSpec<TChar>& spec, const AlignmentSpec<TChar>* alignSpec /*= nullptr*/)
		{
			//using snprintf to convert float
			TChar cFormatString[8];// longest format: %#0-.*f use * to input precision 
			TChar* end = spec.ConvertToC(cFormatString, type);
			*end = '\0';
			StringParser::ResultString<TChar, T> str;
			size_t resultLength = (size_t)StdString::SPrintf(str.MutableBuffer(), str.Size(), cFormatString, spec.Precision, value);
			str.ForceSetLength(resultLength);
			AlignmentSpec<TChar>::WriteString(stream, str, alignSpec);
			return FormatResult::Success;
		}

		template<typename TChar, typename T>
		FormatResult DoWriteHex(BaseString<TChar>& stream, const T& value, TChar type, const NumberFormatSpec<TChar>& spec, const AlignmentSpec<TChar>* alignSpec /*= nullptr*/)
		{
			//using snprintf 
			TChar cFormatString[8];// longest format: %#0-.*x use * to input precision 
			TChar* end = spec.ConvertToC(cFormatString, type);
			*end = '\0';
			TStackString<TChar, 18 + 1, false> str;	//max is 0xFFFFFFFFFFFFFFFF 16+2
			size_t resultLength = (size_t)StdString::SPrintf(str.MutableBuffer(), str.Size(), cFormatString, spec.Precision, value);
			str.ForceSetLength(resultLength);
			AlignmentSpec<TChar>::WriteString(stream, str, alignSpec);
			return FormatResult::Success;
		}

		template<typename TChar, typename T>
		inline typename std::enable_if<std::is_floating_point<T>::value, FormatResult>::type DoWritePercent(BaseString<TChar>& stream, const T& value, TChar type, const NumberFormatSpec<TChar>& spec, const AlignmentSpec<TChar>* alignSpec /*= nullptr*/)
		{
			//using snprintf 
			TChar cFormatString[10];// longest format: %#0-.*f%% use * to input precision 
			TChar* end = spec.ConvertToC(cFormatString, type);
			*end++ = '%';
			*end++ = '%';
			*end = '\0';

			StringParser::ResultString<TChar, T> str;
			size_t resultLength = (size_t)StdString::SPrintf(str.MutableBuffer(), str.Size(), cFormatString, spec.Precision, value);
			str.ForceSetLength(resultLength);

			AlignmentSpec<TChar>::WriteString(stream, str, alignSpec);

			return FormatResult::Success;
		}

		template<typename TChar, typename T>
		inline typename std::enable_if<!std::is_floating_point<T>::value, FormatResult>::type  DoWritePercent(BaseString<TChar>& stream, const T& value, TChar type, const NumberFormatSpec<TChar>& spec, const AlignmentSpec<TChar>* alignSpec /*= nullptr*/)
		{
			bool sign;
			auto&& str = StringParser::ToStringTWithoutSign<TChar>(value, sign);
			size_t resultLength = spec.CalculateIntFormattedLength(str.Length(), sign);

			size_t zeroPrependCount = 0;
			if (spec.HasFlag(NumberFormatSpecFlags::PrependZero) && spec.Precision > resultLength)
			{
				zeroPrependCount = spec.Precision - resultLength;
				resultLength = spec.Precision;
			}

			TChar signChar = '\0';
			if (spec.HasFlag(NumberFormatSpecFlags::DefaultSign))
			{
				if (!sign)
				{
					//add '-' to negative value
					++resultLength;
					signChar = '-';
				}
			}
			else if (spec.HasFlag(NumberFormatSpecFlags::AlwaysShowSign))
			{
				//add '+' or '-'
				signChar = sign ? '+' : '-';
				++resultLength;
			}
			else if (spec.HasFlag(NumberFormatSpecFlags::PrependSpaceToPositiveSign))
			{
				//add '-' to negative value
				//add ' ' to positive value
				signChar = sign ? ' ' : '-';
				++resultLength;
			}

			size_t outLeftAlignWidth;
			size_t outRightAlignWidth;
			AlignmentSpec<TChar>::CalculateWidth(resultLength, outLeftAlignWidth, outRightAlignWidth, alignSpec);

			//add align left
			if (outLeftAlignWidth != 0)
			{
				stream.Append(alignSpec->Fill, outLeftAlignWidth);
			}

			//add sign
			if (signChar != '\0')
			{
				stream += signChar;
			}

			//add prepend zero
			if (zeroPrependCount != 0)
			{
				stream.Append('0', zeroPrependCount);
			}

			//add content
			stream += str;
			stream += '%';

			//add align right
			if (outRightAlignWidth != 0)
			{
				stream.Append(alignSpec->Fill, outRightAlignWidth);
			}

			return FormatResult::Success;
		}

		template<typename TChar>
		struct FormatValue
		{
			using FormatFunc = FormatResult(*)(BaseString<TChar>&, const void*, const TChar*, const TChar*, const AlignmentSpec<TChar>*);

			template<typename T>
			FormatValue(const T& arg)
				:Value(&arg), Func(&FormatToWrapper<typename std::decay<T>::type>)
			{

			}
			FormatValue(const void* arg)
				: Value(arg), Func(&FormatArrayToWrapper<void>)
			{

			}

			template<typename T>
			FormatValue(const T* arg)
				: Value(arg), Func(&FormatArrayToWrapper<typename std::decay<T>::type>)
			{

			}

			FormatValue(const TChar* arg)
				: Value(arg), Func(&FormatArrayToWrapper<TChar>)
			{

			}

			template<size_t N>
			FormatValue(const TChar(&arg)[N])
				: Value(&arg), Func(&FormatArrayToWrapper<TChar>)
			{

			}

			FormatValue(const TStringRef<TChar>& arg)
				: Value(arg.c_str()), Func(&FormatArrayToWrapper<TChar>)
			{

			}



			FormatResult FormatTo(BaseString<TChar>& stream, const TChar* formatBegin, const TChar* formatEnd, const AlignmentSpec<TChar>* alignSpec = nullptr)const
			{
				return Func(stream, Value, formatBegin, formatEnd, alignSpec);
			}



			const void* Value;
			FormatFunc Func;
		private:
			template<typename T>
			static FormatResult FormatToWrapper(BaseString<TChar>& stream, const void* value, const TChar* formatBegin, const TChar* formatEnd, const AlignmentSpec<TChar>* alignSpec = nullptr)
			{
				if (formatBegin == nullptr || formatBegin == formatEnd)
				{
					//no format string
					return DoDefaultFormat(stream, *static_cast<const T*>(value), alignSpec);
				}
				else
				{
					return DoFormat(stream, *static_cast<const T*>(value), formatBegin, formatEnd, alignSpec);
				}
			}

			template<typename T>
			static FormatResult FormatArrayToWrapper(BaseString<TChar>& stream, const void* value, const TChar* formatBegin, const TChar* formatEnd, const AlignmentSpec<TChar>* alignSpec = nullptr)
			{
				if (formatBegin == nullptr || formatBegin == formatEnd)
				{
					//no format string
					return DoDefaultFormatArray(stream, static_cast<const T*>(value), alignSpec);
				}
				else
				{
					return DoFormat(stream, static_cast<const T*>(value), formatBegin, formatEnd, alignSpec);
				}
			}


		};
	}

}

#ifdef __GNUC__
# pragma GCC diagnostic pop
#endif

MEDUSA_END;
