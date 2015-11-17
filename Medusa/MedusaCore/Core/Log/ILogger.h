// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once

#include "MedusaCorePreDeclares.h"
#include "Core/Collection/List.h"
#include "LogLevel.h"
#include "Core/String/HeapString.h"

MEDUSA_BEGIN;

class ILogger
{
public:
	enum class LogType
	{
		Info,
		Error,
		Assert
	};
public:
	ILogger(StringRef name = StringRef::Empty,bool isLogHeader=true);
	virtual ~ILogger(void);
	StringRef GetLogStringA() const { return mBufferA; }
	WStringRef GetLogStringW() const { return mBufferW; }


	LogLevel CurrentLevel() const { return mCurrentLevel; }
	void SetCurrentLevel(LogLevel inCurrentLevel) { mCurrentLevel = inCurrentLevel; }
	bool IsLogInfo(){return mCurrentLevel.Has(LogLevel::Info);}
	bool IsLogError(){return mCurrentLevel.Has(LogLevel::Error);}
	bool IsLogAll(){return mCurrentLevel.Has(LogLevel::All);}

	bool IsLogHeaderEnabled() const { return mIsLogHeaderEnabled; }
	void EnableLogHeader(bool val) { mIsLogHeaderEnabled = val; }
public:
	template<typename... TArgs>
	void FormatInfo(const char* inFormat, const TArgs&... args)
	{
		RETURN_IF_FALSE(IsLogInfo());

		if (mIsLogHeaderEnabled)
		{
			LogHeaderInBufferA();
		}

		mBufferA.Format(mBufferA, inFormat, args...);

		OutputLogString(mBufferA.Buffer());
		OutputLogString("\n");
	}

	void Info(StringRef inString);

	template<typename... TArgs>
	void FormatError(const char* inFormat, const TArgs&... args)
	{
		RETURN_IF_FALSE(IsLogError());

		if (mIsLogHeaderEnabled)
		{
			LogHeaderInBufferA(LogType::Error);
		}

		OutputLogString("ERROR: ", LogType::Error);

		mBufferA.Format(inFormat, args...);

		OutputLogString(mBufferA.Buffer(), LogType::Error);
		OutputLogString("\n", LogType::Error);
	}

	void Error(StringRef inString);

	template<typename... TArgs>
	void AssertFormat(bool condition, const char* inFormat, const TArgs&... args)
	{
		if (!condition)
		{
			if (IsLogError())
			{
				FormatError(inFormat, args...);
			}

			assert(false);
		}
	}

	void Assert(bool condition,StringRef inString);

	template<typename... TArgs>
	void AssertFailedFormat(const char* inFormat, const TArgs&... args)
	{
		if (IsLogError())
		{
			FormatError(inFormat, args...);
		}

		assert(false);
	}
	void AssertFailed(StringRef inString);
public:
	template<typename... TArgs>
	void FormatInfo(const wchar_t* inFormat, const TArgs&... args)
	{
		RETURN_IF_FALSE(IsLogInfo());

		if (mIsLogHeaderEnabled)
		{
			LogHeaderInBufferW();
		}

		mBufferW.Format(mBufferW, inFormat, args...);

		OutputLogString(mBufferW.Buffer());
		OutputLogString(L"\n");
	}

	void Info(WStringRef inString);

	template<typename... TArgs>
	void FormatError(const wchar_t* inFormat, const TArgs&... args)
	{
		RETURN_IF_FALSE(IsLogError());

		if (mIsLogHeaderEnabled)
		{
			LogHeaderInBufferW(LogType::Error);
		}

		OutputLogString(L"ERROR: ", LogType::Error);

		mBufferW.Format(inFormat, args...);

		OutputLogString(mBufferW.Buffer(), LogType::Error);
		OutputLogString(L"\n", LogType::Error);
	}

	void Error(WStringRef inString);

	template<typename... TArgs>
	void AssertFormat(bool condition, const wchar_t* inFormat, const TArgs&... args)
	{
		if (!condition)
		{
			if (IsLogError())
			{
				FormatError(inFormat, args...);
			}

			assert(false);
		}
	}

	void Assert(bool condition,WStringRef inString);

	template<typename... TArgs>
	void AssertFailedFormat(const wchar_t* inFormat, const TArgs&... args)
	{
		if (IsLogError())
		{
			FormatError(inFormat, args...);
		}

		assert(false);
	}

	void AssertFailed(WStringRef inString);
protected:
	void LogHeaderInBufferA(LogType logType=LogType::Info);
	void LogHeaderInBufferW(LogType logType=LogType::Info);

	virtual void OutputLogString(StringRef inString,LogType logType=LogType::Info)=0;
	virtual void OutputLogString(WStringRef inString,LogType logType=LogType::Info)=0;
	virtual void SetLogColor(LogType logType){}
protected:
	HeapString mName;
	LogLevel mCurrentLevel;
	
	bool mIsLogHeaderEnabled;
	HeapString mBufferA;
	WHeapString mBufferW;
};

MEDUSA_END;
