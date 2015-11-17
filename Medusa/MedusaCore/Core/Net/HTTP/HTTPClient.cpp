// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "Core/Net/HTTP/HTTPClient.h"
#include "Core/Net/HTTP/HTTPFileDownloader.h"
#include "Core/Net/HTTP/HTTPMemoryDownloader.h"
#include "Core/Net/HTTP/GlobalDownloadingProgressEventArg.h"
MEDUSA_BEGIN;

HTTPClient::HTTPClient(void)
{
	mHTTPConnectTimeoutSeconds=8;	//default 8 seconds
	mHTTPReadTimeoutSeconds=180;	//default 3 minutes
	mHTTPReadLowSpeedLimit=10;	//8b/s
	mHTTPReadLowSpeedTime=5;	//5s

	mCURL=curl_easy_init();
}

HTTPClient::~HTTPClient(void)
{
	curl_easy_cleanup(mCURL);
	mCURL=nullptr;
}

bool HTTPClient::Initialize()
{
	curl_global_init(CURL_GLOBAL_DEFAULT);
	return true;
}

bool HTTPClient::Uninitialize()
{
	curl_global_cleanup();
	return true;
}

bool HTTPClient::Run()
{
	size_t totalCount=mDownloaders.Count();
	size_t currentCount=0;

	bool isSuccess=true;
	while(!mDownloaders.IsEmpty())
	{
		IHTTPDownloader* downloader=mDownloaders.Head();
		mDownloaders.Pop();

		downloader->Run(mCURL,mHTTPConnectTimeoutSeconds,mHTTPReadTimeoutSeconds,mHTTPReadLowSpeedLimit,mHTTPReadLowSpeedTime);
		if (!downloader->IsSuccess())
		{
			isSuccess=false;
		}
		++currentCount;
		bool isContinue=FireProgressEvent(*downloader,totalCount,currentCount);
		SAFE_DELETE(downloader);
		BREAK_IF_FALSE(isContinue);
	}

	SAFE_DELETE_COLLECTION(mDownloaders);
	return isSuccess;
}


void HTTPClient::AddFileTask( const StringRef& url,const StringRef& localFilePath,const StringRef& md5)
{
	IHTTPDownloader* downloader=new HTTPFileDownloader(url,localFilePath,md5);
	downloader->SetProgressHandler(mSingleProgressHandler);
	mDownloaders.Push(downloader);
}

void HTTPClient::AddMemoryTask( const StringRef& url,const StringRef& md5)
{
	IHTTPDownloader* downloader=new HTTPMemoryDownloader(url,md5);
	downloader->SetProgressHandler(mSingleProgressHandler);
	mDownloaders.Push(downloader);
}


bool HTTPClient::FireProgressEvent(const IHTTPDownloader& downloader, size_t totalCount,size_t currentCount )
{
	if (mGlobalProgessHandler)
	{
		GlobalDownloadingProgressEventArg eventArg(*this,downloader,totalCount,currentCount);
		mGlobalProgessHandler(this,eventArg);
		return eventArg.IsContinue();
	}
	return true;
}

bool HTTPClient::IsResponseOK()
{
	long retcode = 0;
	CURLcode code = curl_easy_getinfo(mCURL, CURLINFO_RESPONSE_CODE , &retcode); 
	return code==CURLE_OK&&retcode==200;
}

MEDUSA_END;
