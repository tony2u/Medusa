// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "LogDefines.h"
#include "Core/Pattern/ISharable.h"
#include "Core/Chrono/DateTime.h"
#include "Core/String/StringParser.h"
#include "Core/Threading/ThreadingDefines.h"

MEDUSA_BEGIN;

template<typename T>
class TLogMessage :public ISharableThreadSafe
{
public:
	TLogMessage(LogLevel level) :mLevel(level)
	{
		mTimestamp = std::chrono::system_clock::now();
#ifdef MEDUSA_WINDOWS
		mThreadId = ::GetCurrentThreadId();
#else
		mThreadId = (ThreadId)pthread_self();
#endif
	}
	~TLogMessage(void) = default;

	LogLevel Level() const { return mLevel; }
	void SetLevel(LogLevel val) { mLevel = val; }
	void EnableHeader(bool val)
	{
		MEDUSA_FLAG_ENABLE(mLevel, LogLevel::WithHeader, val);
	}


	THeapString<T>& MutableContent() { return mContent; }
	TStringRef<T> Content() const { return mContent; }
	void SetContent(const TStringRef<T>& val) { mContent = val; }

	time_t Timestamp() const { return mTimestamp; }
	void SetTimestamp(time_t val) { mTimestamp = val; }

	void Prepare(LogLevel level)
	{
		mLevel = level;
		mTimestamp = std::chrono::system_clock::now();
	}

	void Recycle()
	{
		mContent.Clear();
	}
public:

	template<typename... TArgs>
	void FormatLine(const T* format, TArgs&&... args)
	{
		if (!mContent.AppendFormat(format, std::forward<TArgs>(args)...))
		{
			auto temp = StringParser::ToStringT<char>(THeapString<T>(format));
			throw new std::invalid_argument(temp.c_str());
		}
		mContent.AppendLine();
	}

	template<typename... TArgs>
	void Format(const T* format, TArgs&&... args)
	{
		if (!mContent.AppendFormat(format, std::forward<TArgs>(args)...))
		{
			auto temp = StringParser::ToStringT<char>(THeapString<T>(format));
			throw new std::invalid_argument(temp.c_str());
		}
	}


	void AppendLine(const TStringRef<T>& val)
	{
		mContent.AppendLine(val);
	}
	void Append(const TStringRef<T>& val)
	{
		mContent.Append(val);
	}
	void AddHeader()
	{
		mContent += StringParser::ToStringT<T>(mThreadId);
		mContent.Append((T)' ');

		DateTime dateTime(mTimestamp);
		mContent += StringParser::ToStringT<T>(dateTime.ToLongString());
		constexpr static T str[] = { ' ','=','>',' ' };
		mContent.Append(str, 4);
	}
	void ApplyHeader()
	{
		if (MEDUSA_FLAG_HAS(mLevel, LogLevel::WithHeader))
		{
			AddHeader();
		}

		if (MEDUSA_FLAG_HAS(mLevel, LogLevel::Error))
		{
			constexpr static T str[] = { 'E','R','R','O','R',':' };
			mContent.Append(str, 6);
		}

		if (MEDUSA_FLAG_HAS(mLevel, LogLevel::Assert))
		{
			constexpr static T str[] = { 'A','S','S','E','R','T',':' };
			mContent.Append(str, 7);
		}
	}
protected:
	LogLevel mLevel = LogLevel::None;
	DateTime::TimePoint mTimestamp;
	THeapString<T> mContent;
	ThreadId mThreadId;
};

//[PRE_DECLARE_BEGIN]
typedef TLogMessage<char> LogMessage;
typedef TLogMessage<wchar_t> WLogMessage;
//[PRE_DECLARE_END]

MEDUSA_END;
