// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "Core/String/HeapString.h"
#include "Geometry/Size2.h"
#include "Geometry/GeometryDefines.h"

MEDUSA_BEGIN;

template<typename TData>
class TNodeTemplate
{
public:
	virtual ~TNodeTemplate(void) {}
	int Tag() const { return mTag; }
	void SetTag(int val) { mTag = val; }

	AnchorPoint Anchor() const { return mAnchor; }
	void SetAnchor(AnchorPoint val) { mAnchor = val; }

	DockPoint Dock() const { return mDock; }
	void SetDock(DockPoint val) { mDock = val; }

	virtual Size2F Measure(const TData& data,const Size2F& limitSize=Size2F::Zero)const { return Size2F::Zero; }
	virtual INode* Load(const TData& data, const Size2F& limitSize = Size2F::Zero, INode* reloadNode = nullptr) const { return reloadNode; }
	virtual bool FetchData(const INode* node, TData& refData) const { return false; }
protected:
	void OnSetupNode(INode* node)const
	{
		RETURN_IF_NULL(node);
		node->SetAnchorPoint(mAnchor);
		node->SetDock(mDock);
	}
protected:
	int mTag = 0;
	AnchorPoint mAnchor= AnchorPoint::LeftBottom;
	DockPoint mDock= DockPoint::LeftBottom;
};

MEDUSA_END;
