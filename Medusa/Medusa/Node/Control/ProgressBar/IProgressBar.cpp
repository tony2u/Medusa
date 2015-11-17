// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "IProgressBar.h"
#include "Node/Action/Basic/ProgressToAction.h"
#include "Node/Action/Basic/ProgressByAction.h"
#include "Core/Action/DelegateAction.h"
#include "Core/Action/Composite/SequenceAction.h"

MEDUSA_BEGIN;

IProgressBar::IProgressBar(StringRef name/*=StringRef::Empty*/,ProgressType progressType/*=ProgressType::HorizontalLeftToRight*/,float percent/*=1.f*/)
	:INode(name),mProgressType(progressType),mPercent(percent)
{

}

IProgressBar::~IProgressBar( void )
{

}

bool IProgressBar::Initialize()
{
	OnUpdateMesh();
	return true;
}

void IProgressBar::SetPercent(float val)
{
	if (Math::IsEqual(mPercent,val))
	{
		return;
	}

	mPercent = val;
	OnProgressChanged(this,mPercent);
	OnUpdateMesh(false);

}


void IProgressBar::AddPercent(float val)
{
	SetPercent(mPercent + val);
}

void IProgressBar::SetProgressType(ProgressType val)
{
	RETURN_IF_EQUAL(mProgressType,val);
	mProgressType = val;
	OnUpdateMesh(true);
}

void IProgressBar::MoveTo(float val, float duration /*=0.f*/,ProgressCompletedDelegate handler/*=nullptr*/)
{
	ProgressToAction* action=ProgressToAction::Create(val,duration);
	DelegateAction* completedAction=new DelegateAction(handler);
	SequenceAction* seq=SequenceAction::Create(action,completedAction);
	RunAction(seq);
}

void IProgressBar::MoveBy(float val, float duration /*= 0.f*/,ProgressCompletedDelegate handler/*=nullptr*/)
{
	ProgressByAction* action=ProgressByAction::Create(val,duration);
	DelegateAction* completedAction=new DelegateAction(handler);
	SequenceAction* seq=SequenceAction::Create(action,completedAction);
	RunAction(seq);
}

void IProgressBar::BlendVertex(const Array<Point3F, 4>& initialData, Array<Point3F, 4>& outData, ProgressType progressType, float percent, bool isFlipX)
{
	/*
	3:	left-top		2:	right-top
	0:	left-bottom		1:	right-bottom
	*/
	
	//outData = initialData;
	percent=Math::Clamp(percent,0.f,1.f);

	switch (progressType)
	{
	case ProgressType::HorizontalLeftToRight:
		if (isFlipX)
		{
			outData[0].X = Math::LinearInterpolate(initialData[0].X, initialData[1].X, 1.f - percent);
			outData[3].X = Math::LinearInterpolate(initialData[3].X, initialData[2].X, 1.f - percent);
		}
		else
		{
			outData[1].X = Math::LinearInterpolate(initialData[0].X, initialData[1].X, percent);
			outData[2].X = Math::LinearInterpolate(initialData[3].X, initialData[2].X, percent);
		}
		break;
	case ProgressType::HorizontalRightToLeft:
		if (isFlipX)
		{
			outData[1].X = Math::LinearInterpolate(initialData[0].X, initialData[1].X, percent);
			outData[2].X = Math::LinearInterpolate(initialData[3].X, initialData[2].X, percent);
		}
		else
		{
			outData[0].X = Math::LinearInterpolate(initialData[0].X, initialData[1].X, 1.f - percent);
			outData[3].X = Math::LinearInterpolate(initialData[3].X, initialData[2].X, 1.f - percent);
		}
		
		break;
	case ProgressType::VerticalBottomToTop:
		outData[0].Y=Math::LinearInterpolate(initialData[0].Y,initialData[3].Y,percent);
		outData[1].Y=Math::LinearInterpolate(initialData[1].Y,initialData[2].Y,percent);
		break;
	case ProgressType::VerticalTopToBottom:
		outData[2].Y=Math::LinearInterpolate(initialData[1].Y,initialData[2].Y,1.f-percent);
		outData[3].Y=Math::LinearInterpolate(initialData[0].Y,initialData[3].Y,1.f-percent);
		break;
	case ProgressType::RadialClockWise:
		//TODO: ProgressType::RadialClockWise
		break;
	case ProgressType::RadialCounterClockWise:
		//TODO: ProgressType::RadialCounterClockWise
		break;
	default:
		break;
	}
}

void IProgressBar::BlendTexcoord(const Array<Point2F, 4>& initialData, Array<Point2F, 4>& outData, ProgressType progressType, float percent, bool isFlipX)
{
	/*
	3:	left-top		2:	right-top
	0:	left-bottom		1:	right-bottom
	*/

	percent=Math::Clamp(percent,0.f,1.f);

	switch (progressType)
	{
		case ProgressType::HorizontalLeftToRight:
			if (isFlipX)
			{
				outData[0].X = Math::LinearInterpolate(initialData[0].X, initialData[1].X, 1.f - percent);
				outData[3].X = Math::LinearInterpolate(initialData[3].X, initialData[2].X, 1.f - percent);
			}
			else
			{
				outData[1].X = Math::LinearInterpolate(initialData[0].X, initialData[1].X, percent);
				outData[2].X = Math::LinearInterpolate(initialData[3].X, initialData[2].X, percent);
			}
			break;
		case ProgressType::HorizontalRightToLeft:
			if (isFlipX)
			{
				outData[1].X = Math::LinearInterpolate(initialData[0].X, initialData[1].X, percent);
				outData[2].X = Math::LinearInterpolate(initialData[3].X, initialData[2].X, percent);
			}
			else
			{
				outData[0].X = Math::LinearInterpolate(initialData[0].X, initialData[1].X, 1.f - percent);
				outData[3].X = Math::LinearInterpolate(initialData[3].X, initialData[2].X, 1.f - percent);
			}

			break;
		case ProgressType::VerticalBottomToTop:
			outData[0].Y = Math::LinearInterpolate(initialData[0].Y, initialData[3].Y, percent);
			outData[1].Y = Math::LinearInterpolate(initialData[1].Y, initialData[2].Y, percent);
			break;
		case ProgressType::VerticalTopToBottom:
			outData[2].Y = Math::LinearInterpolate(initialData[1].Y, initialData[2].Y, 1.f - percent);
			outData[3].Y = Math::LinearInterpolate(initialData[0].Y, initialData[3].Y, 1.f - percent);
			break;
		case ProgressType::RadialClockWise:
			//TODO: ProgressType::RadialClockWise
			break;
		case ProgressType::RadialCounterClockWise:
			//TODO: ProgressType::RadialCounterClockWise
			break;
		default:
			break;
	}
}

MEDUSA_IMPLEMENT_RTTI(IProgressBar, INode);

MEDUSA_END;
