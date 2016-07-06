// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Log/ILogger.h"
#include "Core/Collection/List.h"
#include "LogDefines.h"
#include "LogMessagePool.h"
#include "LogMessageAutoRecycle.h"
#include "Core/Pattern/Share.h"
//[IGNORE_PRE_DECLARE_FILE]

MEDUSA_BEGIN;

template<typename TChar, LogLevel TLevel>
class LogStream;

class Log
{
	template<typename TChar, LogLevel TLevel>
	friend class LogStream;
	template <int N>
	struct Manipulator {};

	using NewLineManipulator = Manipulator<1>;
	using HeaderEnabledManipulator = Manipulator<2>;
	using HeaderDisabledManipulator = Manipulator<3>;


public:
	constexpr static NewLineManipulator NewLine{};
	constexpr static HeaderEnabledManipulator HeaderEnabled{};
	constexpr static HeaderDisabledManipulator HeaderDisabled{};
public:
	static bool Initialize(bool isConsole=false, StringRef name = StringRef::Empty);
	static bool Uninitialize();

	bool IsEnabled() const { return mEnabled; }
	void Enable(bool val) { mEnabled = val; }

	static LogLevel Level() { return mLogLevel; }
	static void SetLevel(LogLevel val) { mLogLevel = val; }
	static void AddLevel(LogLevel val) { MEDUSA_FLAG_ADD(mLogLevel, val); }
	static void RemoveLevel(LogLevel val) { MEDUSA_FLAG_REMOVE(mLogLevel, val); }

	static void AddLogger(ILogger* logger);
	static bool AddFileLogger(const StringRef& filePath);

	static void EnableHeader(bool val) { MEDUSA_FLAG_ENABLE(mLogLevel, LogLevel::WithHeader, val); }

	static void Update(float dt = 0.f);

	//////////////////////////////////////////////////////////////////////////
	template<typename... TArgs>
	static void FormatInfo(const char* format, TArgs&&... args)
	{
		return FormatLine(LogLevel::Info, format, std::forward<TArgs>(args)...);
	}

	template<typename... TArgs>
	static void FormatError(const char* format, TArgs&&... args)
	{
		return FormatLine(LogLevel::Error, format, std::forward<TArgs>(args)...);
	}

	template<typename... TArgs>
	static void AssertFormat(bool condition, const char* format, TArgs&&... args)
	{
		if (!condition)
		{
			return FormatLine(LogLevel::Assert, format, std::forward<TArgs>(args)...);
		}
	}

	template<typename... TArgs>
	static void AssertFailedFormat(const char* format, TArgs&&... args)
	{
		return FormatLine(LogLevel::Assert, format, std::forward<TArgs>(args)...);
	}

	template<typename T, typename... TArgs>
	static void AssertNotNullFormat(const T& item, const char* format, TArgs&&... args)
	{
		if (item == nullptr)
		{
			return FormatLine(LogLevel::Assert, format, std::forward<TArgs>(args)...);
		}
	}

	static void Info(StringRef message)
	{
		return Append(LogLevel::Info, message);
	}
	static void Error(StringRef message)
	{
		return Append(LogLevel::Error, message);
	}
	static void Assert(bool condition, StringRef message)
	{
		if (!condition)
		{
			return Append(LogLevel::Assert, message);
		}
	}
	static void AssertFailed(StringRef message)
	{
		return Append(LogLevel::Assert, message);
	}
	template<typename T>
	static void AssertNotNull(const T& item, StringRef message)
	{
		if (item == nullptr)
		{
			return Append(LogLevel::Assert, message);
		}
	}


	//////////////////////////////////////////////////////////////////////////
	template<typename... TArgs>
	static void FormatInfo(const wchar_t* format, TArgs&&... args)
	{
		return FormatLine(LogLevel::Info, format, std::forward<TArgs>(args)...);
	}

	template<typename... TArgs>
	static void FormatError(const wchar_t* format, TArgs&&... args)
	{
		return FormatLine(LogLevel::Error, format, std::forward<TArgs>(args)...);
	}

