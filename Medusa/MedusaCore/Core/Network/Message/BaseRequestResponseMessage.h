// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "BaseRequestMessage.h"
#include "Core/Siren/Siren.h"

MEDUSA_BEGIN;

template<typename TRequest, typename TResponse>
class BaseRequestResponseMessage :public BaseRequestMessage<TRequest>
{
public:
	BaseRequestResponseMessage()
	{
		static std::atomic_uint mCurrentSessionId{ 0 };
		this->mSessionId = ++mCurrentSessionId;
	}

public:
	virtual bool NeedResponse()const override { return true; }

	const TResponse& Response()const { return mResponse; }
	TResponse& MutableResponse() { return mResponse; }
	void SetResponse(const TResponse& val) { mResponse = val; }
protected:
	TResponse mResponse;
};

MEDUSA_END;
