#pragma once
#include "MedusaCorePreDeclares.h"
MEDUSA_BEGIN;
enum class LogLevel
{
	None=0,
	Info=1,
	Error=2,
	All=Info|Error,
};

enum class LogType
{
	Info,
	Error,
	Assert
};

MEDUSA_END;
