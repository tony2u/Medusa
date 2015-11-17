// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/String/StdString.h"

MEDUSA_BEGIN;

/*
printf format:

%[flags][width][.precision][length]specifier
http://www.cplusplus.com/reference/cstdio/printf/


Add support:
POSIX extension for positional arguments
http://pubs.opengroup.org/onlinepubs/009695399/functions/printf.html
e.g. printf("%2$s %1$s\n", "world!", "Hello");  // prints "Hello world!\n"
http://pubs.opengroup.org/onlinepubs/9699919799/

*/


/*
C# string.format
{ index[,alignment][:formatString]}
https://msdn.microsoft.com/en-us/library/txafckwd.aspx

*/

/*
Custom format: similar to C# string format but has some improvement
syntax:	{ index[,alignment][:formatString]}

alignment=	[fill][align]width
fill        =  a character
align       =  "-" | "+" | "=" (left,right,center,left is default)
width       =  integer(If the value of alignment is less than the length of the formatted string, alignment is ignored and the length of the formatted string is used as the field width. )

formatString	=

Standard Numeric Format Strings	=	type[flags][precision]
	type: is a single alphabetic character called the format specifier. Any numeric format string that contains more than one alphabetic character, including white space, is interpreted as a custom numeric format string.
		'B'|'b': bool values
		'C'|'c': char values
		'D'|'d':Integer digits with optional negative sign.
		"F" or "f":float double
		"E" or "e":Exponential (scientific)
		"P" or "p":Percent
		"X" or "x":Hexadecimal
	precision: is an optional integer called the precision specifier. The precision specifier ranges from 0 to 99 and affects the number of digits in the result.


	flags	=	'+' | '-' | ' ' | '#' | '0'
	'+'	indicates that a sign should be used for both positive as well as negative numbers.
	'-'	indicates that a sign should be used only for negative numbers (this is the default behavior).
	' '	indicates that a leading space should be used on positive numbers, and a minus sign on negative numbers.
	'0' When the 'precision' option is specified, prepends zeros for numeric types. (the default prepends spaces).
	'#'	for Alternate form:
			For 'f', 'F', 'e', 'E', types, the output always contains a decimal point.
			For 'x', 'X' types, the text '0x', '0X', respectively, is prepended to non-zero numbers.


Custom Numeric Format Strings.
TODO:
"0":Zero placeholder
"#":Digit placeholder
".":Decimal point
",":Group separator and number scaling
"%":Percentage placeholder
\:Escape character
'string'"string":Literal string delimiter
;:Section separator
Other:The character is copied to the result string unchanged.

Custom Date or other format string

*/


/*
Allow compile format spec to reuse
*/
namespace String
{
	enum class FormatResult
	{
		Success = 0,
		Error = -1,
		InvalidFormatString = -2,
		InvalidArgIndex = -3,
		InvalidType = -4,
		InvalidNumberFormatFlags = -5,
		NotSupport

	};

	namespace internal
	{
		

		enum class FormatAlignment :byte
		{
			None,
			Left,
			Right,
			Center
		};

		enum class NumberFormatSpecFlags :byte
		{
			None = 0,
			//2 bit enum
			DefaultSign = 1,
			AlwaysShowSign = 2,
			PrependSpaceToPositiveSign = 3,

			//flag
			AlternateForm = 4,
			PrependZero = 8,
		};




		template<typename TChar>
		class NumberFormatSpec
		{
		public:
			byte Flags = 0;
			byte Precision = 0;

			inline bool HasFlag(NumberFormatSpecFlags flag)const { return (Flags&(byte)flag) == (byte)flag; }
			size_t CalculateIntFormattedLength(size_t length, bool sign)const
			{
				size_t resultLength = length;
				if (HasFlag(NumberFormatSpecFlags::PrependZero) && Precision > resultLength)
				{
					resultLength = Precision;
				}

				if (HasFlag(NumberFormatSpecFlags::DefaultSign))
				{
					if (!sign)
					{
						//add '-' to negative value
						++resultLength;
					}
				}
				else if (HasFlag(NumberFormatSpecFlags::AlwaysShowSign))
				{
					//add '+' or '-'
					++resultLength;
				}
				else if (HasFlag(NumberFormatSpecFlags::PrependSpaceToPositiveSign))
				{
					//add '-' to negative value
					//add '+' to positive value
					++resultLength;
				}

				return resultLength;
			}

			size_t CalculateFloatFormattedLength(size_t length, bool sign)const
			{
				size_t resultLength = length;
				if (HasFlag(NumberFormatSpecFlags::PrependZero) && Precision > resultLength)
				{
					resultLength = Precision;
				}

				if (HasFlag(NumberFormatSpecFlags::DefaultSign))
				{
					if (!sign)
					{
						//add '-' to negative value
						++resultLength;
					}
				}
				else if (HasFlag(NumberFormatSpecFlags::AlwaysShowSign))
				{
					//add '+' or '-'
					++resultLength;
				}
				else if (HasFlag(NumberFormatSpecFlags::PrependSpaceToPositiveSign))
				{
					//add '-' to negative value
					//add '+' to positive value
					++resultLength;
				}

				return resultLength;
			}

