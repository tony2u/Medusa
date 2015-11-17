// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Net/HTTP/IHTTPDownloader.h"
#include "Core/String/HeapString.h"
#include "Core/IO/Stream/FileStream.h"
#include "Core/Hash/MD5.h"

MEDUSA_BEGIN;

class HTTPFileDownloader:public IHTTPDownloader
{
public:
	HTTPFileDownloader(const StringRef& url,const StringRef& localFilePath,const StringRef& md5);
	~HTTPFileDownloader(void);

	virtual bool Run(CURL* curl,size_t httpConnectTimeoutSeconds,size_t httpReadTimeoutSeconds,size_t httpReadLowSpeedLimit,size_t httpReadLowSpeedTime);

	StringRef LocalFilePath() const { return mLocalFilePath; }
private:
	static size_t WriteDataCallback(void *buffer, size_t size, size_t nmemb, void *user_p);
	

protected:
	HeapString mLocalFilePath;
	FileStream mDownloadedFile;
	MD5 mHasher;
};

MEDUSA_END;
