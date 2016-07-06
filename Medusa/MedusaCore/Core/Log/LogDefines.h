#pragma once
#include "MedusaCorePreDeclares.h"
MEDUSA_BEGIN;

enum class LogLevel
{
	None = 0,
	Info = 1,
	Error = 2,
	Assert = 4,
	All = Info | Error | Assert,
	WithHeader = 8,
};


MEDUSA_END;
