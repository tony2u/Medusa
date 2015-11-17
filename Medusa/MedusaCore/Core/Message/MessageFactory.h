// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once

#include "MedusaCorePreDeclares.h"
#include "Core/Message/IMessage.h"
#include "Core/Pattern/Object/MapObjectFactory.h"
#include "Core/String/StringRef.h"

MEDUSA_BEGIN;


class MessageFactory:public MapObjectFactory<StringRef,IMessage*()>
{
public:
	using MapObjectFactory<StringRef,IMessage*()>::Create;
private:
	MessageFactory()
	{
		
	}
	~MessageFactory(){}
public:
	static MessageFactory& Instance()
	{
		static MessageFactory factory;
		return factory;
	}

};

MEDUSA_END;
