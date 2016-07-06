// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#ifdef MEDUSA_HTTP

#include "Core/Network/HTTP/HTTPFileDownloader.h"
#include "Core/Log/Log.h"
#include "Core/IO/File.h"
#include "Core/IO/FileSystem.h"
#ifdef MEDUSA_WINDOWS
#include <WinSock2.h>
#endif
#include "CoreLib/Common/curl/curl.h"

MEDUSA_BEGIN;

HTTPFileDownloader::HTTPFileDownloader(const StringRef& url,const StringRef& localFilePath,const StringRef& md5)
	:IHTTPDownloader(url,md5),mLocalFilePath(localFilePath)
{
	
}

HTTPFileDownloader::~HTTPFileDownloader(void)
{
}


bool HTTPFileDownloader::Run(CURL* curl,size_t httpConnectTimeoutSeconds,size_t httpReadTimeoutSeconds,size_t httpReadLowSpeedLimit,size_t httpReadLowSpeedTime)
{
	mIsSuccess=true;
	if(!mDownloadedFile.OpenNewWriteBinary(mLocalFilePath))
	{
		Log::AssertFailedFormat("Cannot open local file: {}",mLocalFilePath.c_str());
		mIsSuccess=false;
		return false;
	}
	//set url
	curl_easy_setopt(curl,CURLOPT_URL,mUrl.c_str());
	//set write data callback
	curl_easy_setopt(curl,CURLOPT_WRITEDATA,this);
	curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION,&WriteDataCallback);
	//show progress
	curl_easy_setopt(curl,CURLOPT_NOPROGRESS,0);
	curl_easy_setopt(curl,CURLOPT_PROGRESSDATA,this);
	curl_easy_setopt(curl,CURLOPT_PROGRESSFUNCTION,&ProgressCallback);
	curl_easy_setopt(curl,CURLOPT_CONNECTTIMEOUT,httpConnectTimeoutSeconds);	//timeout to connect
	curl_easy_setopt(curl,CURLOPT_TIMEOUT,httpReadTimeoutSeconds);			//timeout to download files
	curl_easy_setopt(curl,CURLOPT_LOW_SPEED_LIMIT,httpReadLowSpeedLimit);	
	curl_easy_setopt(curl,CURLOPT_LOW_SPEED_TIME,httpReadLowSpeedTime);


	CURLcode code= curl_easy_perform(curl);
	if(code!=CURLE_OK)
	{
		const char* str=curl_easy_strerror(code);
		Log::FormatError("CURL error:{}",str);
		mIsSuccess=false;

		return false;
	}

	if (!mMD5Check.IsEmpty())
	{
		mDownloadedFile.Close();
		mHasher.Final();
		HeapString resultMd5=mHasher.ToString();
		if (resultMd5!=mMD5Check)
		{
			Log::FormatError("Failed to check MD5 for {}",mUrl.c_str());
			mIsSuccess=false;

			return false;
		}
		else
		{
			Log::FormatInfo("MD5 check OK! {}",mUrl.c_str());
			mIsSuccess=true;
		}

	}

	return mIsSuccess;
}


size_t HTTPFileDownloader::WriteDataCallback( void *buffer, size_t size, size_t nmemb, void *user_p )
{
	HTTPFileDownloader* downloader=(HTTPFileDownloader*)user_p;


	MemoryData data=MemoryData::FromStatic((byte*)buffer,size*nmemb);
	downloader->mHasher.Process((const byte*)buffer, size*nmemb);
	size_t resultSize= downloader->mDownloadedFile.WriteData(data);
	return resultSize;
}

MEDUSA_END;
#endif
