// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "Core/Log/Log.h"
#include "Core/Log/FileLogger.h"
#include "Core/IO/Path.h"

#ifdef MEDUSA_WINDOWS
#ifdef _CONSOLE
#include "Core/Log/win/WindowsConsoleLogger.h"
#define DEFAULT_LOGGER WindowsConsoleLogger
#else
#include "Core/Log/win/WindowsTraceLogger.h"
#define DEFAULT_LOGGER WindowsTraceLogger
#endif

#elif defined(MEDUSA_IOS)
#include "Core/Log/ios/IOSConsoleLogger.h"
#define DEFAULT_LOGGER IOSConsoleLogger

#elif defined(MEDUSA_ANDROID)
#include "Core/Log/android/AndroidTraceLogger.h"
#define DEFAULT_LOGGER AndroidTraceLogger
#elif defined(MEDUSA_LINUX)
#include "Core/Log/linux/LinuxConsoleLogger.h"
#define DEFAULT_LOGGER LinuxConsoleLogger
#else
#error "No plaform for default logger";

#endif

MEDUSA_BEGIN;

bool Log::Initialize(StringRef name /*= StringRef::Empty*/)
{
	mLoggers.Append(new DEFAULT_LOGGER(name));
	return true;
}

bool Log::Uninitialize()
{
	SAFE_DELETE_COLLECTION(mLoggers);
	return true;
}



void Log::AddLogger(ILogger* logger)
{
	mLoggers.Append(logger);
}

void Log::AddFileLogger(StringRef filePath, StringRef name /*= StringRef::Empty*/)
{
	FileLogger* logger = new FileLogger(filePath, name);
	AddLogger(logger);
}

void Log::SetCurrentLevel(LogLevel val)
{
	for (auto logger : mLoggers)
	{
		logger->SetCurrentLevel(val);
	}
}

void Log::EnableLogHeader(bool val)
{
	for (auto logger : mLoggers)
	{
		logger->EnableLogHeader(val);
	}
}

//////////////////////////////////////////////////////////////////////////



void Log::Info(const char* inString)
{
	RETURN_IF_FALSE(mLevel <= Level::Info);
	RETURN_IF_NULL(inString);

	FOR_EACH_COLLECTION(i, mLoggers)
	{
		ILogger* logger = *i;
		logger->Info(inString);
	}
}

void Log::Error(const char* inString)
{
	RETURN_IF_FALSE(mLevel <= Level::Error);
	RETURN_IF_NULL(inString);

	FOR_EACH_COLLECTION(i, mLoggers)
	{
		ILogger* logger = *i;
		logger->Error(inString);
	}

}


void Log::Assert(bool condition, StringRef inString)
{
	RETURN_IF_FALSE(mLevel <= Level::Error);

	if (!condition)
	{
		FOR_EACH_COLLECTION(i, mLoggers)
		{
			ILogger* logger = *i;
			logger->Error(inString);
		}
		if (AlertViewEvent.IsEmpty())
		{
			AssertCallback();
		}
		else
		{
			AlertViewEvent(inString, Log::AssertCallback);
		}
	}
}


void Log::AssertFailed(StringRef inString)
{
	RETURN_IF_FALSE(mLevel <= Level::Error);

	FOR_EACH_COLLECTION(i, mLoggers)
	{
		ILogger* logger = *i;
		logger->Error(inString);
	}
	if (AlertViewEvent.IsEmpty())
	{
		AssertCallback();
	}
	else
	{
		AlertViewEvent(inString, Log::AssertCallback);
	}
}

void Log::AssertNotNull(const void* item, StringRef paramName)
{
	RETURN_IF_FALSE(mLevel <= Level::Error);

	if (item == nullptr)
	{
		if (AlertViewEvent.IsEmpty())
		{
			FOR_EACH_COLLECTION(i, mLoggers)
			{
				ILogger* logger = *i;
				logger->FormatError("{} should not be null!", paramName);
			}
			AssertCallback();

		}
		else
		{
			HeapString text;
			FOR_EACH_COLLECTION(i, mLoggers)
			{
				ILogger* logger = *i;
				logger->FormatError("{} should not be null!", paramName);
				text = logger->GetLogStringA();
			}
			AlertViewEvent(text, Log::AssertCallback);

		}


	}
}


void Log::Info(const wchar_t* inString)
{
	RETURN_IF_FALSE(mLevel <= Level::Info);
	RETURN_IF_NULL(inString);

	FOR_EACH_COLLECTION(i, mLoggers)
	{
		ILogger* logger = *i;
		logger->Info(inString);
	}
}

void Log::Error(const wchar_t* inString)
{
	RETURN_IF_FALSE(mLevel <= Level::Error);
	RETURN_IF_NULL(inString);


	FOR_EACH_COLLECTION(i, mLoggers)
	{
		ILogger* logger = *i;
		logger->Error(inString);
	}

}

void Log::Assert(bool condition, WStringRef inString)
{
	RETURN_IF_FALSE(mLevel <= Level::Error);

	if (!condition)
	{
		FOR_EACH_COLLECTION(i, mLoggers)
		{
			ILogger* logger = *i;
			logger->Error(inString);
		}
		if (WAlertViewEvent.IsEmpty())
		{
			AssertCallback();
		}
		else
		{
			WAlertViewEvent(inString, Log::AssertCallback);
		}
	}
}

