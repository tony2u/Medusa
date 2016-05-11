// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/Network/Message/IMessage.h"
#include "Core/Log/Log.h"
#include "Core/Network/Message/MessageFactory.h"
#include "Core/Pattern/StaticConstructor.h"

MEDUSA_BEGIN;

template<typename TRequest,typename TResponse>
class BaseMessage:public IMessage
{
public:
	BaseMessage(){}
	virtual ~BaseMessage(void){}

public:
	virtual bool HasResponse()const{return mError==MessageError::Success&&this->mResponse.IsInitialized()&&mState==MessageState::Completed;}

	TRequest& RequestData(){ return mRequest; }
	void SetRequestData(const TRequest& val) { mRequest = val; }

	TResponse& ResponseData() { return mResponse; }
	void SetResponseData(const TResponse& val) { mResponse = val; }


	virtual void PrintRequest()const
	{
		HeapString outStr;
		Siren::SerializeJson(mRequest,outStr);
		Log::Info(outStr.c_str());
	}

	virtual MemoryData SerializeRequest()const
	{
		return Siren::SerializeBinary(mRequest);
	}

	virtual void ParseFromRequest(MemoryData data)
	{
		Siren::DeserializeBinaryTo(data, mRequest);
	}

	virtual void PrintResponse()const
	{
		HeapString outStr;
		Siren::SerializeJson(mResponse, outStr);
		Log::Info(outStr.c_str());
	}

	virtual MemoryData SerializeResponse()const
	{
		return Siren::SerializeBinary(mResponse);
	}

	virtual void ParseFromResponse(MemoryData data)
	{
		Siren::DeserializeBinaryTo(data, mResponse);
	}
	
protected:
	TRequest mRequest;
	TResponse mResponse;

};


MEDUSA_END;
