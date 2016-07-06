// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Node/INode.h"
#include "Node/Input/Gesture/EventArg/TapGestureEventArg.h"
#include "Node/Input/Gesture/IGestureRecognizer.h"
#include "Core/Pattern/Event.h"

MEDUSA_BEGIN;

//[PRE_DECLARE_BEGIN]
typedef Delegate<void(IProgressBar* sender, float percent)> ProgressChangedDelegate;
typedef Event<void(IProgressBar* sender, float percent)> ProgressChangedEvent;
typedef Delegate<void(void* sender)> ProgressCompletedDelegate;

//[PRE_DECLARE_END]


class IProgressBar :public INode
{
	MEDUSA_RTTI(IProgressBar, INode);
public:
	IProgressBar(const StringRef& name = StringRef::Empty, const IEventArg& e = IEventArg::Empty);
	IProgressBar(StringRef name = StringRef::Empty, ProgressType progressType = ProgressType::HorizontalLeftToRight, float percent = 1.f);
	virtual ~IProgressBar(void);
	virtual bool Initialize() override;

	ProgressChangedEvent OnProgressChanged;

public:
	float Percent() const { return mPercent; }
	void SetPercent(float val);

	void AddPercent(float val);

	ProgressType GetProgressType() const { return mProgressType; }
	void SetProgressType(ProgressType val);

	void MoveTo(float val, float duration = 0.f, ProgressCompletedDelegate handler = nullptr);
	void MoveBy(float val, float duration = 0.f, ProgressCompletedDelegate handler = nullptr);
protected:
	virtual void OnUpdateMesh(bool isProgressTypeChanged = false) = 0;

public:
	static void BlendVertex(const Array<Point3F, 4>& initialData, Array<Point3F, 4>& outData, ProgressType progressType, float percent, bool isFlipX);
	static void BlendTexcoord(const Array<Point2F, 4>& initialData, Array<Point2F, 4>& outData, ProgressType progressType, float percent, bool isFlipX);
protected:
	ProgressType mProgressType=ProgressType::HorizontalLeftToRight;
	float mPercent=1.f;	//0.f~1.f

};

MEDUSA_END;
