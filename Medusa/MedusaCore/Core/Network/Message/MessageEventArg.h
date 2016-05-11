// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"

#include "Core/Network/Message/IMessage.h"

MEDUSA_BEGIN;

class MessageEventArg:public IEventArg
{
public:
	MessageEventArg(IMessage* message);
	virtual ~MessageEventArg(void);
	MessageEventArg(const MessageEventArg& e);
public:
	IMessage* Message() const { return mMessage; }
	void SetMessage(IMessage* val) { mMessage = val; }

	bool IsResultOk()const{return mMessage->IsResultOk();}

	template<typename T>
	T GetCustomError()const{return (T)mMessage->CustomError();}

	int GetServerError()const{return mMessage->ServerError();}

	template<typename T>
	T* Message() const { return (T*)mMessage; }

private:
	IMessage* mMessage;
};


MEDUSA_END;
