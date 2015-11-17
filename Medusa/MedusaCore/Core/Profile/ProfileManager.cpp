// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"

#include "ProfileManager.h"

MEDUSA_BEGIN;



void ProfileManager::Reset()
{
	mRoot.Reset();
	mCurrentNode=&mRoot;
}

void ProfileManager::Begin(const StringRef& name ,size_t count/*=1*/,size_t logCount/*=0*/)
{
	if (!name.IsRefEqualsTo(mCurrentNode->Name()))
	{
		mCurrentNode=mCurrentNode->FindOrCreateChildNode(name,count,logCount);
	}
	mCurrentNode->Begin();
}

void ProfileManager::End()
{
	if (mCurrentNode->End())
	{
		mCurrentNode=mCurrentNode->Parent();
	}
}


void ProfileManager::PrintResult() const
{
	mRoot.PrintResult(StringRef::Empty,"\t");
}

void ProfileManager::StopAll()
{
	mRoot.Stop();
	PrintResult();
}

MEDUSA_END;