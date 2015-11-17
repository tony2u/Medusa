// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once

#include "MedusaCorePreDeclares.h"
#include "Core/Profile/ProfileNode.h"
#include "Core/Pattern/Singleton.h"


MEDUSA_BEGIN;

class ProfileManager:public Singleton<ProfileManager>
{
	friend class Singleton<ProfileManager>;
private:
	ProfileManager():mRoot("Root",nullptr),mCurrentNode(&mRoot),mFrameCount(0)
	{

	}
	~ProfileManager(){}
public:
	void Reset();
	void Begin(const StringRef& name,size_t count=1,size_t logCount=0);
	void End();
	void PrintResult()const;

	void StopAll();
public:
	size_t FrameCount() const { return mFrameCount; }
	void AddFrameCount() { ++mFrameCount ; }
private:
	ProfileNode mRoot;
	ProfileNode* mCurrentNode;
	size_t mFrameCount;

};


MEDUSA_END;