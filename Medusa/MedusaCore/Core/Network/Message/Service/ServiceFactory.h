// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once
#include "MedusaCorePreDeclares.h"
#include "Core/Pattern/Object/MapObjectFactory.h"
#include "Core/String/StringRef.h"
#include "IService.h"
#include "TcpClientService.h"
#include "MockService.h"
#include "ServiceType.h"


MEDUSA_BEGIN;


class ServiceFactory :public MapObjectFactory<ServiceType, IService*(size_t, StringRef, ushort)>
{
public:
	using MapObjectFactory<ServiceType, IService*(size_t, StringRef, ushort)>::Create;
private:
	ServiceFactory()
	{
		Register<MockService>(ServiceType::Mock);
		Register<TcpClientService>(ServiceType::TcpClient);
	}
	~ServiceFactory(){}
public:
	static ServiceFactory& Instance()
	{
		static ServiceFactory factory;
		return factory;
	}



};

MEDUSA_END;
