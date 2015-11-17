// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "IPlayer.h"

MEDUSA_BEGIN;



IPlayer::IPlayer()
	:mIsChanged(false), mIsLogined(false)
{

}

IPlayer::~IPlayer()
{

}

bool IPlayer::Load()
{
	return true;
}

bool IPlayer::Save(bool isForceToSave /*= false*/)
{
	if (!isForceToSave)
	{
		RETURN_TRUE_IF_FALSE(mIsLogined);
		RETURN_TRUE_IF_FALSE(mIsChanged);
	}

	mIsChanged = false;
	return true;
}

void IPlayer::ResetToDefault()
{
	mIsLogined = false;
	MarkChanged();
}

void IPlayer::Update(float dt)
{
	//auto save
}

MEDUSA_END;