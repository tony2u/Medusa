// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"

//SIREN_BODY_INCLUDE_BEGIN
#include "FuckyStringNode.h"
//SIREN_BODY_INCLUDE_END

MEDUSA_BEGIN;

FuckyStringNode::FuckyStringNode()
{
//SIREN_BODY_CONSTRUCT_BEGIN
	mChar = 0;
	mIsFucky = false;
//SIREN_BODY_CONSTRUCT_END
}

FuckyStringNode::~FuckyStringNode()
{
//SIREN_BODY_DESTRUCT_BEGIN
	SAFE_DELETE_DICTIONARY_VALUE(mChilds);
//SIREN_BODY_DESTRUCT_END
}

//SIREN_BODY_METADATA_BEGIN
SIREN_METADATA(FuckyStringNode, 15);
SIREN_PROPERTY_METADATA(0, FuckyStringNode, Char, 4, 0);
SIREN_PROPERTY_METADATA(1, FuckyStringNode, IsFucky, 7, false);
SIREN_PROPERTY_METADATA_STRUCT(2, FuckyStringNode, Childs, 6);
//SIREN_BODY_METADATA_END

MEDUSA_END;