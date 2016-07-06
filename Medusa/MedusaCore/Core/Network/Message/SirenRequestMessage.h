// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "BaseRequestMessage.h"
#include "Core/Siren/Siren.h"

MEDUSA_BEGIN;

template<typename TRequest>
class SirenRequestMessage :public BaseRequestMessage<TRequest>
{
public:
	using BaseRequestMessage<TRequest>::BaseRequestMessage;
public:
	virtual MemoryData SerializeRequest() const override
	{
		return Siren::SerializeBinary(this->mRequest);
	}
	
	virtual bool DeserializeRequest(const MemoryData& val)override
	{
		return Siren::DeserializeBinaryTo(val, this->mRequest);
	}
	
};


MEDUSA_END;
