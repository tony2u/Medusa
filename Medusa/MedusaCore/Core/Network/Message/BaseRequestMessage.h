// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "IMessage.h"

MEDUSA_BEGIN;

template<typename TRequest>
class BaseRequestMessage :public IMessage
{
public:
	using RequestType = TRequest;
	constexpr static uint mStaticId = typename TRequest::Schema::Id;
	using IMessage::IMessage;
	BaseRequestMessage()
	{
		this->mId = mStaticId;
	}
public:
	virtual uint StaticId()const override { return mStaticId; }
	virtual bool NeedResponse()const override { return false; }

	const TRequest& Request()const { return mRequest; }
	TRequest& MutableRequest() { return mRequest; }
	void SetRequest(const TRequest& val) { mRequest = val; }
protected:
	TRequest mRequest;
};


MEDUSA_END;
