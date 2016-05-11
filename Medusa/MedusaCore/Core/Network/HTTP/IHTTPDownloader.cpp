// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "Core/Network/HTTP/IHTTPDownloader.h"
#include "Core/IO/Stream/FileStream.h"
#include "Core/Log/Log.h"
#include "Core/Hash/MD5.h"
#include "Core/Network/HTTP/SingleDownloadingProgressEventArg.h"

MEDUSA_BEGIN;


IHTTPDownloader::IHTTPDownloader(const StringRef& url,const StringRef& md5)
	:mUrl(url),mMD5Check(md5),mIsSuccess(false)
{
	
}

IHTTPDownloader::~IHTTPDownloader(void)
{
}


void IHTTPDownloader::FireProgressEvent( double total, double now )
{
	if (mProgressHandler)
	{
		SingleDownloadingProgressEventArg eventArg(*this,total,now);
		mProgressHandler(this,eventArg);
	}
}

int IHTTPDownloader::ProgressCallback( void *clientp, double dltotal, double dlnow, double ultotal, double ulnow )
{
	IHTTPDownloader* downloader=(IHTTPDownloader*)clientp;
	downloader->FireProgressEvent(dltotal,dlnow);
	return 0;
}
MEDUSA_END;