	template<typename... TArgs>
	static void AssertFormat(bool condition, const wchar_t* format, TArgs&&... args)
	{
		if (!condition)
		{
			return FormatLine(LogLevel::Assert, format, std::forward<TArgs>(args)...);
		}
	}

	template<typename... TArgs>
	static void AssertFailedFormat(const wchar_t* format, TArgs&&... args)
	{
		return FormatLine(LogLevel::Assert, format, std::forward<TArgs>(args)...);
	}

	template<typename T,typename... TArgs>
	static void AssertNotNullFormat(const T& item, const wchar_t* format, TArgs&&... args)
	{
		if (item == nullptr)
		{
			return FormatLine(LogLevel::Assert, format, std::forward<TArgs>(args)...);
		}
	}

	static void Info(WStringRef message)
	{
		return Append(LogLevel::Info, message);
	}
	static void Error(WStringRef message)
	{
		return Append(LogLevel::Error, message);
	}
	static void Assert(bool condition, WStringRef message)
	{
		if (!condition)
		{
			return Append(LogLevel::Assert, message);
		}
	}
	static void AssertFailed(WStringRef message)
	{
		return Append(LogLevel::Assert, message);
	}
	template<typename T>
	static void AssertNotNull(const T item, WStringRef message)
	{
		if (item == nullptr)
		{
			return Append(LogLevel::Assert, message);
		}
	}

	template<typename TException, typename... TArgs>
	static void AssertOrThrow(bool condition, const char* format, TArgs&&... args)
	{
		if (!condition)
		{
			HeapString str;
			str.AppendFormat(format, std::forward<TArgs>(args)...);
			Error(str);
			throw TException(str);
		}
	}

	template<typename TException, typename... TArgs>
	static void Throw(const char* format, TArgs&&... args)
	{
		HeapString str;
		str.AppendFormat(format, std::forward<TArgs>(args)...);
		Error(str);
		throw TException(str);
	}
private:
	template<typename T, typename... TArgs>
	static void FormatLine(LogLevel level, const T* format, TArgs&&... args)
	{
		using LogMessageType = TLogMessage<T>;
		RETURN_IF_FALSE(mEnabled);
		RETURN_IF_NULL(format);
		LogLevel cur = MEDUSA_FLAG_AND(mLogLevel, LogLevel::All);	//only compare events
		LogLevel val = MEDUSA_FLAG_AND(level, LogLevel::All);	//only compare events
		RETURN_IF_FALSE(cur <= val);

		LogLevel withHeader = MEDUSA_FLAG_AND(mLogLevel, LogLevel::WithHeader);	//add header if cur set
		MEDUSA_FLAG_ADD(level, withHeader);

		Share<LogMessageType> logMessage(new LogMessageType(level));
		logMessage->AddHeader();
		logMessage->FormatLine(format, std::forward<TArgs>(args)...);

		if (MEDUSA_FLAG_HAS(level, LogLevel::Assert))
		{
			PrintStackTrace(logMessage->MutableContent());
		}

		for (auto item : mLoggers)
		{
			item->Add(logMessage);
		}
	}

	template<typename T>
	static void Append(LogLevel level, const TStringRef<T>& message, bool newLine = true)
	{
		using LogMessageType = TLogMessage<T>;

		RETURN_IF_FALSE(mEnabled);
		LogLevel cur = MEDUSA_FLAG_AND(mLogLevel, LogLevel::All);	//only compare events
		LogLevel val = MEDUSA_FLAG_AND(level, LogLevel::All);	//only compare events
		RETURN_IF_FALSE(cur <= val);

		LogLevel withHeader = MEDUSA_FLAG_AND(mLogLevel, LogLevel::WithHeader);	//add header if cur set
		MEDUSA_FLAG_ADD(level, withHeader);

		Share<LogMessageType> logMessage(new LogMessageType(level));
		logMessage->AddHeader();
		if (newLine)
		{
			logMessage->AppendLine(message);
		}
		else
		{
			logMessage->Append(message);
		}
		if (MEDUSA_FLAG_HAS(level, LogLevel::Assert))
		{
			PrintStackTrace(logMessage->MutableContent());
		}

		for (auto item : mLoggers)
		{
			item->Add(logMessage);
		}
	}
public:

private:
	static void PrintStackTrace(HeapString& str);
	static void PrintStackTrace(WHeapString& str);

