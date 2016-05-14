// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "StringPropertySet.h"
#include "Core/Log/Log.h"

MEDUSA_BEGIN;


bool StringPropertySet::ToBool(const StringRef& key, bool optional /*= false*/) const
{
	StringRef val = Get(key);
	if (val.IsEmpty())
	{
		return optional;
	}
	return StringParser::StringTo<bool>(val);
}

bool StringPropertySet::Parse(const StringRef& str)
{
	RETURN_TRUE_IF_EMPTY(str);
	//Key=Value,...
	List<StringRef> outPairs;
	StringParser::Split(str, ",", outPairs);

	List<StringRef> keyValuePair;
	for (auto& optionPair : outPairs)
	{
		keyValuePair.Clear();
		StringParser::Split(optionPair, "=", keyValuePair);
		if (keyValuePair.Count() == 2)
		{
			Add(keyValuePair[0], keyValuePair[1]);
		}
		else if (keyValuePair.Count() == 1)
		{
			Add(keyValuePair[0], HeapString::Empty);
		}
		else
		{
			Log::FormatError("Invalid attribute str:{} in {}", optionPair.c_str(), str.c_str());
			return false;
		}
	}

	return true;
}

MEDUSA_END;