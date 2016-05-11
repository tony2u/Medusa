// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "ISirenFunction.h"
#include "Core/Log/Log.h"
#include "Core/Siren/Schema/SirenTextParser.h"

MEDUSA_BEGIN;

ISirenFunction::ISirenFunction(const StringRef& name /*= StringRef::Empty*/)
	:mName(name)
{
	
}

ISirenFunction::~ISirenFunction(void)
{
	
}

bool ISirenFunction::Parse(SirenAssembly& assembly, StringRef& refProto)
{
	//read arguments
	intp endIndex = refProto.IndexOf(')');
	if (endIndex < 0)
	{
		Log::Error("Invalid function.Lost ')' ");
		return false;
	}
	StringRef args = refProto.SubString(1, endIndex - 1);
	bool isSuccess = StringParser::Split(args, ",", mArguments, false);
	if (!isSuccess)
	{
		Log::FormatError("Invalid function argument:{}", args);
		return false;
	}

	refProto = refProto.SubString(endIndex);
	return SirenTextParser::EndBlock(refProto);
}

MEDUSA_END;