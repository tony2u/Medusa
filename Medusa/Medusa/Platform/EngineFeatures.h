#pragma once
#include "MedusaPreDeclares.h"
MEDUSA_BEGIN;

enum class EngineFeatures
{
	None = 0,
	MultipleThreadUpdating = 1,
	MultipleThreadRendering = 2,
	SupportThreadEvent = 4,
	SupportMessage = 8,
	SupportFileUpdating = 16,
};


MEDUSA_END;
