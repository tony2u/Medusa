#pragma once
#include "MedusaPreDeclares.h"
MEDUSA_BEGIN;

enum class ApplicationDebugInfoFlags
{
	None = 0,
	Performance = 1,
	GPU = 2,
	Touch = 4,
	All = Performance | GPU | Touch
};

MEDUSA_END;
