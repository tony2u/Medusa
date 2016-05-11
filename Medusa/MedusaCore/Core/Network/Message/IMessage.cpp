// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "IMessage.h"
#include "Core/Network/Message/MessageDispatcher.h"
#include "Core/Network/Message/MessageEventArg.h"

MEDUSA_BEGIN;


IMessage::IMessage()
{
	mError=MessageError::Success;
	mState=MessageState::None;
	mRefCount=1;
	mTimeout=10.f;//default is 10s
	mTimeLeft=mTimeout;
	mServiceId=0;
	mSocketError=0;
	mIsProfileEnabled=true;
	mSendElapsedMilliseconds=0.f;
	mReceiveElapsedMilliseconds=0.f;
}


IMessage::~IMessage(void)
{
	mRefCount=0;
}

void IMessage::Send()
{
#ifdef MEDUSA_DEBUG
	mTotalStopWatch.Enable(mIsProfileEnabled);
#else
	mTotalStopWatch.Enable(false);
#endif

	mTotalStopWatch.Start();
	MessageDispatcher::Instance().Send(this);
	
}

void IMessage::Send( MessageEventHandler handler)
{
	SetCompleteHandler(handler);
	Send();
}

void IMessage::SetError( SocketError val )
{
	switch(val)
	{
	case SocketError::Success:
		mError=MessageError::Success;
		break;
	default:
		mError=MessageError::ConnectFail;
	}
}

void IMessage::Retain()
{
	++mRefCount;
}

void IMessage::Release()
{
	--mRefCount;
	if (mRefCount==0)
	{
		delete this;
	}
}

void IMessage::Update( float dt )
{
	mTimeLeft-=dt;
	if (IsTimeout())
	{
		mState=MessageState::ConnectFail;
	}
}


void IMessage::BeforeEnd()
{
	mTotalStopWatch.Shot();

	if (mCompleteHandler)
	{
		MessageEventArg eventArg(this);
		mCompleteHandler(this,eventArg);
	}
	
}


MEDUSA_IMPLEMENT_RTTI_ROOT(IMessage);

MEDUSA_END;
