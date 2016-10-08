// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Network/Message/SirenRequestResponseMessage.h"
#include "Proto/LoginRequest.h"
#include "Proto/LoginResponse.h"


USING_MEDUSA;

class LoginMessage :public SirenRequestResponseMessage<LoginRequest, LoginResponse>
{
	MEDUSA_DECLARE_MESSAGE(LoginMessage, IMessage);
public:
	using BaseType = SirenRequestResponseMessage<LoginRequest, LoginResponse>;
	LoginMessage();
	~LoginMessage(void);
public:
	virtual bool OnRequest(MessageSocketConnection& connection) override;
	virtual bool OnResponse(MessageSocketConnection& connection) override;
};

MEDUSA_ENABLE_STATIC_CONSTRUCTOR(LoginMessage);