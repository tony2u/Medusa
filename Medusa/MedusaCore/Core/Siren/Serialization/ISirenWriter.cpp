// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "ISirenWriter.h"
#include "Core/Siren/SirenObject.h"

MEDUSA_BEGIN;

ISirenWriter::~ISirenWriter()
{

}
bool ISirenWriter::OnValue(const SirenObject& val)
{
	switch (val.Type().ToInt())
	{
	case SirenTypeId::Bool.IntValue:
		return OnValue(val.GetBool());
	case SirenTypeId::Int8.IntValue:
		return OnValue(val.GetInt8());
	case SirenTypeId::UInt8.IntValue:
		return OnValue(val.GetUInt8());
	case SirenTypeId::Int16.IntValue:
		return OnValue(val.GetInt16());
	case SirenTypeId::UInt16.IntValue:
		return OnValue(val.GetUInt16());
	case SirenTypeId::Int32.IntValue:
		return OnValue(val.GetInt32());
	case SirenTypeId::UInt32.IntValue:
		return OnValue(val.GetUInt32());
	case SirenTypeId::Int64.IntValue:
		return OnValue(val.GetInt64());
	case SirenTypeId::UInt64.IntValue:
		return OnValue(val.GetUInt64());
	case SirenTypeId::Float.IntValue:
		return OnValue(val.GetFloat());
	case SirenTypeId::Double.IntValue:
		return OnValue(val.GetDouble());
	case SirenTypeId::String.IntValue:
		return OnValue(val.GetString());
	case SirenTypeId::Blob.IntValue:
		return OnValue(val.GetBlob());
	case SirenTypeId::Enum.IntValue:
		return OnValue(val.GetEnum());
	case SirenTypeId::List.IntValue:
	case SirenTypeId::Dictionary.IntValue:
	case SirenTypeId::Struct.IntValue:
	default:
		break;
	}

	return false;
}

MEDUSA_END;

