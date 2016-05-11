// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/Network/Message/BaseMessage.h"
MEDUSA_BEGIN;

template<typename TRequest,typename TResponse>
class BaseRequestMessage:public BaseMessage<TRequest,TResponse>
{
public:
	BaseRequestMessage(){}
	virtual ~BaseRequestMessage(void){}

	virtual bool IsResultOk()const
	{
		if (this->mResponse.IsInitialized())
		{
			return this->mResponse.errorcode()==0;	//0 means success
		}
		return false;
	}
	virtual int CustomError()const
	{
		if (this->mResponse.IsInitialized())
		{
			return this->mResponse.errordetail();
		}
		return (int)this->mError;
	}

	virtual int ServerError()const
	{
		if (this->mResponse.IsInitialized())
		{
			return this->mResponse.errorcode();
		}
		return (int)this->mError;
	}

};

#define DECLARE_REGISTER_REQUEST(className) 													\
															\
public:																							 \
	virtual StringRef ResponseClassName()const{return mResponseClassName;}				\
	static StringRef GetResponseClassNameStatic(){return mResponseClassName;}				\
private:																				\
	const static StringRef mResponseClassName;												\
	const static StaticConstructor mStaticConstructor;							\
	static void SelfStaticCallback();


#define IMPLEMENT_REGISTER_REQUEST(className,baseClassName,reponseName) 																					 \
	MEDUSA_IMPLEMENT_RTTI(className,baseClassName);	\
	MEDUSA_WEAK_MULTIPLE_DEFINE const StringRef className::mResponseClassName=#reponseName;	\
	const StaticConstructor className::mStaticConstructor(SelfStaticCallback);					 \
	void className::SelfStaticCallback(){MessageFactory::Instance().Register<className>(#className);}

MEDUSA_END;
