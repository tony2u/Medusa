// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Pattern/Singleton.h"
#include "Core/Collection/Dictionary.h"
#include "Core/Chrono/ProfileNode.h"
MEDUSA_BEGIN;


class MessageStatics :public Singleton<MessageStatics>
{
	struct MessageNode	//[IGNORE_PRE_DECLARE]
	{
		uint Id;
		uint SessionId;
		ProfileNode RequestSend;
		ProfileNode RequestReceive;

		ProfileNode ResponseSend;
		ProfileNode ResponseReceive;

		ProfileNode RequestResponse;

		void Print(bool isClient)const;

	};

	MessageStatics();
	~MessageStatics(void);
	friend class Singleton<MessageStatics>;
public:
	bool IsClient()const {return mIsClient;}
	void SetClient(bool val) { mIsClient = val; }


	void BeginRequestSend(uint id,uint sessionId);
	void EndRequestSend(uint id, uint sessionId);

	void BeginResponseSend(uint id, uint sessionId);
	void EndResponseSend(uint id, uint sessionId);

	void BeginWrite(const ShareMessage& message);
	void EndWrite(const ShareMessage& message);

	void OnRequestReceive(const ShareMessage& message,StopWatch::Duration time);
	void OnResponseReceive(const ShareMessage& message, StopWatch::Duration time);

private:
	MessageNode* FindOrCreate(uint id);
private:
	Dictionary<uint, MessageNode*> mMessages;	//id
	bool mIsClient=false;
};

MEDUSA_END;
