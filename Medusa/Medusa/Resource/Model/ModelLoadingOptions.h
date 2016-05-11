#pragma once
#include "MedusaPreDeclares.h"
MEDUSA_BEGIN;

enum class ModelLoadingOptions
{
	None = 0,
	NoCameraAnimation = 1,
	NoSkeletonAnimation = 2,
	NoLightAnimation = 4,
};

MEDUSA_END;
