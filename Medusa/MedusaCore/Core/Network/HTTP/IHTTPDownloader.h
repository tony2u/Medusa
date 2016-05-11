// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Pattern/Delegate.h"
#include "Core/Command/EventArg/IEventArg.h"
#include "Core/String/StringRef.h"
#include "Core/String/HeapString.h"
typedef void CURL;


MEDUSA_BEGIN;


class IHTTPDownloader
{
public:
	typedef Delegate<void (IHTTPDownloader* sender,SingleDownloadingProgressEventArg&)> SingleDownloadingProgressEventHandler;

	IHTTPDownloader(const StringRef& url,const StringRef& md5);
	virtual ~IHTTPDownloader(void);

	virtual bool Run(CURL* curl,size_t httpConnectTimeoutSeconds,size_t httpReadTimeoutSeconds,size_t httpReadLowSpeedLimit,size_t httpReadLowSpeedTime)=0;

	bool IsSuccess() const { return mIsSuccess; }
	StringRef Url() const { return mUrl; }

	SingleDownloadingProgressEventHandler ProgressHandler() const { return mProgressHandler; }
	void SetProgressHandler(SingleDownloadingProgressEventHandler val) { mProgressHandler = val; }
protected:
	static int ProgressCallback(void *clientp, double downloadTotal, double downloadNow, double uploadTotal, double uploadNow);
	void FireProgressEvent(double total, double now);
protected:
	HeapString mUrl;
	HeapString mMD5Check;
	bool mIsSuccess;

	SingleDownloadingProgressEventHandler mProgressHandler;

};

MEDUSA_END;
