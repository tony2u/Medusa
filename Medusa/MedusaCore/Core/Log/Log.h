// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Pattern/Singleton.h"
#include "Core/Log/ILogger.h"
#include "Core/Collection/List.h"
#include "Core/Pattern/Event.h"


MEDUSA_BEGIN;

class Log
{
public:
	enum class Level
	{
		None = 0,
		Error = 1,
		Info = 2,
	};
public:
	typedef Delegate<void(StringRef text, Action0 callback)> AlertViewDelegate;
	typedef Delegate<void(WStringRef text, Action0 callback)> WAlertViewDelegate;


	static Event<void(StringRef text, Action0 callback)> AlertViewEvent;
	static Event<void(WStringRef text, Action0 callback)> WAlertViewEvent;

	static bool Initialize(StringRef name = StringRef::Empty);
	static bool Uninitialize();

	static Log::Level GetLevel() { return mLevel; }
	static void SetLevel(Log::Level val) { mLevel = val; }

	static void AddLogger(ILogger* logger);
	static void AddFileLogger(StringRef filePath, StringRef name = StringRef::Empty);

	static void EnableLogHeader(bool val);
	static void SetCurrentLevel(LogLevel val);

	//////////////////////////////////////////////////////////////////////////
	template<typename... TArgs>
	static void FormatInfo(const char* inFormat, const TArgs&... args)
	{
		RETURN_IF_NULL(inFormat);
		RETURN_IF_FALSE(mLevel<=Level::Info);

		if (!mBufferString.Format(inFormat, args...))
		{
			throw new std::invalid_argument(inFormat);
		}
		FOR_EACH_COLLECTION(i, mLoggers)
		{
			ILogger* logger = *i;
			logger->Info(mBufferString);
		}

	}
	static void Info(const char* inString);

	template<typename... TArgs>
	static void FormatError(const char* inFormat, const TArgs&... args)
	{
		RETURN_IF_FALSE(mLevel <= Level::Error);
		RETURN_IF_NULL(inFormat);

		if (!mBufferString.Format(inFormat, args...))
		{
			throw new std::invalid_argument(inFormat);
		}
		FOR_EACH_COLLECTION(i, mLoggers)
		{
			ILogger* logger = *i;
			logger->Error(mBufferString);
		}

	}
	static void Error(const char* inString);

	static void Info(StringRef inString) { return Info(inString.Buffer()); }
	static void Error(StringRef inString) { return Error(inString.Buffer()); }

	template<typename... TArgs>
	static void AssertFormat(bool condition, const char* inFormat, const TArgs&... args)
	{
		RETURN_IF_FALSE(mLevel <= Level::Error);
		RETURN_IF_NULL(inFormat);

		if (!condition)
		{
			if (!mBufferString.Format(inFormat, args...))
			{
				throw new std::invalid_argument(inFormat);
			}
			if (AlertViewEvent.IsEmpty())
			{
				FOR_EACH_COLLECTION(i, mLoggers)
				{
					ILogger* logger = *i;
					logger->Error(mBufferString);
				}
				AssertCallback();
			}
			else
			{
				FOR_EACH_COLLECTION(i, mLoggers)
				{
					ILogger* logger = *i;
					logger->Error(mBufferString);
				}
				AlertViewEvent(mBufferString, Log::AssertCallback);

			}
		}
	}
	static void Assert(bool condition, StringRef inString);

	template<typename... TArgs>
	static void AssertFailedFormat(const char* inFormat, const TArgs&... args)
	{
		RETURN_IF_FALSE(mLevel <= Level::Error);
		RETURN_IF_NULL(inFormat);

		if (!mBufferString.Format(inFormat, args...))
		{
			throw new std::invalid_argument(inFormat);
		}
		if (AlertViewEvent.IsEmpty())
		{
			FOR_EACH_COLLECTION(i, mLoggers)
			{
				ILogger* logger = *i;
				logger->Error(mBufferString);

			}
			AssertCallback();

		}
		else
		{
			HeapString text;
			FOR_EACH_COLLECTION(i, mLoggers)
			{
				ILogger* logger = *i;
				logger->Error(mBufferString);
			}
			AlertViewEvent(mBufferString, Log::AssertCallback);

		}
	}
	static void AssertFailed(StringRef inString);
	static void AssertNotNull(const void* item, StringRef paramName);

	template<typename... TArgs>
	static void AssertNotNullFormat(const void* item, const char* inFormat, const TArgs&... args)
	{
		RETURN_IF_FALSE(mLevel <= Level::Error);
		RETURN_IF_NULL(inFormat);

		if (item == nullptr)
		{
			if (!mBufferString.Format(inFormat, args...))
			{
				throw new std::invalid_argument(inFormat);
			}
			if (AlertViewEvent.IsEmpty())
			{
				FOR_EACH_COLLECTION(i, mLoggers)
				{
					ILogger* logger = *i;
					logger->Error(mBufferString);
				}
				AssertCallback();

			}
			else
			{
				FOR_EACH_COLLECTION(i, mLoggers)
				{
					ILogger* logger = *i;
					logger->Error(mBufferString);
				}
				AlertViewEvent(mBufferString, Log::AssertCallback);
			}

		}
	}

