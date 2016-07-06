// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "BaseRequestResponseMessage.h"

MEDUSA_BEGIN;

template<typename TRequest, typename TResponse>
class SirenRequestResponseMessage :public BaseRequestResponseMessage<TRequest, TResponse>
{
public:
	using BaseRequestResponseMessage<TRequest, TResponse>::BaseRequestResponseMessage;
public:
	virtual MemoryData SerializeRequest() const override
	{
		return Siren::SerializeBinary(this->mRequest);
	}

	virtual bool DeserializeRequest(const MemoryData& val)override
	{
		return Siren::DeserializeBinaryTo(val, this->mRequest);
	}

	virtual MemoryData SerializeResponse() const override
	{
		return Siren::SerializeBinary(this->mResponse);
	}
	virtual bool DeserializeResponse(const MemoryData& val)override
	{
		return Siren::DeserializeBinaryTo(val, this->mResponse);
	}
};


MEDUSA_END;
