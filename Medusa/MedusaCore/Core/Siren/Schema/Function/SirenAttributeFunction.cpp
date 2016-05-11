// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "SirenAttributeFunction.h"
#include "Core/Siren/Schema/SirenTextParser.h"
#include "Core/Log/Log.h"
#include "Core/Siren/Schema/SirenAssembly.h"

MEDUSA_BEGIN;

SirenAttributeFunction::SirenAttributeFunction()
	:ISirenFunction("attribute")
{
	
}

SirenAttributeFunction::~SirenAttributeFunction(void)
{
	
}

bool SirenAttributeFunction::Execute(SirenAssembly& assembly) const
{
	//invoke set attribute
	if (mArguments.Count() == 3)
	{
		auto* type = assembly.FindCustomTypeWithReference(mArguments[0]);
		if (type == nullptr)
		{
			Log::FormatError("Cannot find type:{}", mArguments[0]);
			return false;
		}

		type->AddAttribute(mArguments[1], mArguments[2]);

	}
	else if (mArguments.Count() == 2)
	{
		auto* type = assembly.FindCustomTypeWithReference(mArguments[0]);
		if (type == nullptr)
		{
			Log::FormatError("Cannot find type:{}", mArguments[0]);
			return false;
		}

		type->SetAttribute(mArguments[1]);
	}
	else
	{
		Log::FormatError("Invalid attribute func arguments count:{}.Only accept 2 or 3.", mArguments.Count());
		return false;
	}
	return true;
}

MEDUSA_END;