// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "Core/Pattern/Singleton.h"
#include "Core/Pattern/Sweeper.h"

MEDUSA_BEGIN;


class SceneSweeper :public Sweeper<IScene*>, public Singleton < SceneSweeper >
{
	friend class Singleton < SceneSweeper > ;
protected:
#ifdef MEDUSA_SAFE_CHECK
	virtual void OnAddFailed(IScene* item)const override;
#endif
	virtual void OnRelease(IScene* item)const override;

};

MEDUSA_END;
