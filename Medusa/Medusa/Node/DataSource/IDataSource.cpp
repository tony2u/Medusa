// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "IDataSource.h"

MEDUSA_BEGIN;


IDataSource::IDataSource( ):mIsChanging(false)
{
	
}

IDataSource::~IDataSource( void )
{

}

void IDataSource::PrepareForCommit()
{
	mIsChanging=true;
}

void IDataSource::Commit()
{
	OnDataChanged(*this);
	mIsChanging=false;
}

void IDataSource::FireDataChangedEvent()
{
	if (mIsChanging)
	{

	}
	else
	{
		OnDataChanged(*this);
	}
}


MEDUSA_END;