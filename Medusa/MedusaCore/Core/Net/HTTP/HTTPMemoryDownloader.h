// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Net/HTTP/IHTTPDownloader.h"
MEDUSA_BEGIN;

class HTTPMemoryDownloader:public IHTTPDownloader
{
public:
	HTTPMemoryDownloader(const StringRef& url,const StringRef& md5);
	~HTTPMemoryDownloader(void);

	virtual bool Run(CURL* curl,size_t httpConnectTimeoutSeconds,size_t httpReadTimeoutSeconds,size_t httpReadLowSpeedLimit,size_t httpReadLowSpeedTime);
	const std::vector<byte>& Data() const { return mData; }

private:
	static size_t WriteDataCallback(void *buffer, size_t size, size_t nmemb, void *user_p);
protected:
	std::vector<byte> mData;
};

MEDUSA_END;
