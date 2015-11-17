// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Net/HTTP/IHTTPDownloader.h"
#include "Core/Command/EventArg/IEventArg.h"
#include "Core/Collection/Queue.h"
#include "Core/String/StringRef.h"
#include "CoreLib/Common/curl/curl.h"

MEDUSA_BEGIN;

class HTTPClient
{
public:
	typedef Delegate<void (HTTPClient* sender,GlobalDownloadingProgressEventArg&)> GlobalDownloadingProgressEventHandler;

	HTTPClient(void);
	~HTTPClient(void);

	static bool Initialize();
	static bool Uninitialize();

	void AddFileTask(const StringRef& url,const StringRef& localFilePath,const StringRef& md5);
	void AddMemoryTask(const StringRef& url,const StringRef& md5);

	bool Run();
	GlobalDownloadingProgressEventHandler GlobalProgessHandler() const { return mGlobalProgessHandler; }
	void SetGlobalProgessHandler(GlobalDownloadingProgressEventHandler val) { mGlobalProgessHandler = val; }
	IHTTPDownloader::SingleDownloadingProgressEventHandler SingleProgressHandler() const { return mSingleProgressHandler; }
	void SetSingleProgressHandler(IHTTPDownloader::SingleDownloadingProgressEventHandler val) { mSingleProgressHandler = val; }

	size_t HTTPConnectTimeoutSeconds() const { return mHTTPConnectTimeoutSeconds; }
	void SetHTTPConnectTimeoutSeconds(size_t val) { mHTTPConnectTimeoutSeconds = val; }
	size_t HTTPReadTimeoutSeconds() const { return mHTTPReadTimeoutSeconds; }
	void SetHTTPReadTimeoutSeconds(size_t val) { mHTTPReadTimeoutSeconds = val; }
	size_t HTTPReadLowSpeedLimit() const { return mHTTPReadLowSpeedLimit; }
	void SetHTTPReadLowSpeedLimit(size_t val) { mHTTPReadLowSpeedLimit = val; }
	size_t HTTPReadLowSpeedTime() const { return mHTTPReadLowSpeedTime; }
	void SetHTTPReadLowSpeedTime(size_t val) { mHTTPReadLowSpeedTime = val; }
	bool IsResponseOK();
protected:
	bool FireProgressEvent(const IHTTPDownloader& downloader,size_t totalCount,size_t currentCount);

protected:
	CURL* mCURL;
	Queue<IHTTPDownloader*> mDownloaders;

	GlobalDownloadingProgressEventHandler mGlobalProgessHandler;
	IHTTPDownloader::SingleDownloadingProgressEventHandler mSingleProgressHandler;

	size_t mHTTPConnectTimeoutSeconds;
	size_t mHTTPReadTimeoutSeconds;

	size_t mHTTPReadLowSpeedLimit;
	size_t mHTTPReadLowSpeedTime;
};

MEDUSA_END;
