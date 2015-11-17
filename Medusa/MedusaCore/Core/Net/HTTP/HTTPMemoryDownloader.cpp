// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "Core/Net/HTTP/HTTPMemoryDownloader.h"
#include "Core/Log/Log.h"
#include "Core/Hash/MD5.h"
#include "Core/IO/Stream/FileStream.h"
#include "CoreLib/Common/curl/curl.h"

MEDUSA_BEGIN;

HTTPMemoryDownloader::HTTPMemoryDownloader(const StringRef& url,const StringRef& md5)
	:IHTTPDownloader(url,md5)
{
	
}

HTTPMemoryDownloader::~HTTPMemoryDownloader(void)
{
}


bool HTTPMemoryDownloader::Run(CURL* curl,size_t httpConnectTimeoutSeconds,size_t httpReadTimeoutSeconds,size_t httpReadLowSpeedLimit,size_t httpReadLowSpeedTime)
{
	mIsSuccess=true;
	mData.reserve(1024);
	//set url
	curl_easy_setopt(curl,CURLOPT_URL,mUrl.c_str());
	//set write data callback
	curl_easy_setopt(curl,CURLOPT_WRITEDATA,&mData);
	curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION,&WriteDataCallback);
	//show progress
	curl_easy_setopt(curl,CURLOPT_NOPROGRESS,0);
	curl_easy_setopt(curl,CURLOPT_PROGRESSDATA,this);
	curl_easy_setopt(curl,CURLOPT_PROGRESSFUNCTION,&ProgressCallback);
	curl_easy_setopt(curl,CURLOPT_CONNECTTIMEOUT,httpConnectTimeoutSeconds);	//timeout to connect
	curl_easy_setopt(curl,CURLOPT_TIMEOUT,httpReadTimeoutSeconds);			//timeout to download files

	CURLcode code= curl_easy_perform(curl);
	if(code!=CURLE_OK)
	{
		const char* str=curl_easy_strerror(code);
		Log::FormatError("CURL error:{}",str);
		mIsSuccess=false;
		return false;
	}

	long retcode = 0;
	code = curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE , &retcode); 
	if ( (code != CURLE_OK) || retcode != 200 )	//may be 404 not found
	{
		Log::FormatError("Cannot download file,404 NOT found");
		return false;
	}

	if (!mMD5Check.IsEmpty())
	{
		MD5 md5Coder(mData.data(),mData.size());
		HeapString resultMd5=md5Coder.ToString();
		if (resultMd5!=mMD5Check)
		{
			Log::FormatError("Failed to check MD5 for {}",mUrl.c_str());
			mIsSuccess=false;
			return false;
		}
	}

	return mIsSuccess;
}


size_t HTTPMemoryDownloader::WriteDataCallback( void *buffer, size_t size, size_t nmemb, void *user_p )
{
	//Cannot new in this func, don't know why
	std::vector<byte>* data=(std::vector<byte>*)user_p;
	size_t total=size*nmemb;
	byte* byteBuffer=(byte*)buffer;
	FOR_EACH_SIZE(i,total)
	{
		data->push_back(byteBuffer[i]);
	}

	return total;
}
MEDUSA_END;