			static FormatResult ParseNumberFormatSpec(const TChar* formatBegin, const TChar* formatEnd, NumberFormatSpec<TChar>& outSpec)
			{
				//[flags][precision]
				//flags: '+' | '-' | ' ' | '#' | '0'
				while (formatBegin != formatEnd)
				{
					switch (*formatBegin)
					{
					case (TChar)'+':
#ifdef MEDUSA_SAFE_CHECK
						if ((outSpec.Flags & 0x3) != 0)
						{
							return FormatResult::InvalidNumberFormatFlags;
						}
#endif
						outSpec.Flags |= (byte)NumberFormatSpecFlags::AlwaysShowSign;
						++formatBegin;
						break;
					case (TChar)'-':
#ifdef MEDUSA_SAFE_CHECK
						if ((outSpec.Flags & 0x3) != 0)
						{
							return FormatResult::InvalidNumberFormatFlags;
						}
#endif
						outSpec.Flags |= (byte)NumberFormatSpecFlags::DefaultSign;
						++formatBegin;
						break;
					case (TChar)' ':
#ifdef MEDUSA_SAFE_CHECK
						if ((outSpec.Flags & 0x3) != 0)
						{
							return FormatResult::InvalidNumberFormatFlags;
						}
#endif
						outSpec.Flags |= (byte)NumberFormatSpecFlags::PrependSpaceToPositiveSign;
						++formatBegin;
						break;
					case (TChar)'#':
#ifdef MEDUSA_SAFE_CHECK
						if (outSpec.HasFlag(NumberFormatSpecFlags::AlternateForm))
						{
							return FormatResult::InvalidNumberFormatFlags;
						}
#endif
						outSpec.Flags |= (byte)NumberFormatSpecFlags::AlternateForm;
						++formatBegin;
						break;
					case (TChar)'0':
#ifdef MEDUSA_SAFE_CHECK
						if (outSpec.HasFlag(NumberFormatSpecFlags::PrependZero))
						{
							return FormatResult::InvalidNumberFormatFlags;
						}
#endif

						outSpec.Flags |= (byte)NumberFormatSpecFlags::PrependZero;
						++formatBegin;
						break;
					default:
						//is number?
						if (StdString::IsDigit(*formatBegin))
						{
							TChar* outNext;
							outSpec.Precision =(byte)StdString::ParseUInt(formatBegin, &outNext);
							if (outSpec.Precision == 0 || outNext != formatEnd)	//has too many chars
							{
								return FormatResult::InvalidFormatString;
							}
							formatBegin = outNext;
						}
						else
						{
							return FormatResult::InvalidFormatString;
						}
						break;
					}

				}


				return FormatResult::Success;
			}

			TChar* ConvertToC(TChar* buffer, TChar type)const
			{
				*buffer++ = '%';

				if (HasFlag(NumberFormatSpecFlags::AlternateForm))
				{
					*buffer++ = '#';
				}
				if (HasFlag(NumberFormatSpecFlags::PrependZero))
				{
					*buffer++ = '0';
				}

				if (HasFlag(NumberFormatSpecFlags::DefaultSign))
				{
					*buffer++ = '-';
				}
				else if (HasFlag(NumberFormatSpecFlags::AlwaysShowSign))
				{
					*buffer++ = '+';
				}
				else if (HasFlag(NumberFormatSpecFlags::PrependSpaceToPositiveSign))
				{
					*buffer++ = ' ';
				}

				*buffer++ = '.';
				*buffer++ = '*';
				*buffer++ = type;

				return buffer;
			}
		};


		template<typename TChar>
		class AlignmentSpec
		{
		public:
			TChar Fill = ' ';
			FormatAlignment Aligment = FormatAlignment::None;
			ushort Width = 0;
		