void Log::AssertFailed(WStringRef inString)
{
	RETURN_IF_FALSE(mLevel <= Level::Error);

	FOR_EACH_COLLECTION(i, mLoggers)
	{
		ILogger* logger = *i;
		logger->Error(inString);
	}
	if (WAlertViewEvent.IsEmpty())
	{
		AssertCallback();
	}
	else
	{
		WAlertViewEvent(inString, Log::AssertCallback);
	}
}

void Log::AssertNotNull(const void* item, WStringRef paramName)
{
	RETURN_IF_FALSE(mLevel <= Level::Error);

	if (item == nullptr)
	{
		if (WAlertViewEvent.IsEmpty())
		{
			FOR_EACH_COLLECTION(i, mLoggers)
			{
				ILogger* logger = *i;
				logger->FormatError(L"{} should not be null!", paramName);
			}
			AssertCallback();
		}
		else
		{
			WHeapString text;
			FOR_EACH_COLLECTION(i, mLoggers)
			{
				ILogger* logger = *i;
				logger->FormatError(L"{} should not be null!", paramName);
				text = logger->GetLogStringW();
			}
			WAlertViewEvent(text, Log::AssertCallback);
		}


	}
}

void Log::AssertCallback()
{
	PrintStackTrace();
	__MedusaAssertFailed();
}


void Log::PrintStackTrace()
{
#ifdef MEDUSA_DEBUG
#ifdef MEDUSA_WINDOWS
	void* frames[100];

	HANDLE process = GetCurrentProcess();
	SymInitialize(process, nullptr, TRUE);

	ushort frameCount = CaptureStackBackTrace(0, 100, frames, nullptr);
	SYMBOL_INFO* symbol = (SYMBOL_INFO *)calloc(sizeof(SYMBOL_INFO) + 256 * sizeof(char), 1);
	symbol->MaxNameLen = 255;
	symbol->SizeOfStruct = sizeof(SYMBOL_INFO);
	HeapString str;
	str.AppendLine("***************STACK_BEGIN***************");
	FOR_EACH_SIZE_BEGIN_END(i, 1U, (size_t)frameCount - 1)	//start from 1 to remove  "Log::PrintStackTrace" self
	{
		SymFromAddr(process, (DWORD64)(frames[i]), 0, symbol);
		str.AppendFormat("{}:\t{}\n", frameCount - i - 1, symbol->Name);
	}
	str.AppendLine("***************STACK_END***************");

	FOR_EACH_COLLECTION(i, mLoggers)
	{
		ILogger* logger = *i;
		bool val = logger->IsLogHeaderEnabled();
		logger->EnableLogHeader(false);
		logger->Info(str);
		logger->EnableLogHeader(val);
	}

	SAFE_FREE(symbol);
#elif defined(MEDUSA_ANDROID)||defined(MEDUSA_IOS)
	HeapString str;

	void* buffer[100];
	std::pair<void**, void**> state = { buffer, buffer + 100 };

	_Unwind_Backtrace([](_Unwind_Context* context, void* arg)->_Unwind_Reason_Code
	{
		std::pair<void**, void**>* state = static_cast<std::pair<void**, void**>*>(arg);
		uintptr_t pc = _Unwind_GetIP(context);
		if (pc)
		{
			if (state->first == state->second)
			{
				return _URC_END_OF_STACK;
			}
			else
			{
				*state->first++ = reinterpret_cast<void*>(pc);
			}
		}
		return _URC_NO_REASON;
	}, &state);


	size_t frameCount = state.first - buffer;
	str.AppendLine("***************STACK_BEGIN***************");

	FOR_EACH_SIZE(i, frameCount)
	{
		const void* addr = buffer[i];
		const char* symbol = "";

		Dl_info info;
		if (dladdr(addr, &info) && info.dli_sname)
		{
			symbol = info.dli_sname;
		}

		str.AppendFormat("{}:{:x}\t{}\n", frameCount - i - 1, addr, symbol);
	}
	str.AppendLine("***************STACK_END***************");
	FOR_EACH_COLLECTION(i, mLoggers)
	{
		ILogger* logger = *i;
		bool val = logger->IsLogHeaderEnabled();
		logger->EnableLogHeader(false);
		logger->Info(str);
		logger->EnableLogHeader(val);
	}
#else

	void *frames[100];
	int  frameCount = backtrace(frames, 100);

	/* The call backtrace_symbols_fd(frames, frameCount, STDOUT_FILENO)

	*  would produce similar output to the following: */
	char** strs = backtrace_symbols(frames, frameCount);

	HeapString str;
	str.AppendLine("***************STACK_BEGIN***************");
	FOR_EACH_SIZE_BEGIN_END(i, 1U, (size_t)frameCount - 1)	//start from 1 to remove  "Log::PrintStackTrace" self
	{
		str.AppendFormat("{}:\t{}\n", frameCount - i - 1, str[i]);
	}
	str.AppendLine("***************STACK_END***************");

	FOR_EACH_COLLECTION(i, mLoggers)
	{
		ILogger* logger = *i;
		bool val = logger->IsLogHeaderEnabled();
		logger->EnableLogHeader(false);
		logger->Info(str);
		logger->EnableLogHeader(val);
	}

	SAFE_FREE(strs);
#endif
#endif
}

Event<void(WStringRef text, Action0 callback)> Log::WAlertViewEvent;
Event<void(StringRef text, Action0 callback)> Log::AlertViewEvent;

bool Log::mEnabled = true;
Log::Level Log::mLevel = Log::Level::Error;


HeapString Log::mBufferString;
WHeapString Log::mBufferStringW;


List<ILogger*> Log::mLoggers;

MEDUSA_END;
