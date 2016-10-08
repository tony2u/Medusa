// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "Core/Pattern/RTTI/RTTIObject.h"
#include "Core/String/HeapString.h"
#include "Resource/ResourceType.h"

MEDUSA_BEGIN;

class NodeInstantiateInfo :public RTTIObject
{
	MEDUSA_RTTI_ROOT(NodeInstantiateInfo);
public:
	InstantiateMode Mode = InstantiateMode::None;
	HeapString NodeClassName;
	INode* ParentNode = nullptr;
};


MEDUSA_END;