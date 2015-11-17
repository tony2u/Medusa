// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Command/EventArg/IEventArg.h"

MEDUSA_BEGIN;

class SingleDownloadingProgressEventArg:public IEventArg
{
	SingleDownloadingProgressEventArg& operator=(const SingleDownloadingProgressEventArg& val){return *this;}

public:
	SingleDownloadingProgressEventArg(const IHTTPDownloader& downloader,double total,double current)
		:mTotal(total),mCurrent(current), mDownloader(downloader)
	{

	}
	virtual ~SingleDownloadingProgressEventArg(void){}

	const double Total() const { return mTotal; }
	const double Current() const { return mCurrent; }
	const IHTTPDownloader& Downloader() const { return mDownloader; }

protected:
	const double mTotal;
	const double mCurrent;
	const IHTTPDownloader& mDownloader;
};

MEDUSA_END;

