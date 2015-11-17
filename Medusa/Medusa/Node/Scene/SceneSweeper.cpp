// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "SceneSweeper.h"
#include "IScene.h"
#include "Node/Scene/SceneManager.h"

#ifdef MEDUSA_SAFE_CHECK
#include "Core/Log/Log.h"
#endif

MEDUSA_BEGIN;

#ifdef MEDUSA_SAFE_CHECK
void SceneSweeper::OnAddFailed(IScene* item)const
{
	Log::AssertFailedFormat("Duplicate add dead scene:{}", item->Name().c_str());
}
#endif


void SceneSweeper::OnRelease(IScene* item)const
{
	SceneManager::Instance().DeleteScene(item, false);
}


MEDUSA_END;
