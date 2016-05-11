#pragma once
#include "MedusaPreDeclares.h"
MEDUSA_BEGIN;

enum class PODAnimiationFlags
{
	None=0,
	HasPosition=1,
	HasRotation=2, 
	HasScale=4, 
	HasMatrix=8
};

MEDUSA_END;
