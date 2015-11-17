// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "UISceneGraph.h"
#include "Rendering/RenderEngine.h"
#include "Node/Scene/IScene.h"
#include "Core/Profile/ProfileSample.h"
#include "Rendering/RenderQueue/Multiple/UIRenderQueue.h"

MEDUSA_BEGIN;

UISceneGraph::UISceneGraph(IScene* scene)
	:ISceneGraph(scene)
{
	mRenderQueue = new UIRenderQueue(scene->RenderTarget(), scene->GetCamera());
}


UISceneGraph::~UISceneGraph(void)
{
}


bool UISceneGraph::OnUpdateQueue()
{
	MEDUSA_PROFILE("UISceneGraph::OnUpdateQueue");
	mRenderQueue->Clear();
	if (mScene->IsValidToRenderQueue())
	{
		AddNodeRecursivelyToRenderQueue(mScene);
	}

	//reorder the sprites ???????????? ????????sprite?????,?????????????????

	return true;
}


void UISceneGraph::AddNodeRecursivelyToRenderQueue(INode* node)
{
	NodeList& childs = node->MutableChildren();
	size_t count = childs.Count();
	size_t i = 0;
	//add child z <0
	for (; i < count; i++)
	{
		INode* childNode = childs[i];
		BREAK_IF(childNode->LogicZ() >= 0);
		CONTINUE_IF_FALSE(childNode->IsValidToRenderQueue());
		AddNodeRecursivelyToRenderQueue(childNode);
	}

	//add node
	if (node->HasValidMesh())
	{
		mRenderQueue->AddNode(node);
	}

	//add child z>=0
	for (; i < count; i++)
	{
		INode* childNode = childs[i];
		CONTINUE_IF_FALSE(childNode->IsValidToRenderQueue());
		AddNodeRecursivelyToRenderQueue(childNode);
	}

}



MEDUSA_END;
