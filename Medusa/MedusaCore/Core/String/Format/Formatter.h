// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "FormatValue.h"

MEDUSA_BEGIN;

namespace String
{
	namespace internal
	{
		template<typename TChar>
		class Formatter
		{
		public:
			template<size_t N>
			explicit Formatter(BaseString<TChar>& str, const FormatValue<TChar>(&args)[N]) : mStream(str), mArgs(args), mSize(N) {}
			~Formatter(void) {}

			FormatResult Run(const TStringRef<TChar>& format)
			{
				/*
				parsing state machine
				none->left

				*/

				enum class ParsingState
				{
					None,
					Left,
					Right,

					LeftMatched,
					End,
					Error,

				};


				const TChar* start = format.c_str();
				const TChar* end = start + format.Length();

				const TChar* current = start;
				ParsingState state = ParsingState::None;
				uint currentIndex = 0;
				while (true)
				{
					switch (state)
					{
					case ParsingState::None:
						while (true)
						{
							TChar c = *current++;
							if (c == StdString::ConstValues<TChar>::OpenBrace)
							{
								Write(start, current - 1);
								start = current - 1;
								state = ParsingState::Left;
								break;
							}
							else if (c == StdString::ConstValues<TChar>::CloseBrace)
							{
								Write(start, current - 1);
								start = current - 1;
								state = ParsingState::Right;
								break;
							}
							else if (*current == '\0')
							{
								Write(start, current);
								return FormatResult::Success;
							}
						}
						break;
					case ParsingState::Left:
						//++current;	//find next
						if (*current == StdString::ConstValues<TChar>::OpenBrace)
						{
							//double left
							Write(start, current);
							start = ++current;
							state = ParsingState::None;
						}
						else
						{
							state = ParsingState::LeftMatched;
						}
						break;
					case ParsingState::Right:
						//++current;	//find next
						if (*current == StdString::ConstValues<TChar>::CloseBrace)
						{
							//double right
							Write(start, current);
							start = ++current;
							state = ParsingState::None;
						}
						else
						{
							return FormatResult::InvalidFormatString;
						}
						break;
					case ParsingState::LeftMatched:
					{
						uint argIndex;
						if (*current == StdString::ConstValues<TChar>::CloseBrace)
						{
							//use auto index
							argIndex = currentIndex;
							++currentIndex;

							const FormatValue<TChar>* arg = ArgAt(argIndex);
							if (arg == nullptr)
							{
								return FormatResult::InvalidArgIndex;
							}

							FormatResult formatResult = arg->FormatTo(mStream, nullptr, nullptr, nullptr);
							if (formatResult != FormatResult::Success)
							{
								return formatResult;
							}
							++current;
							start = current;
							if (*current == '\0')
							{
								return FormatResult::Success;
							}
							else
							{
								state = ParsingState::None;
							}
						}
						else if (*current == StdString::ConstValues<TChar>::Colon)
						{
							argIndex = currentIndex;
							++currentIndex;
							//get arg
							const FormatValue<TChar>* arg = ArgAt(argIndex);
							if (arg == nullptr)
							{
								return FormatResult::InvalidArgIndex;
							}

							//parse format string
							//find right brace
							const TChar* formatBegin = ++current;
							const TChar* formatEnd = StdString::FindFirstChar(current, StdString::ConstValues<TChar>::CloseBrace);
							if (formatEnd == nullptr)
							{
								return FormatResult::InvalidFormatString;
							}

							FormatResult formatResult = arg->FormatTo(mStream, formatBegin, formatEnd, nullptr);
							if (formatResult != FormatResult::Success)
							{
								return formatResult;
							}
							current = formatEnd + 1;	//skip }
							start = current;
							if (*current == '\0')
							{
								return FormatResult::Success;
							}
							else
							{
								state = ParsingState::None;
							}
						}
						else
						{
							//find index

							TChar* outNext;
							argIndex = StdString::ParseUInt(current, &outNext);
							if (argIndex == 0 && outNext == current)
							{

								//no valid number
								return FormatResult::InvalidFormatString;
							}
							++currentIndex;



							//get arg
							const FormatValue<TChar>* arg = ArgAt(argIndex);
							if (arg == nullptr)
							{
								return FormatResult::InvalidArgIndex;
							}

							current = outNext;

							bool hasAlign = false;
							AlignmentSpec<TChar> outAlignSpec;
							//find alignment
							if (*current == StdString::ConstValues<TChar>::Comma)
							{
								//parse alignment
								++current;
								if (AlignmentSpec<TChar>::ParseAlignment(current, end, &outNext, outAlignSpec))
								{
									current = outNext;
								}
								else
								{
									return FormatResult::InvalidFormatString;
								}
								hasAlign = true;
							}

							//parse format string
							//find right brace
							const TChar* formatBegin = nullptr;
							const TChar* formatEnd = nullptr;
							if (*current == StdString::ConstValues<TChar>::Colon)
							{
								++current;
								formatBegin = current;
							}

							formatEnd = StdString::FindFirstChar(current, StdString::ConstValues<TChar>::CloseBrace);
							if (formatEnd == nullptr)
							{
								return FormatResult::InvalidFormatString;
							}

							FormatResult formatResult = arg->FormatTo(mStream, formatBegin, formatBegin ? formatEnd : nullptr, hasAlign ? &outAlignSpec : nullptr);
							if (formatResult != FormatResult::Success)
							{
								return formatResult;
							}
							current = formatEnd + 1;	//skip }
							start = current;
							if (*current == '\0')
							{
								return FormatResult::Success;
							}
							else
							{
								state = ParsingState::None;
							}
						}
					}

					break;
					default:
						break;
					}

				}

				return FormatResult::Success;
			}
		protected:
			void Write(const TChar* begin, const TChar* end)
			{
				mStream.Append(begin, end - begin);
			}

			const FormatValue<TChar>* ArgAt(uint index)const
			{
				if (index < mSize)
				{
					return mArgs + index;
				}
				return nullptr;
			}
		protected:
			BaseString<TChar>& mStream;
			const FormatValue<TChar>* mArgs;
			const size_t mSize;
		};

		template<typename TChar, size_t N>
		FormatResult Format(BaseString<TChar>& stream, const TStringRef<TChar>& format, const FormatValue<TChar>(&args)[N])
		{
			return Formatter<TChar>(stream, args).Run(format);
		}

		template<typename TChar, size_t N>
		THeapString<TChar> Format(const TStringRef<TChar>& format, const FormatValue<TChar>(&args)[N])
		{
			THeapString<TChar> str;
			Format(str, format, args);
			return std::move(str);
		}


	}
}
MEDUSA_END;