	//////////////////////////////////////////////////////////////////////////
	template<typename... TArgs>
	static void FormatInfo(const wchar_t* inFormat, const TArgs&... args)
	{
		RETURN_IF_NULL(inFormat);
		RETURN_IF_FALSE(mLevel <= Level::Info);

		if (!mBufferStringW.Format(inFormat, args...))
		{
			throw new std::invalid_argument((const char*)inFormat);
		}
		FOR_EACH_COLLECTION(i, mLoggers)
		{
			ILogger* logger = *i;
			logger->Info(mBufferStringW);
		}

	}

	static void Info(const wchar_t* inString);

	template<typename... TArgs>
	static void FormatError(const wchar_t* inFormat, const TArgs&... args)
	{
		RETURN_IF_FALSE(mLevel <= Level::Error);
		RETURN_IF_NULL(inFormat);

		if (!mBufferStringW.Format(inFormat, args...))
		{
			throw new std::invalid_argument((const char*)inFormat);
		}
		FOR_EACH_COLLECTION(i, mLoggers)
		{
			ILogger* logger = *i;
			logger->Error(mBufferStringW);
		}

	}

	static void Error(const wchar_t* inString);

	static void Info(WStringRef inString) { return Info(inString.Buffer()); }
	static void Error(WStringRef inString) { return Error(inString.Buffer()); }

	template<typename... TArgs>
	static void AssertFormat(bool condition, const wchar_t* inFormat, const TArgs&... args)
	{
		RETURN_IF_FALSE(mLevel <= Level::Error);
		RETURN_IF_NULL(inFormat);

		if (!condition)
		{
			if (!mBufferStringW.Format(inFormat, args...))
			{
				throw new std::invalid_argument((const char*)inFormat);
			}
			if (AlertViewEvent.IsEmpty())
			{
				FOR_EACH_COLLECTION(i, mLoggers)
				{
					ILogger* logger = *i;
					logger->Error(mBufferStringW);
				}
				AssertCallback();
			}
			else
			{
				FOR_EACH_COLLECTION(i, mLoggers)
				{
					ILogger* logger = *i;
					logger->Error(mBufferStringW);
				}
				WAlertViewEvent(mBufferStringW, Log::AssertCallback);

			}
		}
	}

	static void Assert(bool condition, WStringRef inString);

	template<typename... TArgs>
	static void AssertFailedFormat(const wchar_t* inFormat, const TArgs&... args)
	{
		RETURN_IF_FALSE(mLevel <= Level::Error);
		RETURN_IF_NULL(inFormat);

		if (!mBufferStringW.Format(inFormat, args...))
		{
			throw new std::invalid_argument((const char*)inFormat);
		}
		if (AlertViewEvent.IsEmpty())
		{
			FOR_EACH_COLLECTION(i, mLoggers)
			{
				ILogger* logger = *i;
				logger->Error(mBufferStringW);

			}
			AssertCallback();

		}
		else
		{
			HeapString text;
			FOR_EACH_COLLECTION(i, mLoggers)
			{
				ILogger* logger = *i;
				logger->Error(mBufferStringW);
			}
			WAlertViewEvent(mBufferStringW, Log::AssertCallback);

		}
	}

	static void AssertFailed(WStringRef inString);
	static void AssertNotNull(const void* item, WStringRef paramName);
	template<typename... TArgs>
	static void AssertNotNullFormat(const void* item, const wchar_t* inFormat, const TArgs&... args)
	{
		RETURN_IF_FALSE(mLevel <= Level::Error);
		RETURN_IF_NULL(inFormat);

		if (item == nullptr)
		{
			if (!mBufferStringW.Format(inFormat, args...))
			{
				throw new std::invalid_argument((const char*)inFormat);
			}
			if (AlertViewEvent.IsEmpty())
			{
				FOR_EACH_COLLECTION(i, mLoggers)
				{
					ILogger* logger = *i;
					logger->Error(mBufferStringW);
				}
				AssertCallback();

			}
			else
			{
				FOR_EACH_COLLECTION(i, mLoggers)
				{
					ILogger* logger = *i;
					logger->Error(mBufferStringW);
				}
				WAlertViewEvent(mBufferStringW, Log::AssertCallback);
			}

		}
	}

private:
	static void AssertCallback();
	static void PrintStackTrace();


	static List<ILogger*> mLoggers;
	static bool mEnabled;
	static Level mLevel;
	
	static HeapString mBufferString;
	static WHeapString mBufferStringW;

};


#define MEDUSA_NOT_IMPLEMENT(func) Log::AssertFailed(false,#func" not implementd!");

#define LOG_ASSERT_NOT_NULL(p) Log::AssertNotNull(p,#p)
#define LOG_ASSERT_STRING_MAX_LENGTH(str,length) Log::AssertFormat(str.Length()<=length,#str" :{} length > "#length,str.c_str());
#define LOG_ASSERT_COLLECTION_MAX_COUNT(val,count) Log::AssertFormat(val.Count()<=count,#val" count:{}  > "#count,(uint)val.Count());

#define LOG_ASSERT_INT_RANGE(val,min,max) Log::AssertFormat(min<=max&&val>=min&&val<=max,#min"<= {}:{} <="#max,#val,(int)val);



MEDUSA_END;