	static List<ILogger*> mLoggers;
	static bool mEnabled;
	static LogLevel mLogLevel;

};


template<typename TChar, LogLevel TLevel>
class LogStream
{
	using LogMessageType = TLogMessage<TChar>;

public:
	LogStream(LogLevel level = LogLevel::WithHeader)
	{
		MEDUSA_FLAG_ADD(level, TLevel);
		mMessage = new LogMessageType(level);
		LogLevel withHeader = MEDUSA_FLAG_AND(level, LogLevel::WithHeader);	//add header if cur set
		if (withHeader != LogLevel::None)
		{
			mMessage->ApplyHeader();
		}
	}
	~LogStream()
	{
		mMessage->MutableContent().AppendLine();
		for (auto item : Log::mLoggers)
		{
			item->Add(mMessage);
		}

	}
public:
	LogStream& operator<<(Log::NewLineManipulator)
	{
		mMessage->MutableContent().AppendLine();
		return *this;
	}

	LogStream& operator<<(Log::HeaderEnabledManipulator)
	{
		mMessage->EnableHeader(true);
		return *this;
	}
	LogStream& operator<<(Log::HeaderDisabledManipulator)
	{
		mMessage->EnableHeader(true);
		return *this;
	}

	LogStream& operator<<(LogLevel level)
	{
		mMessage->SetLevel(level);
		return *this;
	}

	template<typename T>
	inline typename std::enable_if<std::is_class<T>::value
		&& !std::is_same<T, TStringRef<TChar>>::value
		&& !std::is_same<T, std::basic_string<TChar, std::char_traits<TChar>, std::allocator<TChar> >>::value
		&& !std::is_base_of<BaseString<TChar>, T>::value,
		LogStream&>::type operator<<(const T& val)
	{
		auto&& str = val.template ToString<TChar>();
		mMessage->MutableContent() += str;
		return *this;
	}

	template<typename T>
	inline typename std::enable_if<!std::is_class<T>::value
		|| std::is_same<T, TStringRef<TChar>>::value
		|| std::is_same<T, std::basic_string<TChar, std::char_traits<TChar>, std::allocator<TChar> >>::value
		|| std::is_base_of<BaseString<TChar>, T>::value,
		LogStream&>::type operator<<(const T& val)
	{
		auto&& str = StringParser::ToStringT<TChar>(val);
		mMessage->MutableContent() += str;
		return *this;
	}

	LogStream& operator<<(const TChar* val)
	{
		mMessage->MutableContent() += val;
		return *this;
	}

	template<typename... TArgs>
	void Format(const TChar* format, TArgs&&... args)
	{
		if (!mMessage->MutableContent().AppendFormat(format, std::forward<TArgs>(args)...))
		{
			auto temp = StringParser::ToStringT<char>(THeapString<TChar>(format));
			throw new std::invalid_argument(temp.c_str());
		}
	}
private:
	Share<LogMessageType> mMessage;
};

using LogInfo = LogStream<char, LogLevel::Info>;
using LogError = LogStream<char, LogLevel::Error>;
using WLogInfo = LogStream<wchar_t, LogLevel::Info>;
using WLogError = LogStream<wchar_t, LogLevel::Error>;

#define MEDUSA_NOT_IMPLEMENT(func) Log::AssertFailed(false,#func" not implementd!");

#define LOG_ASSERT_NOT_NULL(p) Log::AssertNotNull(p,#p)
#define LOG_ASSERT_STRING_MAX_LENGTH(str,length) Log::AssertFormat(str.Length()<=length,#str" :{} length > "#length,str.c_str());
#define LOG_ASSERT_COLLECTION_MAX_COUNT(val,count) Log::AssertFormat(val.Count()<=count,#val" count:{}  > "#count,(uint)val.Count());

#define LOG_ASSERT_INT_RANGE(val,min,max) Log::AssertFormat(min<=max&&val>=min&&val<=max,#min"<= {}:{} <="#max,#val,(int)val);



MEDUSA_END;
