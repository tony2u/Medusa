// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/Message/IMessage.h"
#include "Core/Collection/List.h"
MEDUSA_BEGIN;

class BaseCustomMessage:public IMessage
{
public:
	BaseCustomMessage();
	virtual ~BaseCustomMessage(void);
	virtual MessageType Type()const{return MessageType::Custom;}

	virtual bool IsResultOk()const;
	virtual int ServerError()const;
	virtual int CustomError()const{return 0;}

public:
	virtual void Update(float dt);
	virtual void PrepareReadyForSend();
	virtual void PrepareToNextRunning();
	virtual void BeforeEnd();

protected:
	void AddPrevMessage(IMessage* message);
	void AddNextMessage(IMessage* message);
	bool IsPrevMessagesResultOk();
	bool IsNextMessagesResultOk();
protected:
	virtual void SendPrevMessages(){}
	virtual void SendNextMessages(){}
	virtual void UpdatePrevData(){}
	virtual void UpdateNextData(){}
	

protected:
	List<IMessage*> mPrevMessages;
	List<IMessage*> mNextMessages;
	int mLastError;
	mutable IMessage* mLastErrorMessage;
};
MEDUSA_END;
