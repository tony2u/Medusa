// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "Core/Log/Log.h"
#include "Core/Log/FileLogger.h"
#include "Core/IO/Path.h"
#include "Core/IO/FileSystem.h"

#ifdef MEDUSA_DEBUG
#ifdef MEDUSA_WINDOWS
#pragma warning( push)
#pragma warning(disable:4091)	//warning C4091: 'typedef ': ignored on left of '' when no variable is declared (compiling source file
#include <Dbghelp.h>	//include this to support print stack trace
#pragma comment(lib, "Dbghelp.lib")
#pragma warning( pop)

#endif
#endif

#ifdef MEDUSA_WINDOWS
#include "Core/Log/win/WindowsConsoleLogger.h"
#include "Core/Log/win/WindowsTraceLogger.h"
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

bool Log::Initialize(bool isConsole /*= false*/, StringRef name /*= StringRef::Empty*/)
{
#ifdef MEDUSA_WINDOWS
	if (isConsole)
	{
		mLoggers.Append(new WindowsConsoleLogger(name));
	}
	else
	{
		mLoggers.Append(new WindowsTraceLogger(name));
	}
#else
	mLoggers.Append(new DEFAULT_LOGGER(name));
#endif
	return true;
}

bool Log::Uninitialize()
{
	LogMessagePool::Instance().Clear();
	WLogMessagePool::Instance().Clear();

	SAFE_DELETE_COLLECTION(mLoggers);
	return true;
}



void Log::AddLogger(ILogger* logger)
{
	mLoggers.Append(logger);
}

bool Log::AddFileLogger(const StringRef& filePath)
{
	FileStream fs;
	if (fs.Open(filePath, FileOpenMode::AppendReadWriteClearEOFOrCreate, FileDataType::Text))
	{
		fs.Close();
		FileLogger* logger = new FileLogger(filePath);
		AddLogger(logger);
		return true;
	}
	return false;
}


void Log::Update(float dt /*= 0.f*/)
{
	FOR_EACH_TO(mLoggers, Update(dt));
}

void Log::PrintStackTrace(WHeapString& str)
{
	HeapString temp;
	PrintStackTrace(temp);
	str += StringParser::ToW(temp);
}

void Log::PrintStackTrace(HeapString& str)
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
	str.AppendLine("***************STACK_BEGIN***************");
	FOR_EACH_SIZE_BEGIN_END(i, 1U, (size_t)frameCount - 1)	//start from 1 to remove  "Log::PrintStackTrace" self
	{
		SymFromAddr(process, (DWORD64)(frames[i]), 0, symbol);
		str.AppendFormat("{}:\t{}\n", frameCount - i - 1, symbol->Name);
	}
	str.AppendLine("***************STACK_END***************");
	SAFE_FREE(symbol);

#elif defined(MEDUSA_ANDROID)||defined(MEDUSA_IOS)

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
		StringRef symbol = "";

		Dl_info info;
		if (dladdr(addr, &info) && info.dli_sname)
		{
			symbol = info.dli_sname;
		}

		str.AppendFormat("{}:{:x}\t{}\n", frameCount - i - 1, addr, symbol);
	}
	str.AppendLine("***************STACK_END***************");

#else

	void *frames[100];
	int  frameCount = backtrace(frames, 100);

	/* The call backtrace_symbols_fd(frames, frameCount, STDOUT_FILENO)

	*  would produce similar output to the following: */
	char** strs = backtrace_symbols(frames, frameCount);

	str.AppendLine("***************STACK_BEGIN***************");
	FOR_EACH_SIZE_BEGIN_END(i, 1U, (size_t)frameCount - 1)	//start from 1 to remove  "Log::PrintStackTrace" self
	{
		str.AppendFormat("{}:\t{}\n", frameCount - i - 1, str[i]);
	}
	str.AppendLine("***************STACK_END***************");
	SAFE_FREE(strs);
#endif
#endif
}


bool Log::mEnabled = true;
LogLevel Log::mLogLevel = (LogLevel)MEDUSA_FLAG_OR(LogLevel::Info,LogLevel::WithHeader);
List<ILogger*> Log::mLoggers;



#undef  DEFAULT_LOGGER


MEDUSA_END;