			static bool ParseAlignment(const TChar* begin, const TChar* end, TChar** outNext, AlignmentSpec<TChar>& outSpec)
			{
				//no need to check begin at first because has been checked outside
				//parse fill
				switch (*begin)
				{
				case StdString::ConstValues<TChar>::OpenAngle:
					outSpec.Aligment = FormatAlignment::Left;
					break;
				case StdString::ConstValues<TChar>::CloseAngle:
					outSpec.Aligment = FormatAlignment::Right;
					break;
				case StdString::ConstValues<TChar>::Equal:
					outSpec.Aligment = FormatAlignment::Center;
					break;
				case StdString::ConstValues<TChar>::OpenBrace:
					RETURN_FALSE_IF_NOT_EQUAL(*++begin, StdString::ConstValues<TChar>::OpenAngle);	//should double it to use {
					outSpec.Fill = StdString::ConstValues<TChar>::OpenAngle;
					break;
				case StdString::ConstValues<TChar>::CloseBrace:
					RETURN_FALSE_IF_NOT_EQUAL(*++begin, StdString::ConstValues<TChar>::CloseAngle);	//should double it to use }
					outSpec.Fill = StdString::ConstValues<TChar>::CloseAngle;
					break;
				default:
					outSpec.Fill = *begin++;
					break;
				}

				//parse alignment
				if (outSpec.Aligment != FormatAlignment::None)
				{
					switch (*begin)
					{
					case StdString::ConstValues<TChar>::OpenAngle:
						outSpec.Aligment = FormatAlignment::Left;
						++begin;
						break;
					case StdString::ConstValues<TChar>::CloseAngle:
						outSpec.Aligment = FormatAlignment::Right;
						++begin;
						break;
					case StdString::ConstValues<TChar>::Equal:
						outSpec.Aligment = FormatAlignment::Center;
						++begin;
						break;
					default:
						//may be number to be width
						break;
					}
				}

				//parse width
				outSpec.Width = (ushort)StdString::ParseUInt(begin, outNext);
				RETURN_FALSE_IF_ZERO(outSpec.Width);
				return true;
			}

			inline bool IsTrivial(ushort strLength)const
			{
				return Aligment == FormatAlignment::None || Width <= strLength;
			}

			bool CalculateWidth(size_t strLength, size_t& outLeftWidth, size_t& outRightWidth)const
			{
				if (Aligment != FormatAlignment::None)
				{
					uintp width = Width;
					if (strLength >= width)
					{
						//no align
						outLeftWidth = 0;
						outRightWidth = 0;
						return false;
					}
					else
					{
						//make align
						uintp spaceWidth = width - strLength;
						if (Aligment == FormatAlignment::Left)
						{
							outLeftWidth = 0;
							outRightWidth = spaceWidth;
						}
						else if (Aligment == FormatAlignment::Right)
						{
							outLeftWidth = spaceWidth;
							outRightWidth = 0;
						}
						else
						{
							//center
							outLeftWidth = spaceWidth / 2;
							outRightWidth = spaceWidth - outLeftWidth;
						}
					}
				}
				else
				{
					outLeftWidth = 0;
					outRightWidth = 0;
					return false;
				}
				return true;
			}

			void WriteString(BaseString<TChar>& stream, const TStringRef<TChar>& str)const
			{
				if (Aligment != FormatAlignment::None)
				{
					uintp width = Width;
					if (str.Length() >= width)
					{
						//no align
						stream += str;
					}
					else
					{
						//make align
						uintp spaceWidth = width - str.Length();
						if (Aligment == FormatAlignment::Left)
						{
							stream += str;
							stream.Append(Fill, spaceWidth);
						}
						else if (Aligment == FormatAlignment::Right)
						{
							stream.Append(Fill, spaceWidth);
							stream += str;
						}
						else
						{
							//center
							uintp leftWidth = spaceWidth / 2;
							uintp rightWidth = spaceWidth - leftWidth;
							stream.Append(Fill, leftWidth);
							stream += str;
							stream.Append(Fill, rightWidth);
						}
					}
				}
				else
				{
					stream += str;
				}
			}

			static void WriteString(BaseString<TChar>& stream, const TStringRef<TChar>& str, const AlignmentSpec<TChar>* alignSpec)
			{
				if (alignSpec != nullptr)
				{
					alignSpec->WriteString(stream, str);
				}
				else
				{
					stream += str;
				}
			}

			void WriteChar(BaseString<TChar>& stream, TChar str)const
			{
				if (Aligment != FormatAlignment::None)
				{
					uint width = Width;
					if (1 >= width)
					{
						//no align
						stream += str;
					}
					else
					{
						//make align
						uint spaceWidth = width - 1;
						if (Aligment == FormatAlignment::Left)
						{
							stream += str;
							stream.Append(Fill, spaceWidth);
						}
						else if (Aligment == FormatAlignment::Right)
						{
							stream.Append(Fill, spaceWidth);
							stream += str;
						}
						else
						{
							//center
							uint leftWidth = spaceWidth / 2;
							uint rightWidth = spaceWidth - leftWidth;
							stream.Append(Fill, leftWidth);
							stream += str;
							stream.Append(Fill, rightWidth);
						}
					}
				}
				else
				{
					stream += str;
				}
			}

			static void WriteChar(BaseString<TChar>& stream, TChar str, const AlignmentSpec<TChar>* alignSpec)
			{
				if (alignSpec != nullptr)
				{
					alignSpec->WriteChar(stream, str);
				}
				else
				{
					stream += str;
				}
			}

			static bool CalculateWidth(size_t strLength, size_t& outLeftWidth, size_t& outRightWidth, const AlignmentSpec<TChar>* alignSpec)
			{
				if (alignSpec == nullptr)
				{
					outLeftWidth = 0;
					outRightWidth = 0;
					return false;
				}
				else
				{
					return alignSpec->CalculateWidth(strLength, outLeftWidth, outRightWidth);
				}
			}

		};

		
	}
}

MEDUSA_END;
