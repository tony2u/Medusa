// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Siren/SirenHeader.h"

//SIREN_HEADER_INCLUDE_BEGIN
#include "Core/String/FuckyString/FuckyStringNode.h"
//SIREN_HEADER_INCLUDE_END

MEDUSA_BEGIN;

class FuckyStringNode
{

public:
	struct Schema;
	FuckyStringNode();
	~FuckyStringNode();
//SIREN_HEADER_COMPARE_BEGIN
public:
	SIREN_COMMON(FuckyStringNode);
//SIREN_HEADER_COMPARE_END
//SIREN_HEADER_METHOD_BEGIN
public:
	SIREN_METHOD(int, Char);
	SIREN_METHOD(bool, IsFucky);
	SIREN_METHOD_DICTIONARY(int, FuckyStringNode*, Childs);
//SIREN_HEADER_METHOD_END
	const Dictionary<int, FuckyStringNode*>* ChildsPtr()const { return &mChilds; }
//SIREN_HEADER_FIELD_BEGIN
protected:
	int mChar;
	bool mIsFucky;
	Dictionary<int, FuckyStringNode*> mChilds;
//SIREN_HEADER_FIELD_END
};

//SIREN_HEADER_SCHEMA_BEGIN
struct FuckyStringNode::Schema
{
	SIREN_FIELD(0, 0, Required, FuckyStringNode, int, mChar);
	SIREN_FIELD(1, 1, Required, FuckyStringNode, bool, mIsFucky);
	SIREN_FIELD_DICTIONARY(2, 2, Required, FuckyStringNode, int, FuckyStringNode*, mChilds);
	SIREN_FIELDS_3(void,FuckyStringNode);
};
//SIREN_HEADER_SCHEMA_END

MEDUSA_END;