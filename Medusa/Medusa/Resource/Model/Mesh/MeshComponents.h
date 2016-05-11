#pragma once
#include "MedusaPreDeclares.h"
MEDUSA_BEGIN;
enum class MeshComponents
{
	None = 0,
	Vertex = 1,
	Normal = 2,
	Color = 4,
	Texcoord = 8,
	Index = 16,

	All = Vertex | Normal | Color | Texcoord | Index
};

MEDUSA_END;
