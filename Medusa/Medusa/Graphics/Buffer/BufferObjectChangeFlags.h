#pragma once
#include "MedusaPreDeclares.h"
MEDUSA_BEGIN;
enum class BufferObjectChangeFlags
{
	None=0,
	Vertex=1, 
	TexCoord=2, 
	Color=4, 
	Indices=8,
	All= Vertex| TexCoord| Color| Indices
};

MEDUSA_END;
