// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once
#include "MedusaCorePreDeclares.h"
#include "Core/String/HeapString.h"
#include "IService.h"
#include "Core/IO/Stream/MemoryStream.h"
#include "BaseSocketService.h"

MEDUSA_BEGIN;

class TcpClientService :public BaseSocketService
{
public:
	TcpClientService(size_t id, StringRef host, ushort port);
	virtual ~TcpClientService();
	virtual ServiceType Type()const override { return ServiceType::TcpClient; }


protected:
	virtual void OnStart() override;
	virtual void OnRun() override;

protected:
	const static int mInitialMessageBufferSize = 4096;	//4K

};
MEDUSA_END;
