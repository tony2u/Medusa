// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#ifdef MEDUSA_HTTP
#include "Core/Network/HTTP/IHTTPDownloader.h"
#include "Core/Network/HTTP/HTTPClient.h"

MEDUSA_BEGIN;

class GlobalDownloadingProgressEventArg:public IEventArg
{
	GlobalDownloadingProgressEventArg& operator=(const GlobalDownloadingProgressEventArg& val){return *this;}

public:
	GlobalDownloadingProgressEventArg(const HTTPClient& client,const IHTTPDownloader& downloader,size_t total,size_t current)
		:mTotal(total), mCurrent(current),mIsContinue(true), mClient(client),mDownloader(downloader)
	{

	}
	virtual ~GlobalDownloadingProgressEventArg(void){}

	bool IsContinue() const { return mIsContinue; }
	void SetIsContinue(bool val) { mIsContinue = val; }

	size_t Total() const { return mTotal; }
	size_t Current() const { return mCurrent; }
	float Percent()const{return (float)mCurrent/mTotal;}
	const HTTPClient& Client() const { return mClient; }
	const IHTTPDownloader& Downloader() const { return mDownloader; }

protected:
	const size_t mTotal;
	const size_t mCurrent;
	bool mIsContinue;
	const HTTPClient& mClient;
	const IHTTPDownloader& mDownloader;
};


MEDUSA_END;
#endif
