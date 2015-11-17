// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once
#include "MedusaCorePreDeclares.h"
#include "Core/Collection/Dictionary.h"

MEDUSA_BEGIN;

template<typename TKey, typename TValue, typename TKeyHashCoder = DefaultHashCoder<TKey>, typename TValueHashCoder = DefaultHashCoder<TValue>, typename TKeyCompare = DefaultCompare<TKey>, typename TValueCompare = EqualCompare<TValue> >
class PropertySet :public Dictionary < TKey, TValue, TKeyHashCoder, TValueHashCoder, TKeyCompare, TValueCompare >
{

public:
	
	
};

MEDUSA_END;